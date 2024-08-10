#include "AlgoritmoAEstrella.h"

int AlgoritmoAEstrella::calcular_ruta()
{
	int sum = 0;
	attron(COLOR_PAIR(PAR_CAMINO));
	
	posicionar_final();

	if( mapa_anteriores[y_lab()][x_lab()].first == -1 ||
		 mapa_anteriores[y_lab()][x_lab()].second == -1)
		 return 0;
	

	printw("%c",laberinto[y_lab()][x_lab()]);
	
	sum += (laberinto[y_lab()][x_lab()] - '0');
	
	while(x != ix || y != iy)
	{
		//variables auxiliare para correcto calculo de coordenadas
		int ax = x_coor(mapa_anteriores[y_lab()][x_lab()].first);
		int ay = y_coor(mapa_anteriores[y_lab()][x_lab()].second);
		
		x = ax; y = ay;

		sum += (laberinto[y_lab()][x_lab()] - '0');
		
		move(y,x);
		
		refresh();
		fflush(stdout);
		usleep(espera);
		
		printw("%c",laberinto[y_lab()][x_lab()]);
	}
	
	return sum;
}
std::vector<std::pair<int,int>> AlgoritmoAEstrella::obtener_aristas(std::pair<int,int> a)
{
	std::vector<std::pair<int,int>>  aristas;
	/* 
	for(int i = a.first-1; i<=a.first+1; i++)
	{
		for(int j = a.second-1; j<=a.second+1; j++)
		{
			if(i == a.first && j == a.second)
					continue;
			if(i >= 0 && j >= 0 && 
				i < ancho && j < alto
				 )
			{
				aristas.push_back({i,j});
			}
		}
	}
	*/
	std::vector<int> A = {1,-1};
	for(int v : A)
	{
		std::pair<int,int> p = {a.first+v,a.second};
		if(p.first >= 0 && p.first < ancho &&
			p.second >=0 && p.second < alto)
			aristas.push_back(p);
		p = {a.first,a.second+v};
		if(p.first >= 0 && p.first < ancho &&
			p.second >=0 && p.second < alto)
			aristas.push_back(p);
	}
	return aristas;
}
int AlgoritmoAEstrella::menor_f(std::vector<nodo>& nodos)
{
	int len = (int) nodos.size();
	int m = nodos[0].f;	
	int res = 0;
	for(int i = 0; i<len; i++)
	{
		nodo a = nodos[i];
		if(m > a.f){
			m = a.f;
			res = i;
		}
	}
	return res;
}
int AlgoritmoAEstrella::buscar(std::vector<nodo>& nodos, nodo arista)
{
	int len = (int) nodos.size();
	for(int i = 0; i< len; i++)
	{
		nodo n = nodos[i];
		if(n.actual == arista.actual)
			return i;
	}
	return -1;	
}
void AlgoritmoAEstrella::iniciar_busqueda()
{
	// colorea el punto de inicio
	pintar_inicio();
	
	//Cambia al color de busqueda
	attron(COLOR_PAIR(PAR_BUSCAR));

	std::vector<nodo> abiertos;
	std::vector<nodo> cerrados;
	
	abiertos.push_back(nodo({x_lab(),y_lab()}));
	
	while(!abiertos.empty())
	{
		int in = menor_f(abiertos);
		nodo padre = abiertos[in];
		
		for(auto par: obtener_aristas(padre.actual)){
			x = x_coor(par.first);
			y = y_coor(par.second);
			if(laberinto[y_lab()][x_lab()] != muro)
			{
				
				nodo arista({x_lab(),y_lab()});
				int dist = (laberinto[y_lab()][x_lab()] - '0');
				
				arista.g = padre.g + dist;
				arista.h = sqrt(pow( (fx-x),2) + pow((fy-y),2) );
				arista.f = arista.g + arista.h;
				
				int b = buscar(abiertos, arista);
				int c = buscar(cerrados, arista);
				if(c == -1){
					move(y,x);
					refresh();
					fflush(stdout);
					usleep(espera);
					printw("%c",laberinto[y_lab()][x_lab()]);
					
					if(b != -1 && abiertos[b].f > arista.f ){
						mapa_anteriores[y_lab()][x_lab()] = padre.actual;
						std::swap(abiertos[b],arista);
					}
					else if(b == -1){
						mapa_anteriores[y_lab()][x_lab()] = padre.actual;
						abiertos.push_back(arista);
					}
				}
				if(y == fy && x == fx)
				{
					in = -1;
					break;
				}
			}
			
		}
		cerrados.push_back(padre);
		if(in != -1)
			abiertos.erase(abiertos.begin()+in);
		else{
			std::vector<nodo> vacia;
			std::swap(abiertos,vacia);
		}
	}
	
	
	calculo_final();
}
void AlgoritmoAEstrella::calculo_final()
{
	// Se calcula la mejor ruta mas el costo toral
	int total = calcular_ruta();
	// Se coloca el puntero al principio de la pantalla
	y = 0; x = 0; 
	
	attron(COLOR_PAIR(PAR_BLANCO));
	curs_set (0);
	move(y,x);
	refresh();
	fflush(stdout);
	usleep(espera);
	printw("Total: %d", total);
}
