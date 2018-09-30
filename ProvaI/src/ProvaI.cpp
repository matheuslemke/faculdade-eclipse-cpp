//============================================================================
// Name        : ProvaI.cpp
// Author      : Anderson Matheus Lemke
// Description : Códigos das questões da Prova I de programação paralela
// S.O.        : Linux (Ubuntu)
//============================================================================

#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM 1000
#define MAX_THREADS 128

static unsigned long long MULTIPLIER = 764261123;
static unsigned long long PMOD = 2147483647;
static unsigned long long mult_n;
static unsigned long long pseed[MAX_THREADS][4];
double random_low, random_hi;
unsigned long long random_last = 0;
#pragma omp threadprivate(random_last)

using namespace std;

void initializeArray(int* A)
{
#pragma omp parallel for
	for (int i = 0; i < TAM; i++)
		A[i] = i + 1;
}

void questaoUmA()
{
	int fechamentos[TAM], flutuacao_diaria[TAM];
	initializeArray(fechamentos);
	int i;

#pragma omp parallel for private(i)
	for (i = 1; i < TAM; ++i)
		flutuacao_diaria[i] = fechamentos[i] - fechamentos[i - 1];

	flutuacao_diaria[0] = 0;

	for (i = 0; i < TAM; i++)
	{
		if (i % 10 == 0)
			printf("\n");
		printf("%d ", flutuacao_diaria[i]);
	}
}

