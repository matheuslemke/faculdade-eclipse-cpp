//============================================================================
// Name        : FibonacciLista1.cpp
// Author      : Lemke
// Version     :
// Copyright   : Your copyright notice
// Description : Exercise list
//============================================================================

#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define TAM 1000
#define MAX_THREADS 128
using namespace std;

int fibSections(int n)
{
	int r1 = 0, r2 = 0;
	if (n < 2)
		return 1;

#pragma omp parallel sections
	{
#pragma omp section
		{
			r1 = fibSections(n - 1);
		}
#pragma omp section
		{
			r2 = fibSections(n - 2);
		}
	}

	return r1 + r2;
}

int fibTasks(int n)
{
	int r1 = 0, r2 = 0;
	if (n < 2)
		return 1;

#pragma omp task shared(r1)
	r1 = fibTasks(n - 1);

#pragma omp task shared(r2)
	r2 = fibTasks(n - 2);

#pragma omp taskwait
	return r1 + r2;
}

int fibonacciSections(int x)
{
	int value = 0;

	value = fibSections(x);

	return value;
}

int fibonacciTasks(int x)
{
	int value = 0;
#pragma omp parallel
	{
#pragma omp single
		{
			value = fibTasks(x);
		}
	}
	return value;
}

/**
 * Paralelize o código recursivo do Fibonacci utilizando
 * a) tasks e b) sections.
 */
void questaoUm()
{
	int x = 9;

	cout << fibonacciSections(x);
	cout << fibonacciTasks(x);
}

/**
 * Considere como paralelizar o código
 */
void questaoDois()
{
	int a[TAM];
#pragma omp parallel for
	for (int i = 0; i < TAM; ++i)
		a[i] = i;

	int totais[MAX_THREADS][16];
	int total = 0; //,i;
#pragma omp parallel
	{
		int me = omp_get_thread_num();
		totais[me][0] = 0;
#pragma omp for
		for (int i = 0; i < TAM; i++)
		{
			totais[me][0] += a[i] | totais[me][0];
		}
#pragma omp barrier

#pragma omp single
		{
			for (int var = 0; var < omp_get_num_threads(); var++)
			{
				cout << var << ": " << totais[var][0] << endl;
				total += totais[var][0];
			}
		}
	}
	// O valor correto está na thread3, igual no do minimo
	cout << total;
}

/**
 * Considere como paralelizar o código
 */
void questaoTres()
{
	int a[TAM];
#pragma omp parallel for
	for (int i = 0; i < TAM; ++i)
		a[i] = i;

	int ultimos[MAX_THREADS];

	int i;

#pragma omp parallel private(i)
	{
		int me = omp_get_thread_num();
		ultimos[me] = 0;

		int quantidade = TAM / omp_get_num_threads(); //(TAM + num_threads -1)/num_threads;
		if (TAM % omp_get_num_threads() != 0)
			quantidade++;

		int inicio = me * quantidade;
		int fim = inicio + quantidade; //fim adiantado

		if (fim > TAM)
			fim = TAM;

		for (i = inicio + 1; (i < fim); i++)
		{
			a[i] = a[i] | a[i - 1];
		}

		ultimos[me] = a[fim - 1];
#pragma omp barrier

#pragma omp single
		{
			int OR = 0; //elemento neutro do or
			int temp;
			for (i = 0; i < omp_get_num_threads(); i++)
			{
				temp = OR | ultimos[i];
				ultimos[i] = OR;
				OR = temp;
				//printf("Thread %d ult = %d\n", i, ultimos[i]);
			}
		}

		int offset = ultimos[me];

		for (i = inicio; (i < fim); i++)
		{
			a[i] = a[i] | offset;
		}
	}

	for (i = 0; i < TAM; i++)
	{
		if (i % 10 == 0)
			printf("\n");
		printf("%d ", a[i]);
	}

}

void questaoTresSeq()
{
	int a[TAM];
#pragma omp parallel for
	for (int i = 0; i < TAM; ++i)
		a[i] = i;

	for (int i = 1; i < TAM; i++)
		a[i] = a[i] | a[i - 1];

	for (int i = 0; i < TAM; i++)
	{
		if (i % 10 == 0)
			printf("\n");
		printf("%d ", a[i]);
	}

}

int particiona(int a[], int ini, int fim)
{
	return (fim + ini) / 2;
}

void quicksort(int a[], int ini, int fim)
{
	if (ini < fim)
	{
		int pivo = particiona(a, ini, fim);
#pragma omp task
		quicksort(a, ini, pivo - 1);

#pragma omp task
		quicksort(a, pivo + 1, fim);
	}
}

void questaoQuatro()
{
	int a[TAM], inicio, fim;
#pragma omp parallel for
	for (int i = 0; i < TAM; ++i)
		a[i] = i;

#pragma omp parallel
	{
#pragma omp master
		{
			quicksort(a, inicio, fim);
		}
		a[10] = 3; // As threads não podem tentar alterar esse valor em paralelo
	}
}

int main()
{
//questaoUm();
//questaoDois();
//questaoTresSeq();
//questaoTres();
	questaoQuatro(); // <- Não está pronto

	return 0;
}

