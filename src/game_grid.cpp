#include "game_grid.hpp"
#include <stdexcept>

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

TileType GameGrid::getPos( int x, int y ) const
{
    if( ( x >= 0 ) && ( static_cast<unsigned int>( x ) < MATRIX_SIZE_ ) &&
        ( y >= 0 ) && ( static_cast<unsigned int>( y ) < MATRIX_SIZE_ ) ){
        return matrix_.at( y * MATRIX_SIZE_ + x );
    }else{
        return TileType::INVALID;
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

void GameGrid::draw( SDL_Surface *screen,
                     Uint32 playerColor1,
                     Uint32 playerWallColor1,
                     Uint32 playerColor2,
                     Uint32 playerWallColor2 ) const
{
    SDL_Rect rect = { 0, 0, TILE_SIZE, TILE_SIZE };
    unsigned int row, column;

    const Uint32 BACKGROUND_COLOR =
            SDL_MapRGB( screen->format, 200, 200, 200 );
    SDL_FillRect( screen, nullptr, BACKGROUND_COLOR );

    for( row = 0; row < MATRIX_SIZE_; row++ ){
        for( column = 0; column < MATRIX_SIZE_; column++ ){
            rect.w = TILE_SIZE;
            rect.h = TILE_SIZE;
            switch( getPos( column, row ) ){
                case TileType::EMPTY:
                    SDL_FillRect( screen, &rect, 0 );
                break;
                case TileType::PLAYER_1:
                    SDL_FillRect( screen, &rect, playerColor1 );
                break;
                case TileType::PLAYER_1_WALL:
                    SDL_FillRect( screen, &rect, playerWallColor1 );
                break;
                case TileType::PLAYER_2:
                    SDL_FillRect( screen, &rect, playerColor2 );
                break;
                case TileType::PLAYER_2_WALL:
                    SDL_FillRect( screen, &rect, playerWallColor2 );
                break;
                case TileType::INVALID:
                    throw std::runtime_error( "Invalid tile!" );
                break;
            }

            rect.x += TILE_SIZE;
        }
        rect.x = 0;
        rect.y += TILE_SIZE;
    }
}