void questaoUmB(int ini, int fimAdiantado)
{
	int fechamentos[TAM], flutuacao_diaria[TAM];
	initializeArray(fechamentos);
	int i;

#pragma omp parallel for private(i)
	for (i = 1; i < TAM; ++i)
		flutuacao_diaria[i] = fechamentos[i] - fechamentos[i - 1];
	flutuacao_diaria[0] = 0;

	int *flutuacao_acumulada = flutuacao_diaria;
	int ultimos[MAX_THREADS];

#pragma omp parallel private(i)
	{
		int me = omp_get_thread_num();
		ultimos[me] = 0;

		int quantidade = (TAM + omp_get_num_threads() - 1)
				/ omp_get_num_threads();

		int inicio = me * quantidade;
		int fim = inicio + quantidade;

		if (fim > TAM)
			fim = TAM;

		for (i = inicio + 1; (i < fim); i++)
			flutuacao_acumulada[i] = flutuacao_acumulada[i - 1]
					+ flutuacao_acumulada[i];

		ultimos[me] = flutuacao_acumulada[fim - 1];

#pragma omp barrier

#pragma omp single
		{
			int sum = 0;
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
			flutuacao_acumulada[i] += offset;
	}

	for (i = 0; i < TAM; i++)
	{
		if (i % 10 == 0)
			printf("\n");
		printf("%d ", flutuacao_acumulada[i]);
	}

	printf("\nFlutuacao acumulada no intervalo [%d - %d] = %d", ini,
			fimAdiantado,
			flutuacao_acumulada[fimAdiantado - 1] - flutuacao_acumulada[ini]);
}

double randomN()
{
	unsigned long long random_next;
	double ret_val;

//gera num. aleatorio
	random_next = (unsigned long long) ((MULTIPLIER * random_last) % PMOD);
	random_last = random_next;

//normaliza
	ret_val = ((double) random_next / (double) PMOD) * (random_hi - random_low)
			+ random_low;
	return ret_val;
}

void seed(double low_in, double hi_in, unsigned long long seed_initial,
		int n_cada)
{
	int i, id;
	unsigned long long seed_ini;
	id = omp_get_thread_num();

#pragma omp single
	{
		if (low_in < hi_in)
		{
			random_low = low_in;
			random_hi = hi_in;
		}
		else
		{
			random_low = hi_in;
			random_hi = low_in;
		}

		//printf("%d\n", nthreads);

		seed_ini = seed_initial % PMOD;
		pseed[0][0] = seed_ini;
		mult_n = MULTIPLIER;
		for (i = 1; i < n_cada; ++i)
		{
			mult_n = (mult_n * MULTIPLIER) % PMOD;
			//pseed[i][0] = (seed_ant * mult_n) % PMOD;
			//seed_ant = (unsigned long long) ((MULTIPLIER * seed_ant) % PMOD);

			//mult_n = (mult_n * MULTIPLIER) % PMOD;
		}
		for (i = 1; i < omp_get_num_threads(); i++)
		{
			pseed[i][0] = (unsigned long long) (pseed[i - 1][0] * mult_n)
					% PMOD;
		}
	}
	random_last = (unsigned long long) pseed[id][0];
}

void questaoDois()
{
	static long num_cada_thread = 20000;
	long long i;
	long Ncirc = 0;
	double pi, x, y, test;
	double r = 1.0;

#pragma omp parallel
	{
		seed(-r, r, 10, num_cada_thread);
		cout << omp_get_thread_num() << ": " << random_last << endl;

#pragma omp for reduction(+:Ncirc)
		for (i = 0; i < (num_cada_thread * omp_get_num_threads()); i++)
		{
			x = randomN();
			y = randomN();

			test = x * x + y * y;

			if (test <= r * r)
				Ncirc++;
		}

#pragma omp single
		{
			pi = 4.0 * ((double) Ncirc / ((double) num_cada_thread * omp_get_num_threads()));
			cout << endl << (num_cada_thread * omp_get_num_threads())
					<< " trials, pi is " << pi << endl;
		}
	}

}

void questaoTres()
{
	int A[TAM];
	initializeArray(A);
	int i;
	int ultimos[MAX_THREADS];

#pragma omp parallel private(i)
	{
		int inicial = A[0];
		int me = omp_get_thread_num();
		ultimos[me] = 0;

		int quantidade = (TAM + omp_get_num_threads() - 1)
				/ omp_get_num_threads();

		int inicio = me * quantidade;
		int fim = inicio + quantidade;

		if (fim > TAM)
			fim = TAM;

		A[inicio] = inicial;
		for (i = inicio + 1; (i < fim); i++)
			A[i] = A[i - 1] + inicial;

		ultimos[me] = A[fim - 1];

#pragma omp barrier

#pragma omp single
		{
			for (i = 0; i < TAM; i++)
			{
				if (i % 10 == 0)
					printf("\n");
				printf("%d ", A[i]);
			}
			printf("\n");

			int sum = 0;
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
			A[i] += offset;
	}

	for (i = 0; i < TAM; i++)
	{
		if (i % 10 == 0)
			printf("\n");
		printf("%d ", A[i]);
	}
}

void questaoQuatro()
{
	int m = 100, p = 200, q = 400;
	int first[m][p];
	int second[p][q];
	int multiply[m][q];
	int c, d, k;

#pragma omp parallel for private(k)
	for (c = 0; c < m; c++)
		for (k = 0; k < p; k++)
			first[c][k] = 1;

#pragma omp parallel for private(d)
	for (k = 0; k < p; k++)
		for (d = 0; d < q; d++)
			second[k][d] = 1;

#pragma omp parallel for private(d)
	for (c = 0; c < m; c++)
		for (d = 0; d < q; d++)
			multiply[c][d] = 0;

#pragma omp parallel for private(k,d)
	for (c = 0; c < m; c++)
		for (k = 0; k < p; k++)
			for (d = 0; d < q; d++)
				multiply[c][d] += first[c][k] * second[k][d];

	for (c = 0; c < m; c++)
	{
		for (d = 0; d < q; d++)
		{
			if (d % 10 == 0)
				printf("\n");
			printf("%d ", multiply[c][d]);
		}
		printf("\n\n");
	}

}

int main()
{
	//questaoUmA();
	//questaoUmB(0, 1000);
	//questaoDois();
	//questaoTres();
	//questaoQuatro();

	return 0;
}
