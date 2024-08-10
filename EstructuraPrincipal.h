#include <ncurses.h>
#include <random>	
#include <queue>
#include <unistd.h>


// su usan para poner una marca de color
#define PAR_BUSCAR    1
#define PAR_CAMINO    2
#define PAR_BLANCO    3
#define PAR_MURO      4
#define PAR_NORMAL    5

class EstructuraPrincipal{
	protected:
	
	//coordenadas del cursor
	int x = 0, y = 0;

	//tiempo espera
	int espera;
	
	//coordenadas del laberino
	int lx = 20, ly = 3;
	
	//posicion de incio de la busqueda
	int ix, iy;
	
	//posicion de final de la busqeda
	
	int fx, fy;
	
	//caracter que representa un muro
	char muro;
	
	//Alto y ancho del laberinto
	int alto, ancho;
	
	//mapa del laberino
	std::vector<std::string> laberinto;
	
	// mapa con las coordenadas ya visitadas
	std::vector<std::vector<int>> mapa_vistos;
	
	std::vector<std::vector<std::pair<int,int>>> mapa_anteriores; 	/* mapa con los predecesores de las coordenadas */
																	/* sirve para calcular la ruta final */
	
	
	public:
	
	EstructuraPrincipal(int,int,int,int,int,int,char,std::vector<std::string>,int);
	void posicionar_inicio();
	void posicionar_partida();
	void posicionar_final();
	void pintar_final();
	void pintar_inicio();
	void dibujar_laberino();
	void cursor_set_color_string(const char *);
	int x_coor(int);
	int y_coor(int);
	int x_lab();
	int y_lab();
	
	void buscar();
	
	
};

