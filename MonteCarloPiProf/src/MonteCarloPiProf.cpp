//============================================================================
// Name        : MonteCarloPiProf.cpp
// Author      : Richard
// Version     :
// Copyright   : Your copyright notice
// Description : Calculates the pi number in parallel
//============================================================================

// UTILIZA REDUCTION
#include <stdio.h>
#include <omp.h>
#include <iostream>

static unsigned long long MULTIPLIER = 764261123;
static unsigned long long PMOD = 2147483647;
static unsigned long long mult_n;
double random_low, random_hi;

#define MAX_THREADS 128
static unsigned long long pseed[MAX_THREADS][4]; //[4] padding para evitar cache ping-pong
unsigned long long random_last = 0;
#pragma omp threadprivate(random_last)

using namespace std;

double random()
{
	unsigned long long random_next;
	double ret_val;

//gera num. aleatorio
	random_next = (unsigned long long) ((mult_n * random_last) % PMOD);
	random_last = random_next;

//normaliza
	ret_val = ((double) random_next / (double) PMOD) * (random_hi - random_low)
			+ random_low;
	return ret_val;
}

//
// seta as sementes e os saltos
void seed(double low_in, double hi_in, unsigned long long initial_seed)
{
	int i, id, nthreads;
	unsigned long long iseed;
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

		nthreads = omp_get_num_threads();

//printf("%d\n", nthreads);

		iseed = initial_seed % PMOD;
		pseed[0][0] = iseed;
		mult_n = MULTIPLIER;
		for (i = 1; i < nthreads; ++i)
		{
			iseed = (unsigned long long) ((MULTIPLIER * iseed) % PMOD);
			pseed[i][0] = iseed;
			mult_n = (mult_n * MULTIPLIER) % PMOD;
		}

	}
	random_last = (unsigned long long) pseed[id][0];
}

static long num_trials = 5000000;

int main()
{
	long i;
	long Ncirc = 0;
	double pi, x, y, test;
	double r = 1.0;

//omp_set_num_threads(8);

//printf("%d\n",omp_get_num_threads());

#pragma omp parallel
	{
		seed(-r, r, 10);
//printf("%d\n", omp_get_thread_num());

#pragma omp for reduction(+:Ncirc)
		for (i = 0; i < num_trials; i++)
		{
			x = random();
			y = random();

			test = x * x + y * y;

			if (test <= r * r)
				Ncirc++;
		}
	}

	pi = 4.0 * ((double) Ncirc / (double) num_trials);

	cout << endl << num_trials << " trials, pi is " << pi << endl;

	getchar();

	return 0;
}
