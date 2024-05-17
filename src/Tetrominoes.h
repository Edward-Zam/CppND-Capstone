#ifndef TETROMINOES_H
#define TETROMINOES_H

// Each tetromino is made up of 4 squares but I'm setting the max to 5 so that
// we have a center to which to rotate about. 
const int TETROMINO_MAX_SIZE = 5;

enum TetrominoType
{
    I, J, L, O, S, T, Z, EMPTY
};

class Tetrominoes
{
    public:
    Tetrominoes();
    ~Tetrominoes();

    // Getters
    int GetTetrominoType(const TetrominoType& tetrominoType, const int& idx, const int& idy, const int& rotation);
    int GetTetrominoInitialPositionX(const TetrominoType& tetrominoType);
    int GetTetrominoInitialPositionY(const TetrominoType& tetrominoType);
};

#endif

