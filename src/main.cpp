

/*
  Nombre: TRONMOI
  Autor: Moises Bonilla (Neodivert)
  Fecha de inicio: 02/08/2009
  Fecha de finalización: 03/08/2009 (v0.6), 03/08/2009 (v0.65)
  Descripcion: Versión del clásico juego Tron. Dos jugadores permanecen en movimiento sobre la
  pantalla dejando un muro detrás de sí. Si uno de los jugadores sale de la pantalla o se
  choca con un muro pierde.
*/

#include"cMenu.cpp"

/*                             Constantes y variables globales                                 */
/***********************************************************************************************/



enum RGB {
    R = 0, G, B
};

struct sJugador {
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






int main( int argc, char *argv[] ){

    SDL_Rect C1, C2; // Cuadrados que representan a ambos jugadores.


    /*
        Inicialización del sistema de video.
    */

    SDL_Init( SDL_INIT_VIDEO );

    if( SDL_WasInit( SDL_INIT_VIDEO ) ){
        atexit( SDL_Quit );
        Pantalla = SDL_SetVideoMode( 800, 600, 32, SDL_ANYFORMAT );
        SDL_WM_SetCaption( "TRONMOI", NULL );

        const Uint32 COLOR_NEGRO = SDL_MapRGB( Pantalla->format, 0, 0, 0 );

        /*
            Inicialización de los colores elegidos para ambos jugadores.
        */
        J1.Color_Cabeza = SDL_MapRGB( Pantalla->format, 255, 0, 0 );
        J1.Color_Cuerpo = SDL_MapRGB( Pantalla->format, 155, 0, 0 );

        J2.Color_Cabeza = SDL_MapRGB( Pantalla->format, 0, 0, 255 );
        J2.Color_Cuerpo = SDL_MapRGB( Pantalla->format, 0, 0, 155 );

        for( ;; ){

            /*
                Inicialización de las coordenadas y el tamaño de los cuadrados que representaran a
                los jugadores.
            */
            C1.x = 150;
            C1.y = 300;
            C1.h = TAM;
            C1.w = TAM;

            C2.x = 650;
            C2.y = 300;
            C2.h = TAM;
            C2.w = TAM;

            /*
            Inicialización del desplazamiento inicial de cada jugador. Ambos empezarán
            desplazándose hacia arriba.
            */
            J1.dx = J2.dx = 0;
            J1.dy = J2.dy = -TAM;
            /*
                Dibujado de la "cabeza" de cada jugador.
            */
            SDL_FillRect( Pantalla, &C1, J1.Color_Cabeza );
            SDL_FillRect( Pantalla, &C2, J2.Color_Cabeza );

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
                                if( Obtener_Pixel( Pantalla, C1.x, C1.y-TAM ) != J1.Color_Cuerpo ){
                                    J1.dy = -TAM;
                                    J1.dx = 0;
                                }
                            break;
                            case SDLK_s:
                                if( Obtener_Pixel( Pantalla, C1.x, C1.y+TAM ) != J1.Color_Cuerpo ){
                                    J1.dy = TAM;
                                    J1.dx = 0;
                                }
                            break;
                            case SDLK_d:
                                if( Obtener_Pixel( Pantalla, C1.x+TAM, C1.y ) != J1.Color_Cuerpo ){
                                    J1.dy = 0;
                                    J1.dx = TAM;
                                }
                            break;
                            case SDLK_a:
                                if( Obtener_Pixel( Pantalla, C1.x-TAM, C1.y ) != J1.Color_Cuerpo ){
                                    J1.dy = 0;
                                    J1.dx = -TAM;
                                }
                            break;

                            /*
                                Botones de dirección del jugador 2.
                            */
                            case SDLK_UP:
                                if( Obtener_Pixel( Pantalla, C2.x, C2.y-TAM ) != J2.Color_Cuerpo ){
                                    J2.dy = -TAM;
                                    J2.dx = 0;
                                }
                            break;
                            case SDLK_DOWN:
                                if( Obtener_Pixel( Pantalla, C2.x, C2.y+TAM ) != J2.Color_Cuerpo ){
                                    J2.dy = TAM;
                                    J2.dx = 0;
                                }
                            break;
                            case SDLK_RIGHT:
                                if( Obtener_Pixel( Pantalla, C2.x+TAM, C2.y ) != J2.Color_Cuerpo ){
                                    J2.dy = 0;
                                    J2.dx = TAM;
                                }
                            break;
                            case SDLK_LEFT:
                                if( Obtener_Pixel( Pantalla, C2.x-TAM, C2.y ) != J2.Color_Cuerpo ){
                                    J2.dy = 0;
                                    J2.dx = -TAM;
                                }
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
                    Se sustituye la "cabeza" por otra parte del "cuerpo".
                */
                SDL_FillRect( Pantalla, &C1, J1.Color_Cuerpo );
                SDL_FillRect( Pantalla, &C2, J2.Color_Cuerpo );

                /*
                    Se avanzan las coordenadas de ambos jugadores.
                */
                C1.x += J1.dx;
                C1.y += J1.dy;

                C2.x += J2.dx;
                C2.y += J2.dy;

                if( !Valor_En_Rango( C1.x+C1.w, 0, 800 ) || !Valor_En_Rango( C1.y+C1.h, 0, 600 )
                    || ( Obtener_Pixel( Pantalla, C1.x, C1.y ) != COLOR_NEGRO ) ){
                    /*
                        El jugador 1 muere al salir de la pantalla o a chocar con un obstáculo.
                    */
                    Muerte_J1 = true;
                }

                if( !Valor_En_Rango( C2.x+C2.w, 0, 800 ) || !Valor_En_Rango( C2.y+C2.h, 0, 600 )
                    || ( Obtener_Pixel( Pantalla, C2.x, C2.y ) != COLOR_NEGRO ) ){
                    /*
                        El jugador 2 muere al salir de la pantalla o a chocar con un obstáculo.
                    */
                    Muerte_J2 = true;
                }

                /*
                    Se dibuja la "cabeza" en las nuevas coordenadas para ambos jugadores.
                */
                SDL_FillRect( Pantalla, &C1, J1.Color_Cabeza );
                SDL_FillRect( Pantalla, &C2, J2.Color_Cabeza );

                /*
                    Se actualiza la pantalla y se espera 0.250 segundos.
                */
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
    if( Valor <= Min | Valor >= Max ){
        return false;
    }else{
        return true;
    }
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



