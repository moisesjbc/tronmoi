// TODO: Add license note.

/*
  Nombre: TRONMOI
  Autor: Moises Bonilla (Neodivert)
  Fecha de inicio: 02/08/2009
  Fecha de finalización: 03/08/2009 (v0.6), 03/08/2009 (v0.65)
  Descripcion: Versión del clásico juego Tron. Dos jugadores permanecen en movimiento sobre la
  pantalla dejando un muro detrás de sí. Si uno de los jugadores sale de la pantalla o se
  choca con un muro pierde.
*/

#include<SDL/SDL_ttf.h>
#include "game_grid.hpp"

#include <iostream>
using namespace std;


/*                             Constantes y variables globales                                 */
/***********************************************************************************************/

SDL_Surface *Pantalla;
SDL_Event Evento;

enum RGB {
    R = 0, G, B
};

struct sJugador {
    int x, y;
    Sint8 dx, dy;
    Uint32 Color_Cabeza;
    Uint32 Color_Cuerpo;
} J1, J2;

bool Muerte_J1 = false, Muerte_J2 = false;
const Uint8 TAM = 20; // Tamaño del cuadrado que representa a cada jugador.

/*                                 Prototipos de funciones                                     */
/***********************************************************************************************/

inline int Valor_En_Rango( Sint16 Valor, Sint16 Min, Sint16 Max );
Uint32 Obtener_Pixel( SDL_Surface *Superficie, Uint16 x, Uint16 y );
void Mostrar_Resultado();


/*                                Definiciones de funciones                                    */
/***********************************************************************************************/






int main( int argc, char *argv[] )
{
    (void)( argc );
    (void)( argv );

    /*
        Inicialización del sistema de video.
    */

    SDL_Init( SDL_INIT_VIDEO );

    if( SDL_WasInit( SDL_INIT_VIDEO ) ){
        atexit( SDL_Quit );
        Pantalla = SDL_SetVideoMode( 800, 600, 32, SDL_ANYFORMAT );
        SDL_WM_SetCaption( "TRONMOI", NULL );

        GameGrid gameGrid( Pantalla, 30 );

        const Uint32 COLOR_NEGRO = SDL_MapRGB( Pantalla->format, 0, 0, 0 );

        /*
            Inicialización de los colores elegidos para ambos jugadores.
        */
        J1.Color_Cabeza = SDL_MapRGB( Pantalla->format, 255, 0, 0 );
        J1.Color_Cuerpo = SDL_MapRGB( Pantalla->format, 155, 0, 0 );

        J2.Color_Cabeza = SDL_MapRGB( Pantalla->format, 0, 0, 255 );
        J2.Color_Cuerpo = SDL_MapRGB( Pantalla->format, 0, 0, 155 );

        for( ;; ){
            gameGrid.clear();

            /*
                Inicialización de las coordenadas y el tamaño de los cuadrados que representaran a
                los jugadores.
            */
            gameGrid.getPlayerInitialPos( 0, J1.x, J1.y );
            gameGrid.getPlayerInitialPos( 1, J2.x, J2.y );

            /*
            Inicialización del desplazamiento inicial de cada jugador. Ambos empezarán
            desplazándose hacia arriba.
            */
            J1.dx = J2.dx = 0;
            J1.dy = J2.dy = -1;

            /*
                Dibujado de la "cabeza" de cada jugador.
            */
            gameGrid.setPos( J1.x, J1.y, TileType::PLAYER_1 );
            gameGrid.setPos( J2.x, J2.y, TileType::PLAYER_2 );

            Muerte_J1 = Muerte_J2 = false;

            while( !Muerte_J1 && !Muerte_J2 ){
                /*
                    Game loop : Se permanecerá en el bucle mientras ambos jugadores permanezcan
                    vivos.
                */

                while( SDL_PollEvent( &Evento ) ){
                    /*
                        Consulta de la cola de eventos.
                    */
                    if( Evento.type == SDL_KEYDOWN ){
                        /*
                            Evento producido al pulsar una tecla. Se analiza si es uno de los
                            botones de dirección de uno de los jugadores y en tal caso se
                            modifica la dirección de su desplazamiento.
                        */
                        switch( Evento.key.keysym.sym ){
                            /*
                                Botones de dirección del jugador 1.
                            */
                            case SDLK_w:
                                J1.dy = -1;
                                J1.dx = 0;
                            break;
                            case SDLK_s:
                                J1.dy = 1;
                                J1.dx = 0;
                            break;
                            case SDLK_d:
                                J1.dy = 0;
                                J1.dx = 1;
                            break;
                            case SDLK_a:
                                J1.dy = 0;
                                J1.dx = -1;
                            break;

                            /*
                                Botones de dirección del jugador 2.
                            */
                            case SDLK_UP:
                                J2.dy = -1;
                                J2.dx = 0;
                            break;
                            case SDLK_DOWN:
                                J2.dy = 1;
                                J2.dx = 0;
                            break;
                            case SDLK_RIGHT:
                                J2.dy = 0;
                                J2.dx = 1;
                            break;
                            case SDLK_LEFT:
                                J2.dy = 0;
                                J2.dx = -1;
                            break;

                            default:
                                NULL;
                            break;

                        };
                    }else if( Evento.type == SDL_QUIT ){
                        /*
                            Evento para salir del programa.
                        */
                        exit(0);
                    }
                }


                /*
                    Se avanzan las coordenadas de ambos jugadores.
                */
                J1.x += J1.dx;
                J1.y += J1.dy;

                J2.x += J2.dx;
                J2.y += J2.dy;


                if( gameGrid.getPos( J1.x, J1.y ) == TileType::EMPTY ){
                    gameGrid.setPos( J1.x, J1.y, TileType::PLAYER_1 );
                    gameGrid.setPos( J1.x - J1.dx, J1.y - J1.dy, TileType::PLAYER_1_WALL );
                }else{
                    Muerte_J1 = true;
                }

                if( gameGrid.getPos( J2.x, J2.y ) == TileType::EMPTY ){
                    gameGrid.setPos( J2.x, J2.y, TileType::PLAYER_2 );
                    gameGrid.setPos( J2.x - J2.dx, J2.y - J2.dy, TileType::PLAYER_2_WALL );
                }else{
                    Muerte_J2 = true;
                }


                /*
                    Se actualiza la pantalla y se espera 0.250 segundos.
                */
                gameGrid.draw( J1.Color_Cabeza,
                               J1.Color_Cuerpo,
                               J2.Color_Cabeza,
                               J2.Color_Cuerpo );
                SDL_Flip( Pantalla );
                SDL_Delay( 50 );
            }

            SDL_FillRect( Pantalla, NULL, COLOR_NEGRO );
            /*
                Según si uno de los jugadores o ambos están muertos se determina quién ganó.
            */

            Mostrar_Resultado();
            SDL_FillRect( Pantalla, NULL, COLOR_NEGRO );

        }
    }

    /*
        Error inicializando el sistema de vídeo.
    */
    cerr << "Error inicializando el sistema de video: " << SDL_GetError() << endl;
    exit(-1);


}

