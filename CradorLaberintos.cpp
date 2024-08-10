#include <iostream>
#include <vector>
#include <string>
#include <random>

#define len(x) (int) x.size()

using namespace std;



int numero_aleatorio(int ancho)
{
	random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(1,ancho-1); // distribucion

    return dist6(rng);
}
vector<string> crear(int alto, int ancho)
{
	vector<string> mapa;
	for(int i = 0; i<alto ; i++)
	{
		mapa.push_back("");
		for(int j = 0; j<ancho; j++)
		{
			//if(numero_aleatorio(10) > 5)
				mapa[i] += "-";
			//else
				//mapa[i] += "#";
		}
	}
	
	return mapa;	
	
}
void cambiar_muro(vector<string> mundo)
{
	for(int i = 0; i<len(mundo); i++){
		for(int j=0; j<len(mundo[i]); j++){
			if(mundo[i][j] == 'm')
				mundo[i][j] = '#';
		}
	}

	for(auto a : mundo){
		cout << a << endl;
	}
}
vector<string> agregar_costo(vector<string> mundo)
{
	for(int i = 0; i<len(mundo); i++){
		for(int j=0; j<len(mundo[i]); j++){
			if(mundo[i][j] == '-')
			{
				int ran = numero_aleatorio(9);
				mundo[i][j] = ran + '0';
			}
		}
	}
	return mundo;
}

int main()
{
	
	vector<string> m = crear(15,60);
	
	
	for(auto a : m)
	{
		cout << "\"" << a << "\"," << endl;
	}
	
	vector<string> mapa = m;
	
	
	
	cout << endl;
	mapa = agregar_costo(mapa);
	
	for(auto a : mapa)
	{
		cout << "\"" << a << "\"," << endl;
	}
	
	

	

	return 0;
}
