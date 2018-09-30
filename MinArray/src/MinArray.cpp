//============================================================================
// Name        : MinArray.cpp
// Author      : Lemke
// Version     :
// Copyright   : Your copyright notice
// Description : Finds the lowest value in an array in parallel
//============================================================================

#include <iostream>
#include <omp.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_THREADS 128
#define TAM 1000000
using namespace std;

//VERSÃO PARALELA
int main()
{
	int num_threads = omp_get_num_threads();
	int minimos[MAX_THREADS][16];

	int minimo;

	int i;

	int dados[TAM];

	for (i = 0; i < TAM; i++)
	{
		dados[i] = TAM - i;
	}

#pragma omp parallel
	{
//minimo = INT_MAX;
		int me = omp_get_thread_num();
		minimos[me][0] = INT_MAX;

#pragma omp for
		for (i = 0; i < TAM; i++)
		{
			/*if (dados[i] < minimo){
			 minimo = dados[i];
			 }*/
			if (dados[i] < minimos[omp_get_thread_num()][0])
			{
				minimos[omp_get_thread_num()][0] = dados[i];
			}
		}

//somente necessario por causa do nowait
#pragma omp barrier

#pragma omp single
		{
			minimo = minimos[0][0];
			printf("Thread 0 min = %d\n", minimos[0][0]);
			for (i = 1; i < omp_get_num_threads(); i++)
			{
				if (minimos[i][0] < minimo)
				{
					minimo = minimos[i][0];
				}
				printf("Thread %d min = %d\n", i, minimos[i][0]);
			}
		}

	}

	printf("Minimo = %d", minimo);

	getchar();
	return 0;
}

//VERSÃO SEQUENCIAL
/*
 int main()
 {
 int minimos[MAX_THREADS][16];
 int minimo = INT_MAX, i, dados[TAM];

 for (int i = 0; i < TAM; ++i)
 {
 dados[i] = TAM - i;
 }

 for (int i = 0; i < TAM; ++i)
 {
 if (dados[i] < minimo)
 {
 minimo = dados[i];
 }
 }

 cout << "Minimo = " << minimo << endl;

 return 0;
 }
 */

