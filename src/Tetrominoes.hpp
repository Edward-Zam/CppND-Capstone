#ifndef TETROMINOES_H
#define TETROMINOES_H

// Each tetromino is made up of 4 squares but I'm setting the max to 5 so that
// we have a center to which to rotate about. 
const int TETROMINO_MAX_SIZE = 5;

enum TetrominoType
{
    //SQUARE, I, L, L_MIRRORED, Z, Z_MIRRORED, T, UNDEFINED
    I, J, L, O, S, T, Z, UNDEFINED
};

class Tetrominoes
{
    public:
    Tetrominoes();
    ~Tetrominoes();

    // Getters
    int GetTetrominoType(const TetrominoType tetrominoType, const int idx, const int idy, const int rotation);
    int GetTetrominoInitialPositionX(const TetrominoType tetrominoType, const int rotation);
    int GetTetrominoInitialPositionY(const TetrominoType tetrominoType, const int rotation);
};

#endif

