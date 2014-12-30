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

#ifndef GAME_GRID_HPP
#define GAME_GRID_HPP

#include <vector>
#include <SDL/SDL.h>

enum class TileType {
    EMPTY,
    PLAYER_1,
    PLAYER_1_WALL,
    PLAYER_2,
    PLAYER_2_WALL,
    INVALID
};

class GameGrid
{
    public:
        /***
         * 1. Construction
         ***/
        GameGrid( SDL_Surface *screen, unsigned int size );


        /***
         * 2. Destruction
         ***/
        ~GameGrid() = default;


        /***
         * 3. Getters
         ***/
        TileType getPos( int x, int y ) const;
        void getPlayerInitialPos( unsigned int player, int& x, int& y ) const;


        /***
         * 4. Setters
         ***/
        void setPos( int x, int y, TileType type );
        void clear();


        /***
         * 5. Drawing
         ***/
        void draw( Uint32 playerColor1,
                   Uint32 playerWallColor1,
                   Uint32 playerColor2,
                   Uint32 playerWallColor2 ) const;


    private:
        SDL_Surface *screen_;

        const unsigned int MATRIX_SIZE_;
        std::vector< TileType > matrix_;
};

#endif // GAME_GRID_HPP
