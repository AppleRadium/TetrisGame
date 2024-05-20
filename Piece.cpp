#include "Piece.h"
using namespace std;

Piece::Piece(Cell pos) //defines all the pieces on an x,y grid
    :pos{pos}
{
    srand(time(0)); //uses time to choose a random value
    type = static_cast<piece_type>(rand() % 7); //chooses a random piece out of 7

    if (type == t_piece) // the different pieces are given their shapes using the enum pos variable
        body = { pos, pos.shift_copy(1, 0), pos.shift_copy(-1, 0), pos.shift_copy(0, 1) };
    else if (type == i_piece)
        body = { pos, pos.shift_copy(0, -1), pos.shift_copy(0, 1), pos.shift_copy(0, 2) };
    else if (type == o_piece)
        body = { pos, pos.shift_copy(0, 1), pos.shift_copy(1, 0), pos.shift_copy(1, 1) };
    else if (type == l_piece)
        body = { pos, pos.shift_copy(0, 1), pos.shift_copy(0, -1), pos.shift_copy(1, -1) };
    else if (type == j_piece)
        body = { pos, pos.shift_copy(-1, 0), pos.shift_copy(0, 1), pos.shift_copy(0, 2) };
    else if (type == s_piece)
        body = { pos, pos.shift_copy(-1, 0), pos.shift_copy(0, 1), pos.shift_copy(1, 1) };
    else if (type == z_piece)
        body = { pos, pos.shift_copy(1, 0), pos.shift_copy(0, 1), pos.shift_copy(-1, 1) };
}

void Piece::fall_down() // automatically causes pieces to fall
{
    pos.move(0, -1); //allows piece to continue falling while rotating
    for (auto& point : body) // creates a pointer that points to the address of 'body'
        point.move(0, -1); //move the pieces down automatically -1 y positions during each iteration
}

vector<Cell> Piece::fallenbody() // allows the piece's body to shift downward by creating a copy of it at -1y increments
{
    vector<Cell> next_body;
    for (const auto& point : body) // creates a pointer that does not modify body
        next_body.push_back(point.shift_copy(0, -1)); // uses the push back command and a pointer to point to the -1 y position

    return next_body;
}

void Piece::move(enum move_direction dir) //moves the pieces left or right
{
    pos.move(dir, 0);
    for (auto& point : body)
        point.move(dir, 0);
}

vector<Cell> Piece::movedbody(enum move_direction dir)  // creates the body of the piece after it has been moved
{
    vector<Cell> next_body;
    for (const auto& point : body) // pointer to body
        next_body.push_back(point.shift_copy(dir, 0)); // shifts a copy of the body to the direction of the movement
    return next_body;
}

void Piece::rotate() //rotates the pieces
{
    for (auto& point : body) 
    {
        int point_x = point.get_x() - pos.get_x();
        int point_y = point.get_y() - pos.get_y();
        point.set_coordinate((-1 * point_y) + pos.get_x(), point_x + pos.get_y());
    }
}

vector<Cell> Piece::rotatedbody() //creates the rotated body of the piece
{
    vector<Cell> next_body;
    for (const auto& point : body)
    {
        int point_x = point.get_x() - pos.get_x();
        int point_y = point.get_y() - pos.get_y();
        next_body.push_back(Cell((-1 * point_y) + pos.get_x(), point_x + pos.get_y()));
    }
    return next_body;
}