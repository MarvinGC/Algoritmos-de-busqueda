#include "AlgoritmoBFS.h"


int AlgoritmoBFS::calcular_ruta()
{
	int sum = 0;
	attron(COLOR_PAIR(PAR_CAMINO));
	posicionar_final();
	
	if( mapa_anteriores[y_lab()][x_lab()].first == -1 ||
		 mapa_anteriores[y_lab()][x_lab()].second == -1)
		 return 0;
	
	printw("%c",laberinto[y_lab()][x_lab()]);
	
	sum ++;
	
	while(x != ix || y != iy)
	{
		//variables auxiliares para correcto calculo de coordenadas
		int ax = x_coor(mapa_anteriores[y_lab()][x_lab()].first);
		int ay = y_coor(mapa_anteriores[y_lab()][x_lab()].second);
		
		x = ax; y = ay;

		sum ++;
		
		move(y,x);
		
		refresh();
		fflush(stdout);
		usleep(espera);
		
		printw("%c",laberinto[y_lab()][x_lab()]);
	}
	
	return sum;
}
std::vector<std::pair<int,int>> AlgoritmoBFS::obtener_aristas(std::pair<int,int> a)
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
void AlgoritmoBFS::iniciar_busqueda()
{
	// colorea el punto de inicio
	pintar_inicio();
	
	//Cambia al color de busqueda
	attron(COLOR_PAIR(PAR_BUSCAR));

	std::queue<std::pair<int,int>> q;
	q.push({x_lab(),y_lab()});
	
	while(!q.empty()) // mientras la cola no esta vacia
	{
		std::pair<int,int> a = q.front(); // coordenadas punto actual
		q.pop();
		
		for(auto par : obtener_aristas(a))
		{
			x = x_coor(par.first);
			y = y_coor(par.second);
			if(laberinto[y_lab()][x_lab()] != muro && mapa_vistos[y_lab()][x_lab()] == 0)
			{
				mapa_anteriores[y_lab()][x_lab()] = a;
	
				move(y,x);
				refresh();
				fflush(stdout);
				usleep(espera);
				
				printw("%c",laberinto[y_lab()][x_lab()]);
				
				q.push({x_lab(),y_lab()});
				mapa_vistos[y_lab()][x_lab()] = 1;
				
				if(y == fy && x == fx)
				{
					std::queue<std::pair<int,int>> vacia;
					std::swap(q, vacia);
				}
				
			}
		}
	}
	calculo_final();
}
void AlgoritmoBFS::calculo_final()
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
