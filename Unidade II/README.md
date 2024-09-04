# Trabalho 2.1 – Algoritmo de Ordenação com Threads
**Objetivo**: Escrever um programa para medir o desempenho do algoritmo de ordenação 
MergeSort, com e sem uso de threads:
* Utilize um vetor 80.000 amostras geradas aleatoriamente (utilize a mesma semente 
para poder reproduzir o experimento.
* Divida o vetor em N subvetores de mesma dimensão.
* Utilize uma thread para ordenar cada subvetor, utilizando-se o algoritmo BubbleSort.
* Em seguida utilize uma thread para fazer o MERGE (fusão, combinação) ordenado dos N
subvetores já ordenados.
* Faça o experimento para N=1,2,4,8,16.
* Meça o tempo de execução para cada um dos valores de N excutando as threads em 
sequência e em paralelo.
* Apresente o gráfico de desempenho da duas abordagens (em sequência e em paralelo).

Resolução: 
- Sequencial: arquivo sequencial.cpp
- Paralelo: arquivo paralelo.cpp
- Gráfico: notebook Tarefa_Un2_STR
