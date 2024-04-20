#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include "Tetrominoes.h"

// Define some constants of the playfield
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BLOCK_SIZE = 16;
const int PLAYFIELD_COLUMNS = 10;
const int PLAYFIELD_ROWS = 20; // SRS specifies 20 rows + 2 hidden rows, omit hidden rows for now
const int PLAYFIELD_SEPERATOR_THICKNESS = 6;
const int PLAYFIELD_SEPERATOR_MARGIN = (SCREEN_WIDTH/2) -((PLAYFIELD_COLUMNS * BLOCK_SIZE)/2) - PLAYFIELD_SEPERATOR_THICKNESS;

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
    TetrominoType _playfield[PLAYFIELD_COLUMNS][PLAYFIELD_ROWS];
    Tetrominoes *_tetrominoes;

    void InitializePlayfield();
    void DeleteLine(const int posY);


};

#endif