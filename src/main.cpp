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
#include <SDL/SDL_ttf.h>

/*                             Constantes y variables globales                                 */
/***********************************************************************************************/

SDL_Surface *screen_;
SDL_Event event;


/*                                Definiciones de funciones                                    */
/***********************************************************************************************/

int main( int argc, char *argv[] )
{
    (void)( argc );
    (void)( argv );

    // Initialize SDL.
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        throw std::runtime_error( SDL_GetError() );
    }
    atexit( SDL_Quit );

    // Initialize SDL_ttf
    if( TTF_Init() < 0 ){
        throw std::runtime_error( TTF_GetError() );
    }
    atexit( TTF_Quit );

    // Set main window.
    screen_ = SDL_SetVideoMode( 800, 600, 32, SDL_ANYFORMAT );
    SDL_WM_SetCaption( "TRONMOI", NULL );

    // Run the game
    Tronmoi tronmoi( screen_ );
    tronmoi.run();

    return 0;
}
