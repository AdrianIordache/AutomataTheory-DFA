#include <fstream>
#include <iostream>
#include <cstring>
#define N 20

using namespace std;

//Functia care ajuta la decodificarea datelor in functie de indicii vectorului
inline int decodifica(char c, int n, char *v)
{
	for(int i = 0; i < n; ++i)
		if(v[i] == c) return i;
	return 0;
}

//Functia care ajuta la codificare datelor in functie de vector
inline char codifica(int c, char* v)
{
	return v[c];
}

//Aici sunt accesate elementele matricei de tranzitie pe a vedea starea finala daca este acceptata
bool verifica(int **tranzitii, char *cuvant, char stareaInitiala, int nrStari, int nrAlfabet, char* stari, char* alfabet, bool* final)
{
 	static int i = 0; static bool ok;
 	int aux = tranzitii[decodifica(cuvant[i], nrAlfabet, alfabet)][decodifica(stareaInitiala, nrStari, stari)];
 	stareaInitiala = codifica(aux, stari);
 	if(i == strlen(cuvant) - 1)
 	{
 		if(final[aux] == true) ok = true; 
 					else ok = false;
 	}
 	while(i < strlen(cuvant) - 1)
 	{
 		++i;
 		verifica(tranzitii, cuvant, stareaInitiala, nrStari, nrAlfabet, stari, alfabet, final);
 	}

 	if(ok == true) return true;
 	return false;
}

//Realizeaza citirea starilor, alfabetului, starilor finale si determinarea matricei de tranzitie 
void automat(char *nume_fisier)
{
	ifstream fin(nume_fisier);
	int nrStari, nrAlfabet, nrTranzitii, nrFinal;

	fin >> nrStari;
	char *stari = new char[nrStari];
	for(int i = 0; i < nrStari; ++i)
		fin >> stari[i];

	cout<<"Starile automatului sunt: \n";
	for(int i = 0; i < nrStari; ++i)
		cout<< stari[i] <<' ';
	cout<<'\n';

	fin >> nrAlfabet;
	char *alfabet = new char[nrAlfabet];
	for(int i = 0; i < nrAlfabet; ++i)
		fin >> alfabet[i];

	cout<<"Alfabetul automatului este: \n";
	for(int i = 0; i < nrAlfabet; ++i)
		cout<< alfabet[i] <<' ';
	cout<<'\n';

	fin >> nrTranzitii;
	int** tranzitii = new int*[nrAlfabet];
	for(int i = 0; i < nrAlfabet; ++i)
		tranzitii[i] = new int [nrStari];

	for(int i = 0; i < nrAlfabet; ++i)
		for(int j = 0; j < nrStari; ++j)
			tranzitii[i][j] = 0;
		
	cout<<"Matricea functiilor de tranzitie este: \n";
	char nodInitial, tranzitie, nodFinal;
	for(int i = 0; i < nrTranzitii; ++i)
	{
		fin >> nodInitial >> tranzitie >> nodFinal;


		int k = decodifica(tranzitie, nrAlfabet, alfabet);
		int t = decodifica(nodInitial, nrStari, stari);
		tranzitii[k][t] = decodifica(nodFinal, nrStari, stari);
	}

	for(int i = 0; i < nrAlfabet; ++i)
	{
		for(int j = 0; j < nrStari; ++j)
			cout<<tranzitii[i][j]<<' ';
		cout<<'\n';
	}

	cout<<"Vectorul de booli"<<'\n';
	bool final[nrStari]; char aux;
	for(int i = 0; i < nrStari; ++i)
	{
		fin >> aux;
		if(aux == 'f') final[i] = false;
				else final[i] = true;
	}	

	for(int i = 0; i < nrStari; ++i)
	{
		if(final[i] == true) cout<<'1'<<' ';
					else cout<<'0'<<' ';
	}
	cout<<'\n';

	char stareaInitiala;
	fin >> stareaInitiala;
	char *cuvant = new char[N];
	fin >> cuvant; 

	bool ok = true;

	char auxiliar[N];
	for(int i = 0; i < nrAlfabet; ++i)
		auxiliar[i] = alfabet[i];
	
	if(strspn(cuvant, auxiliar) != strlen(cuvant)) ok = false;

	if(ok == false) {cout << "Cuvantul nu apartine limbajului\n";}
		else
	if(strcmp(cuvant, "#") == 0) cout << "Cuvantul apartine limbajului\n";
		else
	{
		if(verifica(tranzitii, cuvant, stareaInitiala, nrStari, nrAlfabet, stari, alfabet, final))
			cout << "Cuvantul apartine limbajului\n";
				else
			cout << "Cuvantul nu apartine limbajului\n";
	}

}
int main()
{
	char s[] = "Exemplu1.in", g[] = "Exemplu2.in", t[] = "Exemplu3.in";
	//automat(s);
	//automat(g);
	automat(t);

}

