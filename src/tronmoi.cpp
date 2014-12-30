/*
    Copyright 2009, 2014 Moises J. Bonilla Caraballo

    This file is part of Tronmoi.

    Tronmoi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Tronmoi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Tronmoi.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "tronmoi.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;

/***
 * 1. Construction
 ***/

Tronmoi::Tronmoi( SDL_Surface* screen ) :
    screen_( screen ),
    gameGrid( screen_, 30 )
{
    // Initialize player's colors
    player1.playerColor = SDL_MapRGB( screen_->format, 255, 0, 0 );
    player1.wallColor = SDL_MapRGB( screen_->format, 155, 0, 0 );
    player2.playerColor = SDL_MapRGB( screen_->format, 0, 0, 255 );
    player2.wallColor = SDL_MapRGB( screen_->format, 0, 0, 155 );
}


/***
 * 3. Execution
 ***/

void Tronmoi::run()
{
    SDL_Event event;

    for( ;; ){
        gameGrid.clear();

        /*
            Inicialización de las coordenadas y el tamaño de los cuadrados que representaran a
            los jugadores.
        */
        gameGrid.getPlayerInitialPos( 0, player1.x, player1.y );
        gameGrid.getPlayerInitialPos( 1, player2.x, player2.y );

        /*
        Inicialización del desplazamiento inicial de cada jugador. Ambos empezarán
        desplazándose hacia arriba.
        */
        player1.dx = player2.dx = 0;
        player1.dy = player2.dy = -1;

        /*
            Dibujado de la "cabeza" de cada jugador.
        */
        gameGrid.setPos( player1.x, player1.y, TileType::PLAYER_1 );
        gameGrid.setPos( player2.x, player2.y, TileType::PLAYER_2 );

        player1.dead = player2.dead = false;

        while( !player1.dead && !player2.dead ){
            /*
                Game loop : Se permanecerá en el bucle mientras ambos jugadores permanezcan
                vivos.
            */

            while( SDL_PollEvent( &event ) ){
                /*
                    Consulta de la cola de events.
                */
                if( event.type == SDL_KEYDOWN ){
                    /*
                        event producido al pulsar una tecla. Se analiza si es uno de los
                        botones de dirección de uno de los jugadores y en tal caso se
                        modifica la dirección de su desplazamiento.
                    */
                    switch( event.key.keysym.sym ){
                        /*
                            Botones de dirección del jugador 1.
                        */
                        case SDLK_w:
                            player1.dy = -1;
                            player1.dx = 0;
                        break;
                        case SDLK_s:
                            player1.dy = 1;
                            player1.dx = 0;
                        break;
                        case SDLK_d:
                            player1.dy = 0;
                            player1.dx = 1;
                        break;
                        case SDLK_a:
                            player1.dy = 0;
                            player1.dx = -1;
                        break;

                        /*
                            Botones de dirección del jugador 2.
                        */
                        case SDLK_UP:
                            player2.dy = -1;
                            player2.dx = 0;
                        break;
                        case SDLK_DOWN:
                            player2.dy = 1;
                            player2.dx = 0;
                        break;
                        case SDLK_RIGHT:
                            player2.dy = 0;
                            player2.dx = 1;
                        break;
                        case SDLK_LEFT:
                            player2.dy = 0;
                            player2.dx = -1;
                        break;

                        default:
                            NULL;
                        break;

                    };
                }else if( event.type == SDL_QUIT ){
                    /*
                        event para salir del programa.
                    */
                    exit(0);
                }
            }


            /*
                Se avanzan las coordenadas de ambos jugadores.
            */
            player1.x += player1.dx;
            player1.y += player1.dy;

            player2.x += player2.dx;
            player2.y += player2.dy;


            if( gameGrid.getPos( player1.x, player1.y ) == TileType::EMPTY ){
                gameGrid.setPos( player1.x, player1.y, TileType::PLAYER_1 );
                gameGrid.setPos( player1.x - player1.dx, player1.y - player1.dy, TileType::PLAYER_1_WALL );
            }else{
                player1.dead = true;
            }

            if( gameGrid.getPos( player2.x, player2.y ) == TileType::EMPTY ){
                gameGrid.setPos( player2.x, player2.y, TileType::PLAYER_2 );
                gameGrid.setPos( player2.x - player2.dx, player2.y - player2.dy, TileType::PLAYER_2_WALL );
            }else{
                player2.dead = true;
            }


            /*
                Se actualiza la screen_ y se espera 0.250 segundos.
            */
            gameGrid.draw( player1.playerColor,
                           player1.wallColor,
                           player2.playerColor,
                           player2.wallColor );
            SDL_Flip( screen_ );
            SDL_Delay( 50 );
        }

        SDL_FillRect( screen_, NULL, 0 );
        displayResult();
    }
}


void Tronmoi::displayResult(){
    SDL_Event event;

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
    if( player1.dead && player2.dead ){
        I_Victoria = SDL_LoadBMP( "../share/tronmoi/img/Empate.bmp" );
    }else if( player1.dead ){
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
        Blitting y refresco de la screen_.
    */
    SDL_BlitSurface( I_Victoria, NULL, screen_, &C_Victoria );
    SDL_Flip( screen_ );
    SDL_Delay( 1000 );
    while( SDL_PollEvent( &event ) ){
        if( event.type == SDL_QUIT ){
            exit(0);
        }
    }

    SDL_BlitSurface( I_Recomenzar, NULL, screen_, &C_Recomenzar );
    SDL_Flip( screen_ );

    /*
        Liberación de las superficies;
    */
    SDL_FreeSurface( I_Victoria );
    SDL_FreeSurface( I_Recomenzar );

    /*
        Se permanece en la screen_ de resultado mientras no se pulse una tecla o no se cierre
        el juego.
    */
    while( !Salir_Bucle ){
        while( SDL_PollEvent( &event ) ){
            if( event.type == SDL_KEYDOWN ){
                Salir_Bucle = true;
            }else if( event.type == SDL_QUIT ){
                exit( 0 );
            }
        }
    }

}
