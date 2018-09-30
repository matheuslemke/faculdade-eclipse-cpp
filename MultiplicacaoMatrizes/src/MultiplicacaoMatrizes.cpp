//============================================================================
// Name        : MultiplicacaoMatrizes.cpp
// Author      : Lemke
// Version     :
// Copyright   : Your copyright notice
// Description : Multiply matrixes in parallel
//============================================================================

#include <iostream>
#include <omp.h>
#include <stdio.h>
#define TAM 800

using namespace std;

int main()
{
	int matrixA[TAM][TAM];
	int matrixB[TAM][TAM];
	int matrixC[TAM][TAM];

	int i, j, k;

#pragma omp parallel for private(j)
	for (i = 0; i < TAM; i++)
		for (j = 0; j < TAM; j++)
		{
			matrixA[i][j] = 1;
			matrixB[i][j] = 1;
			matrixC[i][j] = 0;
		}

#pragma omp parallel for private(j, k)
	for (i = 0; i < TAM; i++)
		for (k = 0; k < TAM; k++)
			for (j = 0; j < TAM; j++)
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];

	for (i = 0; i < TAM; i++)
	{
		for (j = 0; j < TAM; j++)
			printf("%d ", matrixC[i][j]);
		cout << endl;
	}

	return 0;
}
