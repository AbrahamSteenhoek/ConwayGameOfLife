/*-------------------------------------------------------------------------------------/
Abraham Steenhoek

**gameoflife.cpp**
    contains defined methods for gameoflife model
CPS 210 - Program 1: Game of Life
9/23/2017
4.5 hours
/-------------------------------------------------------------------------------------*/
#include "gameoflife.h"


using namespace std;

//Constructor:
//Sets all cells to false by default
GameOfLife::GameOfLife (unsigned int _r, unsigned int _c) : row(_r), col(_c) {
    board = new bool *[row];
    for (int i = 0; i < row; i++) {
        board[i] = new bool [col];
        for(int j = 0; j < col; j++) {
            // zero out the board
            board[i][j] = false;
        }
    }
}

GameOfLife::~GameOfLife() {
    for (int i = 0; i < row; i++) {
        delete [] board[i];
    }
    delete [] board;
}

/* 
Method: print()
        -Prints the status of a given game model in ASCII on the terminal.
        -Uses std::cout for output stream.
        -Changes nothing.
Returns: void
*/
void GameOfLife::print() {
    cout << endl;

    for (int i = 0; i < this->height(); i++) {
        cout << "| ";
        for (int j = 0; j < this->width(); j++) {
            if (this->get(i,j) == true)
                cout << "X";
            else   
                cout << " ";
        }
        cout << " |" << endl;
    }
}

/* 
Method: randomize()
        -randomizes the values of every cell, creating a random grid
        -sets using operator[]
Returns: void
*/
void GameOfLife::randomize() {

    srand (time(NULL));

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            board[i][j] = rand() % 2;
        }
    }
}

/*
Method: get()
        -indexes the board with int r, and int c using operator[][]
        -throws out_of_range exception when going out of bounds
Returns: bool
        -state of the current cell, indexed by r, c
*/
bool GameOfLife::get(int r, int c) {
    if(r < 0 || c < 0 || r >= row || c >= col) {
        throw out_of_range("out of range");
    }
    else
        return board[r][c];
}

/*
Method: checkCell()
        -Counts the amount of live neighbors to a given cell inside of the matrix
        -Nested if's used.  Lots of them
Returns: unsigned int
        -The count of alive neighbors to a given cell
*/
unsigned int GameOfLife::checkCell(unsigned int r, unsigned int c) {
    // count of living neighbors to a cell
    int nCount = 0;
                  //  L, Up,  R, Dn  LU, RU, LD, RD
    int xvals[8] = { -1,  0,  1,  0, -1, -1,  1, 1};
    int yvals[8] = {  0, -1,  0,  1, -1,  1, -1, 1};

    for (int i = 0; i < 8; i++) {
        try {
            nCount = (get(r + xvals[i], c + yvals[i])) ? nCount + 1 : nCount;
        }
        catch (out_of_range &ex) {
            //do nothing, go to next neighbor
        }
    }
    
    return nCount;
}