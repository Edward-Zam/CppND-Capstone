#include "Playfield.h"

Playfield::Playfield(Tetrominoes *tetrominoes)
{
    _tetrominoes = tetrominoes;

    InitializePlayfield();
}

Playfield::~Playfield()
{
}

int Playfield::GetPlayfieldPositionX(const int posX)
{
    return (posX * BLOCK_SIZE) + PLAYFIELD_SEPERATOR_MARGIN + PLAYFIELD_SEPERATOR_THICKNESS + 1;
}

int Playfield::GetPlayfieldPositionY(const int posY)
{
    return (posY * BLOCK_SIZE) + SCREEN_HEIGHT - (PLAYFIELD_HEIGHT_BLOCKS * BLOCK_SIZE) + 1;
}

TetrominoType Playfield::GetPlayfieldState(const int posX, const int posY)
{
    return (TetrominoType)_playfield[posX][posY];
}

// We want to check each cell of the playfield and compare it with the corresponding 5x5 area of the board
// against the board limits and stored tetrominoes
bool Playfield::IsLegalMove(const TetrominoType tetrominoType, const int posX, const int posY, const int rotation)
{
    int playfieldPosX = posX;
    int playfieldPosY = posY;

    for (int i = 0; i < TETROMINO_MAX_SIZE; i++)
    {
        playfieldPosY = posY;
        for (int j = 0; j < TETROMINO_MAX_SIZE; j++)
        {

            if (_tetrominoes->GetTetrominoType(tetrominoType, j, i, rotation) != 0)
            {
                // Check against playfield limits
                if (playfieldPosX < 0 || playfieldPosX > PLAYFIELD_WIDTH_BLOCKS - 1 || playfieldPosY > PLAYFIELD_HEIGHT_BLOCKS -1 )
                {
                    return false;
                }

                // Check against stored tetrominoes
                if (posY >= 0 && _playfield[playfieldPosX][playfieldPosY] != EMPTY)
                {
                    return false;
                }
            }
            playfieldPosY++;
        }
        playfieldPosX++;
    }

    // All checks passed, return true
    return true;
}

void Playfield::StoreTetromino(const TetrominoType tetrominoType, const int posX, const int posY, const int rotation)
{
    int playfieldPosX = posX;
    int playfieldPosY = posY;

    for (int i = 0; i < TETROMINO_MAX_SIZE; i++ )
    {
        playfieldPosY = posY;
        for (int j = 0; j < TETROMINO_MAX_SIZE; j++)
        {
            if(_tetrominoes->GetTetrominoType(tetrominoType, j, i, rotation) != 0)
            {
                _playfield[playfieldPosX][playfieldPosY] = tetrominoType;
            }
            playfieldPosY++;
        }
        playfieldPosX++;
    }
}

void Playfield::DeleteCompletedLines()
{
    for (int i = 0; i < PLAYFIELD_HEIGHT_BLOCKS; i++)
    {
        for (int j = 0; j < PLAYFIELD_WIDTH_BLOCKS; j++)
        {
            if (_playfield[j][i] == EMPTY)
            {
                break;
            }
            else if (j == PLAYFIELD_WIDTH_BLOCKS - 1)
            {
                DeleteLine(i);
            }
        }
    }
}

bool Playfield::IsGameOver()
{
    for (int i = 0; i < PLAYFIELD_WIDTH_BLOCKS; i++)
    {
        if(_playfield[i][0] != EMPTY)
        {
            return true;
        }
    }

    return false;
}

void Playfield::InitializePlayfield()
{
    for (int i = 0; i < PLAYFIELD_WIDTH_BLOCKS; i++)
    {
        for (int j = 0; j < PLAYFIELD_HEIGHT_BLOCKS; j++)
        {
            _playfield[i][j] = EMPTY;
        }
    }
}

void Playfield::DeleteLine(const int posY)
{
    for (int i = posY; i > 0; i++)
    {
        for (int j = 0; j < PLAYFIELD_WIDTH_BLOCKS; j++)
        {
            _playfield[j][i] = _playfield[j][i-1];
        }
    }
}