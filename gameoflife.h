/*-------------------------------------------------------------------------------------/
Abraham Steenhoek

**gameoflife.h**
    contains declaration for gameoflife model
CPS 210 - Program 1: Game of Life
9/23/2017
4.5 hours
/-------------------------------------------------------------------------------------*/


#include <iostream>
#include <array>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h> 
#include <exception>


class GameOfLife {
    // using 2D C-Style array for matrix
    bool **board;
    const unsigned int row;
    const unsigned int col;
    
    public:

    GameOfLife (unsigned int _r, unsigned int _c);
    
    const int height() { return row; }
    const int width() { return col; }

    // get method implemented due to bugs from RETRIEVING values using overloaded operator
    bool get(int r, int c);
    void set(int r, int c, bool stat) { board[r][c] = stat; }

    void randomize();
    unsigned int checkCell(unsigned int r, unsigned int c);
    
    void print();

    /*
    Method:
        -Overloaded [] to index the matrix like a 2D array (square[][])
    Returns:
        -Pointer to appropriate row
        -From there, the user can derefrence returned pointer again to get the value of the appropriate column
    */
    bool* operator[](int row) { return board[row]; }
    
    ~GameOfLife();
    
};