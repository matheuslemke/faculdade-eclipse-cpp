//============================================================================
// Name        : TestesCpp.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
 * cin.get();

 //if (s == "aaa")

 cout << "Good job.\n" << s;
 //else
 cout << "I meant ONLY the ENTER key... Oh well.\n";
 *
 *
 *cout << "Press the ENTER key";
 string s;

 //getline(cin, s) &&
 cin >> s;
 while (s != "#")
 {
 cout << " hm" << endl;
 cin >> s;
 }
 */

int main()
{
	// um vector vazio que conterá strings
	vector<string> nomes;

	// vamos inserir três nomes
	for (int var = 0; var < 1; ++var)
	{
		nomes.push_back("Osmar J. Silva");
		nomes.push_back("Carlos de Souza");
		nomes.push_back("Maria Dias de Carvalho");
	}

	// vamos percorrer o vector e exibir os nomes
	vector<string>::iterator it;
	for (int i = 0, it = nomes.begin(); it < nomes.end(); i++, it++)
	{
		cout << *it << i << endl;
	}

	return 0;

	return 0;
}
