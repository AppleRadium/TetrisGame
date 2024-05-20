#ifndef GAME_H
#define GAME_H

#include <iostream> //function libraries
#include <vector>
#include <algorithm>
#include "windows.h"
using namespace std;

#include "Cell.h" // includes functions and variables from the Cell, Piece, and Board header files
#include "Piece.h"
#include "Board.h"


class Game 
{
private:

    Board board; //board variable
    Piece curr_piece; // current piece variable
    vector<Cell> final_points;
    int linesbuilt; // variable for number of lines built
    int score; // variable for the score
    int speed; // variable for the speed
    int speedCounter; // variable for the 
    int speedCounterincrem = 2; // intital value of the speed incrementor
    int piececount; // number of pieces that have fallen
    int level = 1; // intial value of the level
    bool run; // boolean run variable

public:

    Game(); //constructor
    void controls(); // contains the key bindings for the game controls
    void running(); // main game loop, this contains the main game sequence
    bool blocksland(); // checks for collisions with the floor, wall, or with other pieces

    bool checked_move(enum move_direction dir); // checks if the piece is still able to move
    bool checked_rotate(); // checks if the piece is still able to rotate

    void draw(); // draws the board on the screen
    void refreshall(); //refreshes the final points on the screen

    void ClearScreen(); // function that prevents the screen from rapidly flickering and jumping
    bool game_over(); // bool function that tells whether the conditions for a game over are met or not
    bool regame(); // allows for the game to restarts if the player chooses


};


#endif