#include <chrono>
#include <future>
#include <random>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Game.h"

Game::Game(Playfield * playfield, Tetrominoes * tetrominoes, Renderer * renderer) :
_playfield(playfield),
_tetrominoes(tetrominoes),
_renderer(renderer)
{
    InitializeGame();
}

Game::~Game()
{
}

void Game::DrawAll()
{
    DrawPlayfield();
    DrawStoredTetrominoes();
    DrawTetromino(CurrentTetromino, CurrentTetrominoPosX, CurrentTetrominoPosY, CurrentTetrominoRotation);
    DrawFuturePlacement();
    DrawTetromino(_nextTetromino, _nextTetrominoPosX, _nextTetrominoPosY, _nextTetrominoRotation);

}

void Game::CreateTetromino()
{
    CurrentTetromino = _nextTetromino;
    CurrentTetrominoRotation = _nextTetrominoRotation;
    CurrentTetrominoPosX = _tetrominoes->GetTetrominoInitialPositionX(CurrentTetromino) + (PLAYFIELD_COLUMNS / 2) -1;
    CurrentTetrominoPosY = _tetrominoes->GetTetrominoInitialPositionY(CurrentTetromino);

    _nextTetromino = (TetrominoType)GetRandomInt(I, Z);
}

void Game::RotateTetromino()
{
    int nextRotation = (CurrentTetrominoRotation + 1) % 4;

    // Rotate normally if possible    
    if ( _playfield->IsLegalMove(CurrentTetromino, CurrentTetrominoPosX, CurrentTetrominoPosY, nextRotation) )
    {
        CurrentTetrominoRotation = nextRotation;
    }
    // Simple wall kick, check if we can move tetronimo +/- 1 for a succesful rotation. If not then don't rotate
    else if ( _playfield->IsLegalMove(CurrentTetromino, CurrentTetrominoPosX - 1, CurrentTetrominoPosY, nextRotation) )
    {
        CurrentTetrominoPosX--;
        CurrentTetrominoRotation = nextRotation;
    }
    else if ( _playfield->IsLegalMove(CurrentTetromino, CurrentTetrominoPosX + 1, CurrentTetrominoPosY, nextRotation) )
    {
        CurrentTetrominoPosX++;
        CurrentTetrominoRotation = nextRotation;
    }
}

void Game::DropTetromino()
{
    int dropDistance = GetTetrominoMaxPosY();
    CurrentTetrominoPosY += dropDistance;
    _playfield->StoreTetromino(CurrentTetromino, CurrentTetrominoPosX, CurrentTetrominoPosY, CurrentTetrominoRotation);
    
    // We've dropped the tetromino down instantly, perform checks and create a new one
    _playfield->DeleteCompletedLines();
    CreateTetromino();
}

void Game::PauseGame()
{
    // Toggle the game state
    this->_isPaused = !this->_isPaused;
    // Continue if paused
    this->Resume();
}

void Game::EndGame()
{
    std::thread resume_timer(&Game::WaitTime, this);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    resume_timer.detach();
    std::unique_lock<std::mutex> lock(_pauseMutex);

    std::cout << "Game Over!" << std::endl;
}

int Game::GetRandomInt(const int min, const int max)
{
    return min + (rand() % static_cast<int>(max-min + 1));
}

void Game::InitializeGame()
{
    // Random-like numbers are sufficient here, we'll generate the seed at runtime
    srand(time(NULL));

    _nextTetromino = (TetrominoType)GetRandomInt(I, Z);
    _nextTetrominoPosX = PLAYFIELD_COLUMNS + 5;
    _nextTetrominoPosY = 5;
    _nextTetrominoRotation = 0; // All tetrominoes spawn horizontally per the SRS (Tetris Guideline)

    CreateTetromino();
}

Color Game::GetTetrominoTypeColor(const TetrominoType tetrominoType)
{
    switch (tetrominoType)
    {
        case I:
            return CYAN;
        case J:
            return BLUE;
        case L:
            return ORANGE;
        case O:
            return YELLOW;
        case S:
            return GREEN;
        case T:
            return PURPLE;
        case Z:
            return RED;
        default:
            return GRAY;
    }
}

int Game::GetTetrominoMaxPosY()
{
    // Find the lowest position the tetromino can go
    int y = 0;
    while ( _playfield->IsLegalMove(CurrentTetromino, CurrentTetrominoPosX, CurrentTetrominoPosY + y, CurrentTetrominoRotation) )
    {
        y++;
    }

    return y-1;
}

