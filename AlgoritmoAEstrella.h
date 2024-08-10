#include <iostream>

class nodo{
	public:
	int g; // costo del origen hasta el nodo
	int h; // costo del nodo al objetivo
	int f; // suma de g + h

	std::pair<int,int> anterior;
	std::pair<int,int> actual;
	nodo(std::pair<int,int> p){
		f = 0;
		g = 0;
		h = 0;
		anterior = {-1,-1};
		actual = p;
	}
};

class AlgoritmoAEstrella: public EstructuraPrincipal{
	public:
	using EstructuraPrincipal::EstructuraPrincipal;
	void iniciar_busqueda();
	int calcular_ruta();
	int menor_f(std::vector<nodo>&);
	int buscar(std::vector<nodo>&, nodo);
	std::vector<std::pair<int,int>> obtener_aristas(std::pair<int,int>);
	void calculo_final();
};
