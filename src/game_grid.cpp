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

#include "game_grid.hpp"
#include <stdexcept>

const unsigned int TILE_SIZE = 20;

/***
 * 1. Construction
 ***/

GameGrid::GameGrid( SDL_Surface *screen, unsigned int size ) :
    screen_( screen ),
    MATRIX_SIZE_( size ),
    matrix_( MATRIX_SIZE_ * MATRIX_SIZE_, TileType::EMPTY )
{
    if( size * TILE_SIZE > static_cast< unsigned int>( screen_->w ) ||
        size * TILE_SIZE > static_cast< unsigned int>( screen_->h ) ){
        throw std::runtime_error( "Game's grid is bigger than screen!" );
    }
}


/***
 * 3. Getters
 ***/

TileType GameGrid::getPos( int x, int y ) const
{
    if( ( x >= 0 ) && ( static_cast<unsigned int>( x ) < MATRIX_SIZE_ ) &&
        ( y >= 0 ) && ( static_cast<unsigned int>( y ) < MATRIX_SIZE_ ) ){
        return matrix_.at( y * MATRIX_SIZE_ + x );
    }else{
        return TileType::INVALID;
    }
}

void GameGrid::getPlayerInitialPos( unsigned int player, int &x, int &y ) const
{
    if( player == 0 ){
        x = MATRIX_SIZE_ / 3;
        y = MATRIX_SIZE_ >> 1;
    }else{
        x = MATRIX_SIZE_ * 2 / 3;
        y = MATRIX_SIZE_ >> 1;
    }
}


/***
 * 4. Setters
 ***/

void GameGrid::setPos( int x, int y, TileType type )
{
    matrix_.at( y * MATRIX_SIZE_ + x ) = type;
}


void GameGrid::clear()
{
    for( TileType& tile : matrix_ ){
        tile = TileType::EMPTY;
    }
}


/***
 * 5. Drawing
 ***/

void GameGrid::draw( Uint32 playerColor1,
                     Uint32 playerWallColor1,
                     Uint32 playerColor2,
                     Uint32 playerWallColor2 ) const
{
    SDL_Rect rect = {
        static_cast< Sint16 >( ( screen_->w - MATRIX_SIZE_ * TILE_SIZE ) >> 1 ),
        static_cast< Sint16 >( ( screen_->h - MATRIX_SIZE_ * TILE_SIZE ) >> 1 ),
        TILE_SIZE,
        TILE_SIZE };
    unsigned int row, column;

    const Uint32 BACKGROUND_COLOR =
            SDL_MapRGB( screen_->format, 200, 200, 200 );
    SDL_FillRect( screen_, nullptr, BACKGROUND_COLOR );

    for( row = 0; row < MATRIX_SIZE_; row++ ){
        for( column = 0; column < MATRIX_SIZE_; column++ ){
            rect.w = TILE_SIZE;
            rect.h = TILE_SIZE;
            switch( getPos( column, row ) ){
                case TileType::EMPTY:
                    SDL_FillRect( screen_, &rect, 0 );
                break;
                case TileType::PLAYER_1:
                    SDL_FillRect( screen_, &rect, playerColor1 );
                break;
                case TileType::PLAYER_1_WALL:
                    SDL_FillRect( screen_, &rect, playerWallColor1 );
                break;
                case TileType::PLAYER_2:
                    SDL_FillRect( screen_, &rect, playerColor2 );
                break;
                case TileType::PLAYER_2_WALL:
                    SDL_FillRect( screen_, &rect, playerWallColor2 );
                break;
                case TileType::INVALID:
                    throw std::runtime_error( "Invalid tile!" );
                break;
            }

            rect.x += TILE_SIZE;
        }
        rect.x = ( screen_->w - MATRIX_SIZE_ * TILE_SIZE ) >> 1;
        rect.y += TILE_SIZE;
    }
}
