#ifndef GAME_H
#define GAME_H

#include <condition_variable>
#include <mutex>


#include "Renderer.h"
#include "Playfield.h"
#include "Tetrominoes.h"

class Game
{
public:
    Game(Playfield *playfield, Tetrominoes *tetrominoes, Renderer *renderer);
    ~Game();

    TetrominoType CurrentTetromino;
    int CurrentTetrominoPosX;
    int CurrentTetrominoPosY;
    int CurrentTetrominoRotation;

    void DrawAll();
    void CreateTetromino();
    void RotateTetromino();
    void DropTetromino();
    bool isPaused(){return _isPaused;}
    
    void PauseGame();
    void EndGame();

private:
    Playfield *_playfield;
    Tetrominoes *_tetrominoes;
    Renderer *_renderer;

    TetrominoType _nextTetromino;
    int _nextTetrominoPosX;
    int _nextTetrominoPosY;
    int _nextTetrominoRotation;
    bool _isPaused = false;
    std::mutex _pauseMutex;
    std::condition_variable _cv;

    int GetRandomInt(const int min, const int max);
    void InitializeGame();
    Color GetTetrominoTypeColor(const TetrominoType tetrominoType);
    int GetTetrominoMaxPosY();
    void DrawTetromino(const TetrominoType tetrominoType, const int posX, const int posY, const int rotation);
    void DrawFuturePlacement();
    void DrawPlayfield();
    void DrawStoredTetrominoes();
    void Resume();
    void WaitTime();

};

#endif