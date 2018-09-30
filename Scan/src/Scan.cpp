//============================================================================
// Name        : Scan.cpp
// Author      : Lemke
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// ScanOpenMP.cpp : Defines the entry point for the console application.
//
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <limits.h>

#define MAX_THREADS 128
#define TAM 1000

int main(int argc, char* argv[])
{
//int num_threads = omp_get_num_threads();
	int ultimos[MAX_THREADS];

	int i;

	int dados[TAM];

#pragma omp parallel for
	for (i = 0; i < TAM; i++)
	{
		dados[i] = 1; //i;
	}

#pragma omp parallel private(i)
	{
		int me = omp_get_thread_num();
		ultimos[me] = 0;

		int quantidade = TAM / omp_get_num_threads(); //(TAM + num_threads -1)/num_threads;
		if (TAM % omp_get_num_threads() != 0)
			quantidade++;

		int inicio = me * quantidade;
		int fim = inicio + quantidade; //fim adiantado, ou seja, é até o < e não <=

		if (fim > TAM)
			fim = TAM;

		for (i = inicio + 1; (i < fim); i++)
		{
			dados[i] += dados[i - 1];
		}

		ultimos[me] = dados[fim - 1];

#pragma omp barrier

#pragma omp single
		{
			int sum = 0; //elemento neutro
			int temp;
			for (i = 0; i < omp_get_num_threads(); i++)
			{
				temp = sum + ultimos[i];
				ultimos[i] = sum;
				sum = temp;
				printf("Thread %d ult = %d\n", i, ultimos[i]);
			}
		}

		int offset = ultimos[me];

		for (i = inicio; (i < fim); i++)
		{
			dados[i] += offset;
		}

	}

	for (i = 0; i < TAM; i++)
	{
		if (i % 10 == 0)
			printf("\n");
		printf("%d ", dados[i]);
	}
}
