//============================================================================
// Name        : Teste.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

enum Cor
{
	BRANCO, CINZA, PRETO
};

typedef struct Aresta
{
	int indiceDestino;
} ares;

typedef struct Vertice
{
	string nome;
	int descoberta;
	int finalizacao;
	int pai;
	Cor cor;
	list<Aresta> adj;
} vert;

list<Vertice> List;
string String;

static int tempo;
int tamanhoVetor = 0;

int procurarVeticePeloNome(Vertice *vetor, string v)
{
	int indice = -1;

	for (int i = 0; i < tamanhoVetor; i++)
		if (vetor[i].nome == v)
			indice = i;

	return indice;
}

bool contains(list<Aresta> lista, int element)
{
	for (Aresta aresta : lista)
		if (aresta.indiceDestino == element)
			return true;
	return false;
}

void lerArestas(Vertice **vetor, int orientado)
{
	string aresta;

	for (;;)
	{
		getline(cin, aresta);

		if (!aresta.empty())
		{
			int espaco = aresta.find(" ");

			string nomeV1 = aresta.substr(0, espaco);
			string nomeV2 = aresta.substr(espaco + 1);

			int v1 = procurarVeticePeloNome(*vetor, nomeV1);
			int v2 = procurarVeticePeloNome(*vetor, nomeV2);

			if (!(contains((*(vetor + v1))->adj, v2)))
			{
				Aresta *aresta = (Aresta *) malloc(sizeof(Aresta));
				aresta->indiceDestino = v2;
				(*vetor)[v1].adj.push_back(*aresta);
			}

			if (orientado == 1)
			{
				Aresta *aresta = (Aresta *) malloc(sizeof(Aresta));
				aresta->indiceDestino = v1;
				(*vetor)[v2].adj.push_back(*aresta);
			}
		}
		else
			return;
	}
}

int tamanhoLista(list<string> lista)
{
	int i = 0;
	for (i = 0; !lista.empty(); i++)
	{
		lista.pop_front();
	}
	return i;
}

Vertice* lerVetor()
{
	int orientado;
	string separador;
	list<string> listaVertices;

	cin >> orientado;

	cin >> separador;

	if (separador == "#")
	{
		//Leitura dos vertices
		string v;
		for (int i = 0;; i++)
		{
			cout << "V" << i << ": ";
			cin >> v;

			if (v.compare("#") != 0)
			{
				listaVertices.push_back(v);
			}

		}

		//Transferir valores da lista pro vetor

		Vertice *vetor = (Vertice*) malloc(
				tamanhoLista(listaVertices) * sizeof(Vertice));

		for (int i = 0; i < tamanhoLista(listaVertices); i++)
		{
			vetor[i].nome = listaVertices.front();
			listaVertices.remove(vetor[i].nome);
		}

		//Leitura das arestas
		lerArestas(&vetor, orientado);

		return vetor;
	}

	return NULL;
}

void dfsVisit(Vertice **vetor, int i)
{
	tempo++;
	(*vetor)[i].descoberta = tempo;
	(*vetor)[i].cor = CINZA;

	for (Aresta aresta : (*vetor)[i].adj)
		if ((*vetor)[aresta.indiceDestino].cor == BRANCO)
		{
			(*vetor)[aresta.indiceDestino].pai = i;
			dfsVisit(vetor, aresta.indiceDestino);
		}

	(*vetor)[i].cor = PRETO;
	tempo++;
	(*vetor)[i].finalizacao = tempo;
}

void dfs(Vertice **vetor)
{
	for (int i = 0; i < tamanhoVetor; ++i)
	{
		(*vetor)[i].cor = BRANCO;
		(*vetor)[i].pai = -1;
	}
	tempo = 0;

	for (int i = 0; i < tamanhoVetor; ++i)
		if ((*vetor)[i].cor == BRANCO)
			dfsVisit(vetor, i);

}

void imprimir(Vertice *vetor)
{
	for (int i = 0; i < tamanhoVetor; ++i)
	{
		cout << vetor[i].nome << " ";
		cout << vetor[i].descoberta << "/";
		cout << vetor[i].finalizacao << " ";

		if (vetor[i].pai == -1)
			cout << "NIL" << endl;
		else
			cout << vetor[vetor[i].pai].nome << endl;
	}
}

int main()
{

	Vertice *vetor = lerVetor();

	//dfs(&vetor);

	//imprimir(vetor);

	//string aresta;

	//getline(cin, aresta);

	//if (true)
	//cout << aresta.empty();
	return 0;
}
