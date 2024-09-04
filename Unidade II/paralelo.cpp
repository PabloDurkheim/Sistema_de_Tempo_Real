#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <thread>
#include <chrono>

void bubbleSort(std::vector<int>& subvector) {
    bool swapped;
    for (size_t i = 0; i < subvector.size() - 1; ++i) {
        swapped = false;
        for (size_t j = 0; j < subvector.size() - i - 1; ++j) {
            if (subvector[j] > subvector[j + 1]) {
                std::swap(subvector[j], subvector[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> merged;
    merged.reserve(left.size() + right.size());
    size_t i = 0, j = 0;

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            merged.push_back(left[i++]);
        } else {
            merged.push_back(right[j++]);
        }
    }

    while (i < left.size()) {
        merged.push_back(left[i++]);
    }

    while (j < right.size()) {
        merged.push_back(right[j++]);
    }

    return merged;
}

void parallelSortAndMerge(int N, const std::vector<int>& vec) {
    std::vector<std::vector<int>> subvectors(N);
    int subvector_size = vec.size() / N;
    int remainder = vec.size() % N;

    int start = 0;
    for (int i = 0; i < N; ++i) {
        int current_size = subvector_size + (i < remainder ? 1 : 0);
        subvectors[i] = std::vector<int>(vec.begin() + start, vec.begin() + start + current_size);
        start += current_size;
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads;
    for (auto& subvector : subvectors) {
        threads.emplace_back(bubbleSort, std::ref(subvector));
    }
    for (auto& th : threads) {
        th.join();
    }

    while (subvectors.size() > 1) {
        std::vector<std::vector<int>> new_subvectors;
        std::vector<std::thread> merge_threads;
        for (size_t i = 0; i + 1 < subvectors.size(); i += 2) {
            merge_threads.emplace_back([&new_subvectors, &subvectors, i] {
                std::vector<int> merged = merge(subvectors[i], subvectors[i + 1]);
                new_subvectors.push_back(std::move(merged));
            });
        }
        for (auto& th : merge_threads) {
            th.join();
        }
        if (subvectors.size() % 2 == 1) {
            new_subvectors.push_back(std::move(subvectors.back()));
        }
        subvectors = std::move(new_subvectors);
    }

    std::vector<int> sorted_par = subvectors[0];

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;
    std::cout << "N = " << N << " - Tempo de ordenação paralelo: " << duration.count() << " segundos.\n";
}

int main() {
    const int size = 80000;
    std::vector<int> vec(size);

    std::mt19937 gen(0);
    std::uniform_int_distribution<int> dis(0, 100000);

    for (int i = 0; i < size; ++i) {
        vec[i] = dis(gen);
    }

    std::vector<int> N_values = {1, 2, 4, 8, 16, 32};

    for (int N : N_values) {
        parallelSortAndMerge(N, vec);
    }

    return 0;
}