void Mostrar_Resultado(){
    // Superficies para guardar las imágenes.
    SDL_Surface *I_Victoria, *I_Recomenzar;

    // Rectángulos para establecer las coordenadas y tamaño de las imágenes.
    SDL_Rect C_Victoria, C_Recomenzar;

    bool Salir_Bucle = false;

    /*
        Inicialización de las coordenadas y el tamaño de los rectángulos de ambas imágenes.
    */
    C_Victoria.x = 175;
    C_Victoria.y = 250;
    C_Victoria.w = 500;
    C_Victoria.h = 60;

    C_Recomenzar.x = 75;
    C_Recomenzar.y = 560;
    C_Recomenzar.w = 650;
    C_Recomenzar.h = 40;

    /*
        Según se trate de un empate o de la victoria de uno de los jugadores se carga la imagen
        con el resultado acorde.
    */
    if( Muerte_J1 && Muerte_J2 ){
        I_Victoria = SDL_LoadBMP( "../share/tronmoi/img/Empate.bmp" );
    }else if( Muerte_J1 ){
        I_Victoria = SDL_LoadBMP( "../share/tronmoi/img/Gana_Jugador_2.bmp" );
    }else{
        I_Victoria = SDL_LoadBMP( "../share/tronmoi/img/Gana_Jugador_1.bmp" );
    }

    /*
        Se carga la imagen con el texto "Pulse una tecla cualquiera para jugar de nuevo".
    */
    I_Recomenzar = SDL_LoadBMP( "../share/tronmoi/img/Recomenzar.bmp" );

    /*
        Si una de las imagenes no se cargó correctamente se sale del programa y se informa del
        error.
    */
    if( !I_Victoria ){
        cerr << "No se pudo cargar el texto de victoria : " << SDL_GetError() << endl;
        exit(-1);
    }

    if( !I_Recomenzar ){
        cerr << "No se pudo cargar el texto de recomenzar : " << SDL_GetError() << endl;
        exit(-1);
    }

    /*
        Blitting y refresco de la pantalla.
    */
    SDL_BlitSurface( I_Victoria, NULL, Pantalla, &C_Victoria );
    SDL_Flip( Pantalla );
    SDL_Delay( 1000 );
    while( SDL_PollEvent( &Evento ) ){
        if( Evento.type == SDL_QUIT ){
            exit(0);
        }
    }

    SDL_BlitSurface( I_Recomenzar, NULL, Pantalla, &C_Recomenzar );
    SDL_Flip( Pantalla );

    /*
        Liberación de las superficies;
    */
    SDL_FreeSurface( I_Victoria );
    SDL_FreeSurface( I_Recomenzar );

    /*
        Se permanece en la pantalla de resultado mientras no se pulse una tecla o no se cierre
        el juego.
    */
    while( !Salir_Bucle ){
        while( SDL_PollEvent( &Evento ) ){
            if( Evento.type == SDL_KEYDOWN ){
                Salir_Bucle = true;
            }else if( Evento.type == SDL_QUIT ){
                exit( 0 );
            }
        }
    }

}



inline int Valor_En_Rango( Sint16 Valor, Sint16 Min, Sint16 Max ){
    return ( ( Valor > Min ) && ( Valor < Max ) );
}



Uint32 Obtener_Pixel( SDL_Surface *Superficie, Uint16 x, Uint16 y ){
    // Obtiene los Bytes Per Píxel.
    int bpp = Superficie->format->BytesPerPixel;


    // Accede al píxel solicitado.
    Uint8 *p = (Uint8 *)Superficie->pixels + y * Superficie->pitch + x * bpp;

    switch( bpp ){
        case 1: // 8 bits
            return *p;
        break;
        case 2: // 16 bits
            return *(Uint16*)p;
        break;
        case 3: // 24 bits
            if( SDL_BYTEORDER == SDL_BIG_ENDIAN ){
                /*
                    Se desplazan los valores de R 16 posiciones y de G 8 posiciones para
                    determinar el color.
                */
                return p[R] << 16 | p[G] << 8 | p[B];
            }else{
                return p[R] | p[G] << 8 | p[B] << 16;
            }
        break;
        default: // 4 bytes - 32 bits
            return *(Uint32*)p;
        break;
    }

}



