// TODO: Add license note.

#ifndef GAME_GRID_HPP
#define GAME_GRID_HPP

#include <vector>
#include <SDL/SDL.h>

enum class TileType {
    EMPTY,
    PLAYER_1,
    PLAYER_2
};

class GameGrid
{
    public:
        /***
         * 1. Construction
         ***/
        GameGrid( unsigned int rows, unsigned int columns );


        /***
         * 2. Destruction
         ***/
        ~GameGrid() = default;


        /***
         * 3. Getters
         ***/
        TileType getPos( unsigned int row, unsigned int column ) const;


        /***
         * 4. Setters
         ***/
        void setPos( unsigned int row, unsigned int column, TileType type );


        /***
         * 5. Drawing
         ***/
        void draw( SDL_Surface* screen, Uint32 playerColor1, Uint32 playerColor2 ) const;


    private:
        const unsigned int MATRIX_SIZE_;
        std::vector< TileType > matrix_;
};

#endif // GAME_GRID_HPP
