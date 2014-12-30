#include "game_grid.hpp"

/***
 * 1. Construction
 ***/

GameGrid::GameGrid( unsigned int rows, unsigned int columns ) :
    MATRIX_SIZE_( rows * columns ),
    matrix_( MATRIX_SIZE_, TileType::EMPTY )
{}


/***
 * 3. Getters
 ***/

TileType GameGrid::getPos( unsigned int row, unsigned int column )
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