void Game::DrawTetromino(const TetrominoType tetrominoType, const int posX, const int posY, const int rotation)
{
    Color color = GetTetrominoTypeColor(tetrominoType);
    int pixelX = _playfield->GetPlayfieldPositionX(posX);
    int pixelY = _playfield->GetPlayfieldPositionY(posY) - 1;

    for (int i = 0; i < TETROMINO_MAX_SIZE; i++)
    {
        for (int j = 0; j < TETROMINO_MAX_SIZE; j++)
        {
            if (_tetrominoes->GetTetrominoType(tetrominoType, j, i, rotation) != 0)
            {
                    _renderer->DrawRectangle(pixelX + (i*BLOCK_SIZE), 
                                        pixelY + (j*BLOCK_SIZE), 
                                        BLOCK_SIZE -1,
                                        BLOCK_SIZE - 1, 
                                        color);
            }
        }
    }
}

void Game::DrawFuturePlacement()
{
    int distanceToBottom = GetTetrominoMaxPosY();
    Color color = GRAY;
    int pixelX = _playfield->GetPlayfieldPositionX(CurrentTetrominoPosX);
    int pixelY = _playfield->GetPlayfieldPositionY(CurrentTetrominoPosY + distanceToBottom);

    for ( int i = 0; i < TETROMINO_MAX_SIZE; i++ )
    {
        for ( int j = 0; j < TETROMINO_MAX_SIZE; j++ ) 
        {
            if ( _tetrominoes->GetTetrominoType(CurrentTetromino, j, i, CurrentTetrominoRotation) != 0 )
            {
                _renderer->DrawRectangleOutline(pixelX + (i*BLOCK_SIZE),
                                                pixelY + (j*BLOCK_SIZE), 
                                                BLOCK_SIZE - 1, 
                                                BLOCK_SIZE - 1, 
                                                color);
            }
        }
    }
    
}

void Game::DrawPlayfield()
{
    _renderer->DrawRectangle(PLAYFIELD_SEPERATOR_MARGIN,
                            SCREEN_HEIGHT - (PLAYFIELD_ROWS * BLOCK_SIZE),
                            PLAYFIELD_SEPERATOR_THICKNESS,
                            PLAYFIELD_ROWS * BLOCK_SIZE,
                            GRAY);

    _renderer->DrawRectangle(SCREEN_WIDTH - PLAYFIELD_SEPERATOR_MARGIN - PLAYFIELD_SEPERATOR_THICKNESS,
                            SCREEN_HEIGHT - (PLAYFIELD_ROWS * BLOCK_SIZE),
                            PLAYFIELD_SEPERATOR_THICKNESS,
                            PLAYFIELD_ROWS * BLOCK_SIZE,
                            GRAY);
}

void Game::DrawStoredTetrominoes()
{
    TetrominoType  playfieldState;
    Color color;

    for ( int i = 0; i < PLAYFIELD_COLUMNS; i++ )
    {
        for ( int j =0; j<  PLAYFIELD_ROWS; j++ )
        {
            playfieldState = _playfield->GetPlayfieldState(i, j);
            if ( playfieldState != EMPTY )
            {
                color = GetTetrominoTypeColor(playfieldState);
                _renderer->DrawRectangle(PLAYFIELD_SEPERATOR_MARGIN + PLAYFIELD_SEPERATOR_THICKNESS + (i * BLOCK_SIZE),
                                        SCREEN_HEIGHT - (PLAYFIELD_ROWS * BLOCK_SIZE) + (j * BLOCK_SIZE),
                                        BLOCK_SIZE - 1,
                                        BLOCK_SIZE - 1,
                                        color);
            }
        }
    }
}

void Game::Resume()
{
    if (!this->_isPaused)
    {
        return;
    }

    std::thread resume_timer(&Game::WaitTime, this);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    resume_timer.detach();
    std::unique_lock<std::mutex> lock(_pauseMutex);

}

void Game::WaitTime()
{
    std::cout << "Waiting for requesting action after 1s" << std::endl;
    std::unique_lock<std::mutex> lock(_pauseMutex);
    // Notify for resuming game
    _cv.notify_one();
    std::this_thread::sleep_for(std::chrono::seconds(1));

}
