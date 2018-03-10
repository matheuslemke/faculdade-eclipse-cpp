//============================================================================
// Name        : dfs.cpp
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
static int tamanhoVetor;

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
	list<Aresta>::iterator it;
	for (it = lista.begin(); it != lista.end(); it++)
		if ((*it).indiceDestino == element)
			return true;
	return false;
}

void lerArestas(Vertice **vetor, int orientado)
{
	string aresta, aresta2;

	while (getline(cin, aresta) && !aresta.empty())
	{
		cout << "procura ae";

		int espaco = aresta.find(" ");

		cout << "Espaço: " << espaco << endl;

		string nomeV1 = aresta.substr(0, espaco);
		string nomeV2 = aresta.substr(espaco);

		int v1 = procurarVeticePeloNome(*vetor, aresta);
		int v2 = procurarVeticePeloNome(*vetor, aresta2);

		if (!(contains((*(vetor + v1))->adj, v2)))
		{
			cout << "Não contém" << endl;
			Aresta *aresta = (Aresta *) malloc(sizeof(Aresta));
			aresta->indiceDestino = v2;
			(*vetor)[v1].adj.push_back(*aresta);
		}

		if (orientado == 1)
		{
			Aresta *aresta2 = (Aresta *) malloc(sizeof(Aresta));
			aresta2->indiceDestino = v1;
			(*vetor)[v2].adj.push_back(*aresta2);
		}
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
	vector<string> vetorVertices;

	cin >> orientado;

	cin >> separador;

	if (separador == "#")
	{
		//Leitura dos vertices
		string v;
		cout << "V: ";
		cin >> v;

		while (v != "#")
		{
			vetorVertices.push_back(v);

			cout << "V: ";
			cin >> v;

		}

		//Transferir valores da lista pro vetor

		//cout << "Tam: " << vetorVertices.size() << endl;

		Vertice *vetor = (Vertice*) malloc(
				vetorVertices.size() * sizeof(Vertice));

		vector<string>::iterator it;
		int i = 0;

		for (it = vetorVertices.begin(); it < vetorVertices.end(); it++)
		{
			cout << *it << endl;
			vetor[i].nome = *it;
			++i;
		}

		//list<int> lista;
		//lista.push_back(1);
		//lista.push_back(2);
		//lista.push_back(3);

		if (!vetorVertices.empty())
		{

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

	list<Aresta>::iterator it;

	for (it = (*vetor)[i].adj.begin(); it != (*vetor)[i].adj.end(); it++)
		if ((*vetor)[(*it).indiceDestino].cor == BRANCO)
		{
			(*vetor)[(*it).indiceDestino].pai = i;
			dfsVisit(vetor, (*it).indiceDestino);
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

	cout << tamanhoVetor;

	cout << "opa1";
	//dfs(&vetor);
	cout << "opa2";
	//imprimir(vetor);

	//string aresta;

	//getline(cin, aresta);

	//if (true)
	//cout << aresta.empty();
	return 0;
}
