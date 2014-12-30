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

        // Initialize players' positions.
        gameGrid.getPlayerInitialPos( 0, player1.x, player1.y );
        gameGrid.getPlayerInitialPos( 1, player2.x, player2.y );

        // Initialize player's velocity.
        player1.dx = player2.dx = 0;
        player1.dy = player2.dy = -1;

        // Place the "head" of every player on the game's grid.
        gameGrid.setPos( player1.x, player1.y, TileType::PLAYER_1 );
        gameGrid.setPos( player2.x, player2.y, TileType::PLAYER_2 );

        // Main loop: keep running as long as both players are alive.
        player1.dead = player2.dead = false;
        while( !player1.dead && !player2.dead ){
            while( SDL_PollEvent( &event ) ){
                // Process user input.
                if( event.type == SDL_KEYDOWN ){
                    switch( event.key.keysym.sym ){
                        // Movement for player 1.
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

                        // Movement for player 2.
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
                    // Exit game.
                    exit( 0 );
                }
            }


            // Update both players.
            player1.x += player1.dx;
            player1.y += player1.dy;
            if( gameGrid.getPos( player1.x, player1.y ) == TileType::EMPTY ){
                gameGrid.setPos( player1.x, player1.y, TileType::PLAYER_1 );
                gameGrid.setPos( player1.x - player1.dx, player1.y - player1.dy, TileType::PLAYER_1_WALL );
            }else{
                player1.dead = true;
            }

            player2.x += player2.dx;
            player2.y += player2.dy;
            if( gameGrid.getPos( player2.x, player2.y ) == TileType::EMPTY ){
                gameGrid.setPos( player2.x, player2.y, TileType::PLAYER_2 );
                gameGrid.setPos( player2.x - player2.dx, player2.y - player2.dy, TileType::PLAYER_2_WALL );
            }else{
                player2.dead = true;
            }

            // Update screen and wait.
            gameGrid.draw( player1.playerColor,
                           player1.wallColor,
                           player2.playerColor,
                           player2.wallColor );
            SDL_Flip( screen_ );
            SDL_Delay( 50 );
        }

        // Display the match's result.
        displayResult();
    }
}


void Tronmoi::displayResult(){
    SDL_Event event;
    SDL_Surface *victorySurface, *restartSurface;
    bool exitLoop = false;

    // TODO: Use a relative path.
    TTF_Font* font =
            TTF_OpenFont( "/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf",
                          30 );
    if( !font ){
        throw std::runtime_error( TTF_GetError() );
    }

    // Create the victory text surface.
    if( player1.dead && player2.dead ){
        const SDL_Color fontColor = { 255, 255, 255, 255 };
        victorySurface =
                TTF_RenderText_Solid( font,
                                      "Draw",
                                      fontColor );
    }else if( player1.dead ){
        const SDL_Color fontColor = { 0, 0, 255, 255 };
        victorySurface =
                TTF_RenderText_Solid( font,
                                      "Player 2 wins",
                                      fontColor );
    }else{
        const SDL_Color fontColor = { 255, 0, 0, 255 };
        victorySurface =
                TTF_RenderText_Solid( font,
                                      "Player 1 wins",
                                      fontColor );
    }
    if( !victorySurface ){
        throw std::runtime_error( TTF_GetError() );
    }

    // Create a surface with the text "press any key to restart".
    const SDL_Color fontColor = { 255, 255, 255, 255 };
    restartSurface = TTF_RenderText_Solid( font,
                                           "Press any key to restart",
                                           fontColor );
    if( !restartSurface ){
        throw std::runtime_error( TTF_GetError() );
    }

    // Display the victory surface and wait one second.
    SDL_FillRect( screen_, NULL, 0 );
    SDL_Rect victoryRect = {
        ( ( screen_->w - victorySurface->w ) >> 1 ),
        ( ( screen_->h - victorySurface->w ) >> 1 ),
        victorySurface->w,
        victorySurface->h
    };
    SDL_BlitSurface( victorySurface, NULL, screen_, &victoryRect );
    SDL_Flip( screen_ );
    SDL_Delay( 1000 );
    while( SDL_PollEvent( &event ) ){
        if( event.type == SDL_QUIT ){
            exit(0);
        }
    }

    // Display the restart surface.
    SDL_Rect restartRect =
    {
        ( ( screen_->w - restartSurface->w ) >> 1 ),
        ( screen_->h - restartSurface->h ),
        restartSurface->w,
        restartSurface->h
    };
    SDL_BlitSurface( restartSurface, NULL, screen_, &restartRect );
    SDL_Flip( screen_ );

    // Free resources.
    SDL_FreeSurface( victorySurface );
    SDL_FreeSurface( restartSurface );

    // Wait until user presses any key or exits the game.
    while( !exitLoop ){
        while( SDL_PollEvent( &event ) ){
            if( event.type == SDL_KEYDOWN ){
                exitLoop = true;
            }else if( event.type == SDL_QUIT ){
                exit( 0 );
            }
        }
    }

}
