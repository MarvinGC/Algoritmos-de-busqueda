#include "EstructuraPrincipal.h"

EstructuraPrincipal::EstructuraPrincipal(int labx, int laby, int iniciox, int inicioy, int finalx, int finaly,
								char caracter_muro, std::vector<std::string> mapa, int tiempo_espera = 50000)
{
	lx = labx;              /*  coordenadas del la posicion inicial de laberinito*/
	ly = laby;
	ix = x_coor(iniciox);    /* coordenadas de la posicion de partida de la busqueda */
	iy = y_coor(inicioy);    /* expresada con las coordenadas del arreglo */
	fx = x_coor(finalx);     /* coordenadas de la posicion objetivo de la busqueda */
	fy = y_coor(finaly);     /* expresada con las coordenadas del arreglo */
	muro = caracter_muro;
	espera = tiempo_espera;
	laberinto = mapa;
	alto = (int) laberinto.size();
	ancho = (int) laberinto[0].size();
	
	curs_set (2);
	
	init_pair(PAR_BUSCAR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(PAR_CAMINO, COLOR_WHITE, COLOR_YELLOW);
    init_pair(PAR_BLANCO, COLOR_WHITE, COLOR_BLACK);
    init_pair(PAR_MURO, COLOR_WHITE, COLOR_WHITE);
    
    clear();
    
	
	/* mapa con las coordenadas ya visitadas */
	/* Aqui se inicalizan todoas las coordenadas de igual amplitud y anchura que el laberinoto*/
	/* con valor 0 que representara que no se ha visitado mientras que 1 representara que ya se visito*/
	mapa_vistos = std::vector<std::vector<int>>(alto, std::vector<int>(ancho)); 
	
	/* mapa anteriores es un arreglo bidimencional de pares que representaran */
	/* las coordenadas predecesoras en una ubicacion dada */
	/* Aqui se inicalizan todoas las coordenadas de igual amplitud y anchura que el laberinoto*/
	/* con valor (-1,-1) que representa que no existe predecesor*/
	mapa_anteriores = std::vector<std::vector<std::pair<int,int>>>
										(alto, std::vector<std::pair<int,int>>( ancho, {-1,-1} ) );
	
	// Aqui hace el dibujo de laberino base
	dibujar_laberino();
	
	// colorea el punto de objetivo final
	pintar_final();
}

//Posiciona en la esquina superior izquierda del laberinito
void EstructuraPrincipal::posicionar_inicio()
{
	x = lx, y = ly;
	move(y,x);
}
//Posiciona el punto de se comenzara la busqueda
void EstructuraPrincipal::posicionar_partida()
{
	x = ix, y = iy;
	move(y,x);
}
//Posiciona el punto de se comenzara la busqueda
void EstructuraPrincipal::posicionar_final()
{
	x = fx, y = fy;
	move(y,x);
}
void EstructuraPrincipal::pintar_final()
{
	x = fx, y = fy;
	move(y,x);
	attron(COLOR_PAIR(PAR_CAMINO));
	printw("%c",laberinto[y_lab()][x_lab()]);
	
}
void EstructuraPrincipal::pintar_inicio()
{
	x = ix, y = iy;
	move(y,x);
	attron(COLOR_PAIR(PAR_CAMINO));
	printw("%c",laberinto[y_lab()][x_lab()]);
	
}
int EstructuraPrincipal::x_coor(int num)
{
	return num + lx;
}
int EstructuraPrincipal::y_coor(int num)
{
	return num + ly;
}
	
int EstructuraPrincipal::x_lab()
{
	return x - lx;
}
int EstructuraPrincipal::y_lab()
{
	return y - ly;
}

void EstructuraPrincipal::dibujar_laberino()
{		
	posicionar_inicio();
	for(std::string s: laberinto)
	{
		for(int i = 0; i<(int) s.size();i++)
		{
				if(s[i] == muro)
				{
					attron(COLOR_PAIR(PAR_MURO));
					printw("%c",s[i]);
				}
				else
				{
					attron(COLOR_PAIR(PAR_BLANCO));
					printw("%c",s[i]);
				}
		}
		y++;
		move(y,x);
	}
		
}

void EstructuraPrincipal::cursor_set_color_string(const char *color) 
{
	printf("\e]12;%s\a", color);
	fflush(stdout);
}
