#include <iostream>      // Biblioteca para entrada e saída de dados
#include <vector>        // Biblioteca para o uso de vetores
#include <random>        // Biblioteca para geração de números aleatórios
#include <algorithm>     // Biblioteca para funções algorítmicas, como std::swap
#include <chrono>        // Biblioteca para medir o tempo
#include <thread>        // Biblioteca para o uso de threads

// Função para realizar o BubbleSort em um subvetor
void bubbleSort(std::vector<int>& subvector) {
    bool swapped;
    for (size_t i = 0; i < subvector.size() - 1; ++i) {
        swapped = false;
        for (size_t j = 0; j < subvector.size() - i - 1; ++j) {
            if (subvector[j] > subvector[j + 1]) {
                // Troca elementos se estiver fora de ordem
                std::swap(subvector[j], subvector[j + 1]);
                swapped = true;
            }
        }
        // Se nenhum elemento foi trocado, o vetor está ordenado
        if (!swapped) {
            break;
        }
    }
}

// Função para mesclar dois vetores ordenados em um vetor único ordenado
std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> merged;
    merged.reserve(left.size() + right.size()); // Reserva espaço para evitar realocações
    size_t i = 0, j = 0;

    // Mescla os vetores enquanto ambos contêm elementos
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            merged.push_back(left[i++]);
        } else {
            merged.push_back(right[j++]);
        }
    }

    // Adiciona os elementos restantes do vetor left se houver
    while (i < left.size()) {
        merged.push_back(left[i++]);
    }

    // Adiciona os elementos restantes do vetor right se houver
    while (j < right.size()) {
        merged.push_back(right[j++]);
    }

    return merged;
}

// Função para ordenar subvetores e mesclar os resultados de forma sequencial usando threads
void sequentialSortAndMerge(int N, const std::vector<int>& vec) {
    std::vector<std::vector<int>> subvectors(N); // Vetor de vetores para armazenar os subvetores
    int subvector_size = vec.size() / N; // Calcula o tamanho base de cada subvetor
    int remainder = vec.size() % N; // Calcula o resto para distribuir igualmente entre os subvetores

    int start = 0;
    // Divide o vetor principal em N subvetores
    for (int i = 0; i < N; ++i) {
        int current_size = subvector_size + (i < remainder ? 1 : 0); // Ajusta o tamanho do subvetor
        subvectors[i] = std::vector<int>(vec.begin() + start, vec.begin() + start + current_size); // Cria o subvetor
        start += current_size; // Atualiza o índice de início para o próximo subvetor
    }

    auto start_time = std::chrono::high_resolution_clock::now(); // Marca o início do tempo de ordenação

    // Ordenação sequencial com threads
    for (auto& subvector : subvectors) {
        // Cria uma thread para ordenar o subvetor
        std::thread t([&subvector]() {
            bubbleSort(subvector); // Ordena o subvetor
        });
        t.join(); 
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Pausa de 1 segundo
    }

    // Mesclagem sequencial com threads
    std::vector<int> sorted_seq = subvectors[0]; // Inicializa o vetor ordenado com o primeiro subvetor
    for (size_t i = 1; i < subvectors.size(); ++i) {
        std::vector<int> temp_sorted;
        // Cria uma thread para mesclar o vetor ordenado com o próximo subvetor
        std::thread t([&sorted_seq, &subvectors, i, &temp_sorted]() {
            temp_sorted = merge(sorted_seq, subvectors[i]); // Mescla os vetores
        });
        t.join(); // Espera a thread terminar antes de continuar
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Pausa de 1 segundo
        sorted_seq = std::move(temp_sorted); // Atualiza o vetor ordenado
    }

    auto end_time = std::chrono::high_resolution_clock::now(); // Marca o fim do tempo de ordenação
    std::chrono::duration<double> duration = end_time - start_time; // Calcula a duração da ordenação
    std::cout << "N = " << N << " - Tempo de ordenação sequencial com threads: " << duration.count() << " segundos.\n"; // Imprime o tempo de ordenação
}

int main() {
    const int size = 160000; // Define o tamanho do vetor principal
    std::vector<int> vec(size); // Cria o vetor principal

    std::mt19937 gen(0); // Inicializa o gerador de números aleatórios com uma semente
    std::uniform_int_distribution<int> dis(0, 100000); // Define a distribuição uniforme para números aleatórios entre 0 e 100000

    // Preenche o vetor com números aleatórios
    for (int i = 0; i < size; ++i) {
        vec[i] = dis(gen);
    }

    std::vector<int> N_values = {1, 2, 4, 8, 16, 32}; // Diferentes valores de N para testar

    // Itera sobre cada valor de N e executa a ordenação e mesclagem
    for (int N : N_values) {
        sequentialSortAndMerge(N, vec); // Chama a função para ordenar e mesclar com o valor atual de N
    }

    return 0; // Finaliza o programa
}
