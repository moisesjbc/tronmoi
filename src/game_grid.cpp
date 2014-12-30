#include "game_grid.hpp"

const unsigned int TILE_SIZE = 20;

/***
 * 1. Construction
 ***/

GameGrid::GameGrid( unsigned int size ) :
    MATRIX_SIZE_( size ),
    matrix_( MATRIX_SIZE_ * MATRIX_SIZE_, TileType::EMPTY )
{}


/***
 * 3. Getters
 ***/

TileType GameGrid::getPos( unsigned int row, unsigned int column ) const
{
    return matrix_.at( column * MATRIX_SIZE_ + row );
}


/***
 * 4. Setters
 ***/

void GameGrid::setPos( unsigned int row, unsigned int column, TileType type )
{
    matrix_.at( column * MATRIX_SIZE_ + row ) = type;
}


/***
 * 5. Drawing
 ***/

void GameGrid::draw( SDL_Surface *screen, Uint32 playerColor1, Uint32 playerColor2 ) const
{
    SDL_Rect rect = { 0, 0, TILE_SIZE, TILE_SIZE };
    unsigned int row, column;

    for( row = 0; row < MATRIX_SIZE_; row++ ){
        for( column = 0; column < MATRIX_SIZE_; column++ ){
            switch( getPos( row, column ) ){
                case TileType::EMPTY:
                    SDL_FillRect( screen, &rect, 0 );
                break;
                case TileType::PLAYER_1:
                    SDL_FillRect( screen, &rect, playerColor1 );
                break;
                case TileType::PLAYER_2:
                    SDL_FillRect( screen, &rect, playerColor2 );
                break;
            }

            rect.x += TILE_SIZE;
        }
        rect.y += TILE_SIZE;
    }
}
