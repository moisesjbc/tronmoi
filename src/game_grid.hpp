// TODO: Add license note.

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
