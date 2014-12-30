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

#ifndef TRONMOI_HPP
#define TRONMOI_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "game_grid.hpp"

struct Player {
    int x, y;
    Sint8 dx, dy;
    Uint32 playerColor;
    Uint32 wallColor;

    bool dead;
};

class Tronmoi
{
    public:
        /***
         * 1. Construction
         ***/
        Tronmoi( SDL_Surface* screen );


        /***
         * 2. Destruction
         ***/
        ~Tronmoi() = default;


        /***
         * 3. Execution
         ***/
        void run();


    private:
        /***
         * 4. Result displaying
         ***/
        void displayIntroScreen();
        void displayResult();


        /***
         * Attributes
         ***/
        SDL_Surface* screen_;
        Player player1, player2;

        GameGrid gameGrid;

        TTF_Font* textFont_;
};

#endif // TRONMOI_HPP
