//============================================================================
// Name        : Hello.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
	int num_threads, id, A[1000000];
#pragma omp parallel private(id, num_threads)
	{
		id = omp_get_thread_num();
		cout << id;
		num_threads = omp_get_num_threads();
		for (int i = id * (1000000 / num_threads);
				i < ((id + 1) * (1000000 / num_threads) - 1); i++)
		{
			A[i] = i;
		}
	}
	//cout << id << endl;
	return 0;
}
