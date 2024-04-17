#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include "Tetrominoes.hpp"

// Define some constants of the playfield
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BLOCK_SIZE = 16;
const int PLAYFIELD_WIDTH_BLOCKS = 10;
const int PLAYFIELD_HEIGHT_BLOCKS = 20;
const int PLAYFIELD_SEPERATOR_THICKNESS = 6;
const int PLAYFIELD_SEPERATOR_MARGIN = (SCREEN_WIDTH/2) -((PLAYFIELD_WIDTH_BLOCKS * BLOCK_SIZE)/2) - PLAYFIELD_SEPERATOR_THICKNESS;

class Playfield
{
public:
    Playfield(Tetrominoes *tetrominoes);
    ~Playfield();

    int GetPlayfieldPositionX(const int posX);
    int GetPlayfieldPositionY(const int posY);
    TetrominoType GetPlayfieldState(const int posX, const int posY);
    bool IsLegalMove(const TetrominoType tetrominoType, const int posX, const int posY, const int rotation);
    void StoreTetromino(const TetrominoType tetrominoType, const int posX, const int posY, const int rotation);
    void DeleteCompletedLines();
    bool IsGameOver();

private:
    TetrominoType _playfield[PLAYFIELD_WIDTH_BLOCKS][PLAYFIELD_HEIGHT_BLOCKS];
    Tetrominoes *_tetrominoes;

    void InitializePlayfield();
    void DeleteLine(const int posY);


};

#endif