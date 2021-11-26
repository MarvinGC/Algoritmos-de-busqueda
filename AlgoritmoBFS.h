#include <iostream>

class AlgoritmoBFS: public EstructuraPrincipal{
	public:
	using EstructuraPrincipal::EstructuraPrincipal;
	void iniciar_busqueda();
	int calcular_ruta();
	std::vector<std::pair<int,int>> obtener_aristas(std::pair<int,int>);
	void calculo_final();
};
