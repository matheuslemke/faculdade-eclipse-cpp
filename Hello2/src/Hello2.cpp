//============================================================================
// Name        : Hello2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <omp.h>
#include <time.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int fibonnacci(int x)
{
	if (x == 1)
		return 1;
	if (x == 0)
		return 1;
	return fibonnacci(x - 1) + fibonnacci(x - 2);
}

int fibonnacci_iter(int x)
{
	unsigned int i = 1, j = 0, k, t;
//#pragma omp parallel for
	for (k = 1; k <= x; k++)
	{
		t = i + j;
		i = j;
		j = t;
	}
	return j;
}

int main()
{
	/*
	 int size = 100000;
	 int num_threads, id, A[size], B[size], C[size];
	 #pragma omp parallel private(id, num_threads)
	 {
	 id = omp_get_thread_num();
	 num_threads = omp_get_num_threads();
	 for (int i = id * (size / num_threads);
	 i < ((id + 1) * (size / num_threads) - 1); i++)
	 {
	 B[i] = i;
	 C[i] = 1;
	 }
	 }
	 */
	/*
	 #pragma omp parallel for
	 for (int i = 0; i < size; ++i)
	 A[i] = B[i] + C[i];

	 #pragma omp parallel for
	 for (int i = 0; i < size; ++i)
	 cout << A[i] << " ";
	 */

	/*
	 * padrão = static
	 * schedule(guided)
	 * schedule(dynamic)
	 */
	/*
	 #pragma omp parallel for
	 for (int i = 0; i < 1000; ++i)
	 cout << fibonnacci(i) << endl;
	 */

	int no_circulo = 0;
	double pi;
	srand((unsigned) time(NULL));

#pragma omp parallel reduction(+:no_circulo)
	{
		double x, y;
		for (int i = 0; i < 10; ++i)
		{
			x = (rand() % 101) / 100.0;
			y = (rand() % 101) / 100.0;

			if (((x * x) + (y * y)) < 1.0)
				no_circulo++;
		}
		pi = 4 * no_circulo / 10;
		cout << pi << endl;
	}

	return 0;
}
