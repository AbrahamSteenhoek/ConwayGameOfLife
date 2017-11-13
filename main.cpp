/*-------------------------------------------------------------------------------------/
Abraham Steenhoek

**main.cpp**
    contains defined methods outside of gameoflife class used to run the game
CPS 210 - Program 1: Game of Life
9/23/2017
4.5 hours
/-------------------------------------------------------------------------------------*/


#include <iostream>
#include <array>
#include "gameoflife.h"
#include <string>
#include <chrono>
#include <thread>

using namespace std;

/*
Method: cycle
        -Runs the game of life using two matrices: an 'old' board, and the 'new' board 
        representing the appropriatechanges made
        -Runs recursively in order to avoid unnecessary while statements
        -Passes by reference in order to avoid duplicating values
*/
void cycle(GameOfLife &board1, GameOfLife &board2, int lifetime) {
    if (lifetime <= 0)
        return;

    //std::this_thread::sleep_for (std::chrono::seconds(1));

    board1.print();

    for (int i = 0; i < board2.height(); i++) {
        for (int j = 0; j < board2.width(); j++) {
            board2.set(i,j,false);
        }
    }

    for (int i = 0; i < board1.height(); i++) {
        for (int j = 0; j < board1.width(); j++) {
            if (board1.get(i,j) == true) {
                // death if 0-1 or > 3
                if (board1.checkCell(i,j) <= 1 || board1.checkCell(i,j) >= 4) {
                    board2[i][j] = false;
                }
                else
                    board2[i][j] = true;
            }
            else {
                if (board1.checkCell(i,j) == 3) {
                    board2[i][j] = true;
                }
            }
        }
    }

    cout << endl;

    cycle (board2, board1, lifetime - 1);
}

/*
Method: Unit Test
        -runs tests on the critical functions inside GameOfLife
        -creates several sample tables to run various test cases, specifically ones on odd-shaped rectangle matrices
        -uses std::cout to display results of specific tests.  To shut off output from unit tests, comment out line 89 
Returns:
        -void
*/
void unitTests() {
    cout << "UNIT TESTS" << endl;

    // testing [1][1] matrix
    GameOfLife game1(1,1);
    cout << "height: " << game1.height() << "\nwidth: " << game1.width() << endl;
    cout << "test 1x1 neighbors: " << game1.checkCell(0,0) << endl;

    // testing function checkCell()
    // testing ability to change cells with overloaded operator[]
    GameOfLife testGame(3,3);
    GameOfLife testGame2(3,3);
    testGame[1][0] = true;
    testGame[1][1] = true;
    testGame[1][2] = true;
    cout << "test 3x3 neighbors: " << testGame.checkCell(1,1) << endl;
    // should alternate pattern
    cycle(testGame, testGame2, 4);

    // test case for single column
    GameOfLife oneColumn(7,1);
    oneColumn[4][0] = true;
    oneColumn[6][0] = true;
    cout << "test oneColumn neighbors: " << oneColumn.checkCell(5,0) << endl;
    // test case for single row
    GameOfLife oneRow(1,7);
    oneRow[0][4] = true;
    oneRow[0][6] = true;
    cout << "test oneRow neighbors: " << oneRow.checkCell(0,5) << endl;
    

}

int main () {
    // comment out to remove testing output
    unitTests();
    
    unsigned int height;
    unsigned int width;
    unsigned int lifetime;
    cout << "Matrix height:" << endl;
    cin >> height;
    cout << "Matrix width:" << endl;
    cin >> width;
    cout << "Lifetime:" << endl;
    cin >> lifetime;

    GameOfLife board1(height, width);
    GameOfLife board2(height, width);

    board1.randomize();
    cycle(board1, board2, lifetime);

    return 0;
}