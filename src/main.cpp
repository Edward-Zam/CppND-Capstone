/*
    Tetris Game for C++ NanoDegree Capstone Project
    Edward Zamora
    This game follows the guidelines layed out by the Super Rotation System (SRS) which
    is the current Tetris Guidline standard for how Tetrominoes spawn, behave and look.
    https://tetris.fandom.com/wiki/SRS  
*/

#include <SDL2/SDL.h>

#include "Game.h"
#include "Playfield.h"
#include "Renderer.h"
#include "Tetrominoes.h"

const int FRAME_UPDATE_TIME = 1000; // Update every second (1000ms)

int main(int argc, char * args[])
{
    Renderer renderer;
    Tetrominoes tetrominoes;
    Playfield playfield(&tetrominoes);
    Game game = Game(&playfield, &tetrominoes, &renderer);

    unsigned long frameStart = SDL_GetTicks();
    unsigned long frameDuration;

    while ( !renderer.HasPlayerQuit() && !playfield.IsGameOver() )
    {
        // Don't render if game is paused
        if( !game.isPaused() )
        {
            renderer.ClearScreen();
            game.DrawAll();
            renderer.UpdateScreen();
        }

        // Handle player movement:
        // Left arrow = left, Right arrow = Right, Down arrow = down, Up arrow = Rotate
        // Space = Drop, ESC = quit
        int keyPressed = renderer.GetKeyPress();
        switch (keyPressed)
        {
            case SDLK_LEFT:
                if( !game.isPaused() )
                {   
                    if ( playfield.IsLegalMove(game.CurrentTetromino, game.CurrentTetrominoPosX - 1, game.CurrentTetrominoPosY, game.CurrentTetrominoRotation))
                    {
                        game.CurrentTetrominoPosX--;
                    }
                }
                break;

            case SDLK_RIGHT:
                if( !game.isPaused() )
                {
                    if ( playfield.IsLegalMove(game.CurrentTetromino, game.CurrentTetrominoPosX + 1, game.CurrentTetrominoPosY, game.CurrentTetrominoRotation))
                    {
                        game.CurrentTetrominoPosX++;
                    }
                }
                break;

            case SDLK_DOWN:
                if( !game.isPaused() )
                {
                    if ( playfield.IsLegalMove(game.CurrentTetromino, game.CurrentTetrominoPosX, game.CurrentTetrominoPosY + 1, game.CurrentTetrominoRotation))
                    {
                        game.CurrentTetrominoPosY++;
                    }
                }
                break;

            case SDLK_UP:
                if( !game.isPaused() )
                {
                    game.RotateTetromino();
                }
                break;

            case SDLK_SPACE:
                if( !game.isPaused() )
                {
                    if (playfield.IsGameOver())
                    {
                        break;
                    }
                    game.DropTetromino();
                }
                break;

            case SDLK_p:
                game.PauseGame();
                break;

            case SDLK_ESCAPE:
                // For now just exit. Future update will show end-screen
                game.EndGame();
                return 0;
                break;
        }

        // Automatic movement (only when game is not paused)
        if( !game.isPaused() )
        {
            unsigned long frameEnd = SDL_GetTicks();
            frameDuration = frameEnd - frameStart;
            if ( frameDuration > FRAME_UPDATE_TIME )
            {
                if ( playfield.IsLegalMove(game.CurrentTetromino, game.CurrentTetrominoPosX, game.CurrentTetrominoPosY + 1, game.CurrentTetrominoRotation) )
                {
                    game.CurrentTetrominoPosY++;
                }
                else
                {
                    playfield.StoreTetromino(game.CurrentTetromino, game.CurrentTetrominoPosX, game.CurrentTetrominoPosY, game.CurrentTetrominoRotation);
                    playfield.DeleteCompletedLines();
                    game.CreateTetromino();
                }
                frameStart = SDL_GetTicks();
            }
        }

    }

    return 0;

}
