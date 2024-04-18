#include <stdlib.h>
#include "Game.h"

Game::Game(Playfield * playfield, Tetrominoes * tetrominoes, Renderer * rendererService)
{
}

Game::~Game()
{
}

void Game::DrawAll()
{
}

void Game::CreateTetromino()
{
}

void Game::RotateTetromino()
{
}

void Game::DropTetromino()
{
}

int Game::GetRandomInt(const int min, const int max)
{
return 0;
}

void Game::InitializeGame()
{
}

Color Game::GetTetrominoTypeColor(const TetrominoType tetrominoType)
{
return Color();
}

int Game::GetTetrominoMaxPosY()
{
    return 0;
}

void Game::DrawPiece(const TetrominoType tetrominoType, const int posX, const int posY, const int rotation)
{
}

void Game::DrawFutureTetromino()
{

}

void Game::DrawPlayfield()
{

}

void Game::DrawStoredTetrominoes()
{
    
}
