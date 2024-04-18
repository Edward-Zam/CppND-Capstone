#ifndef GAME_H
#define GAME_H

#include "Renderer.h"
#include "Playfield.h"
#include "Tetrominoes.h"

class Game
{
public:
    Game(Playfield *playfield, Tetrominoes *tetrominoes, Renderer *rendererService);
    ~Game();

    TetrominoType CurrentPiece;
    int CurrentTetrominoPosX;
    int CurrentTetrominoPosY;
    int CurrentTetrominoRotation;

    void DrawAll();
    void CreateTetromino();
    void RotateTetromino();
    void DropTetromino();

private:
    Playfield *_playfield;
    Tetrominoes *_tetrominoes;
    Renderer *_rendererService;

    TetrominoType _nextTetromino;
    int _nextTetrominoPosX;
    int _nextTetrominoPosY;
    int _nextTetrominoRotation;

    int GetRandomInt(const int min, const int max);
    void InitializeGame();
    Color GetTetrominoTypeColor(const TetrominoType tetrominoType);
    int GetTetrominoMaxPosY();
    void DrawPiece(const TetrominoType tetrominoType, const int posX, const int posY, const int rotation);
    void DrawFutureTetromino();
    void DrawPlayfield();
    void DrawStoredTetrominoes();

};

#endif