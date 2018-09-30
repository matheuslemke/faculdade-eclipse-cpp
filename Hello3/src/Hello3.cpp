//============================================================================
// Name        : Hello3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#define a 16807
#define c 0
#define m (2^31) -1
using namespace std;

long long lcg(long long x)
{
	return (a * x + c) % m;
}

long long lcg(long long x, int skip)
{
	return (x * (a ^ skip)) % m;
}

int main()
{
	int no_circulo = 0, no_quadr = 100000;
	double pi;
	srand((unsigned) time(NULL));

#pragma omp parallel reduction(+:no_circulo)
	{
		double x, y, div_x, div_y;
		long long seed_x, seed_y;
		seed_x = (rand() % (m + 1));
		seed_y = (rand() % (m + 1));
		for (int i = 0; i < no_quadr; ++i)
		{
			x = lcg(seed_x);
			y = lcg(seed_y);

			div_x = (double) x / (double) (m + 1);
			div_y = (double) y / (double) (m + 1);

			if ((((double) div_x * div_x) + ((double) div_y * div_y)) < 1.0)
				no_circulo++;

			seed_x = x;
			seed_y = y;

		}
		pi = 4.0 * (double) no_circulo / (double) no_quadr;
		cout << pi << endl;
	}

	return 0;
}
