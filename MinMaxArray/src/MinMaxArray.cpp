//============================================================================
// Name        : MinMaxArray.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Finds the lowest and the higher values in an array in parallel
//============================================================================

#include <iostream>
#include <omp.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_THREADS 128
#define TAM 650000
using namespace std;

//VERSÃO PARALELA
int main()
{
	int num_threads = omp_get_num_threads();
	int minimos_maximos[MAX_THREADS][16];

	int minimo, maximo;

	int i;

	int dados[TAM];
	double dados_normalizados[TAM];

	double limite_inferior = 0.0;
	double limite_superior = 1.0;

	for (i = 0; i < TAM; i++)
	{
		dados[i] = TAM - i;
	}

#pragma omp parallel
	{
//minimo = INT_MAX;
		int me = omp_get_thread_num();
		minimos_maximos[me][0] = INT_MAX;
		minimos_maximos[me][1] = INT_MIN;

#pragma omp for
		for (i = 0; i < TAM; i++)
		{
			/*if (dados[i] < minimo){
			 minimo = dados[i];
			 }*/
			if (dados[i] < minimos_maximos[omp_get_thread_num()][0])
			{
				minimos_maximos[omp_get_thread_num()][0] = dados[i];
			}
			if (dados[i] > minimos_maximos[omp_get_thread_num()][1])
			{
				minimos_maximos[omp_get_thread_num()][1] = dados[i];
			}
		}

//somente necessario por causa do nowait
#pragma omp barrier

#pragma omp single
		{
			minimo = minimos_maximos[0][0];
			maximo = minimos_maximos[0][1];
			printf("Thread 0 min = %d, max = %d\n", minimos_maximos[0][0],
					minimos_maximos[0][1]);
			for (i = 1; i < omp_get_num_threads(); i++)
			{
				if (minimos_maximos[i][0] < minimo)
				{
					minimo = minimos_maximos[i][0];
				}
				printf("Thread %d min = %d, max = %d\n", i,
						minimos_maximos[i][0], minimos_maximos[i][1]);
			}
		}

	}

	printf("Minimo = %d, Maximo = %d", minimo, maximo);

#pragma omp for
	for (i = 0; i < TAM; ++i)
	{
		dados_normalizados[i] = ((double) (dados[i] - minimo)
				/ (double) (maximo - minimo))
				* (limite_superior - limite_inferior);
	}

	for (i = 0; i < TAM; ++i)
	{
		printf("%.8lf ", dados_normalizados[i]);
		if ((i + 1) % 10 == 0)
			printf("\n");
	}

	getchar();
	return 0;
}
