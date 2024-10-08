//código disponibilizado pelo professor

/*
 *  ordenacao.cpp
 *  
 *
 *  Created by Luiz Affonso Guedes on 06/03/17.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

// UFRN-CT-DCA
// Programa: programa para ordenação de um vetor

// Manipulação de tempo em c,c++
// Programa: programa que usa manipuladores de tempo para 
// medir o desempenho de algoritmos de ordenação


#include <cstdlib>   //qsort
#include  <time.h>   // clock(),time()
#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()


//Vetores usados pelos métodos de ordenação
int *vetorQuickSort;
int *vetorBubbleSort;
int tamanho;

//Função usada pelo qsort para comparar dois numeros
int compare_ints( const void* a, const void* b ) {
	int* arg1 = (int*) a;
	int* arg2 = (int*) b;
	if( *arg1 < *arg2 ) return -1;
	else if( *arg1 == *arg2 ) return 0;
	else return 1;
}

//Algoritmos de ordenação bubble sort
void bubbleSort(int *vetor, int tamanho) {
	int aux;
	for (int i = 0; i < tamanho-1; i++) {
		for (int j = 0; j < tamanho-1; j++) {
			if (vetor[j] > vetor[j+1]) {
				aux = vetor[j];
				vetor[j] = vetor[j+1];
				vetor[j+1] = aux;
			}
		}
	}
}


//Observe que os números são gerados aleatoriamente baseados
//em uma semente. Se for passado a mesma semente, os 
//números aleatórios serão os mesmos
void criarVetor(int tamanhoVetor, int semente){
	srand (semente);
	vetorQuickSort = new int[tamanhoVetor];
	vetorBubbleSort = new int[tamanhoVetor];
	for (int i=0;i<tamanhoVetor;i++){
		vetorQuickSort[i] =  rand()%100000;
        vetorBubbleSort[i] = vetorQuickSort[i]; // utilizar os mesmos valores
		//vetorBubbleSort[i] = rand()%100000;
	}
}



int main ()
{

clock_t inicio, fim;
    double tempo_quick, tempo_bubble;
//time_t inicio, fim;
	//Tamanho do vetor
	int n = 100000;
	//Criar vetor com elementos aleatorios[0,100000] 
	criarVetor(n,23);
	//Ordenar utilizando quickSort
// Medir o tempo de execução do Quick Sort
    inicio = clock();
	//inicio = time(NULL);
	qsort (vetorQuickSort, n, sizeof(int), compare_ints);
fim = clock();
//fim = time(NULL);
    //tempo_quick = difftime(fim, inicio);
    tempo_quick = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
	//Ordenar utilizando bubleSort
 // Medir o tempo de execução do Bubble Sort
    inicio = clock();
//inicio = time(NULL);
	bubbleSort(vetorBubbleSort,n);
 //fim = time(NULL);
    //tempo_bubble = difftime(fim, inicio);
 fim = clock();
    tempo_bubble = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    // Exibir os tempos de execução
    printf("Tempo de execução do Quick Sort: %.6f segundos\n", tempo_quick);
    printf("Tempo de execução do Bubble Sort: %.6f segundos\n", tempo_bubble);
	exit(0);
}


