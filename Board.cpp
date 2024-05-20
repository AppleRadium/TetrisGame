#include "Board.h"

Board::Board(int width, int height) //constructor
    :width{ width }, height{ height }
{
    for (int i{ 0 }; i < width; i++)
        for (int j{ 0 }; j < height; j++)
            all_points.push_back(Cell(i, j));

    set_border();
}

void Board::refresh() // sets all recently fallen blocks or tiles to new built tiles
{ //refreshes the board
    set_border();
    for (auto& all_pnt : all_points) // auto pointer that points to all tiles
        for (auto built_pnt : built_points) //sets all built points in place
        {
            if (all_pnt == built_pnt)
            {
                all_pnt = built_pnt;  //seting the char of all_pnt to built pnt
            }
        }
}

void Board::insert_to_built_points(vector<Cell> insert_points) 
{
    built_points.insert(built_points.end(), insert_points.begin(), insert_points.end());
    
}

void Board::set_border() //creates the board's design
{
    for (auto& point : all_points) // points to all points on the board
    {
        if (point.get_x() == 1 || point.get_x() == width - 2) // sets the graphical design of the board by assigning characters to different x and y values
            point.set_type('!');
        else if (point.get_y() == 1)
            point.set_type('=');
        else if (point.get_x() == 0)
            point.set_type('<');
        else if (point.get_x() == width - 1)
            point.set_type('>');
        else if (point.get_y() == 0)
            point.set_type('v');
        else
            point.set_type('.');
    }
}

int Board::remove_row() //removes rows whenever they are filled
{
    int removed_rows{ 0 }; // initialized to zero
    int i{ 1 }; // initializes i to 1
    while (i < height)  // while i is greater than height
    {


        int built_points_count = count_if(built_points.begin(), built_points.end(), [i](const Cell& point) 
            {
            return (point.get_y() == i);
            });

        if (built_points_count == (width - 4))
        {
            removed_rows++;

            // erase-remove idiom
            auto it = remove_if(built_points.begin(), built_points.end(), [i](Cell point) 
                {
                 
                return (point.get_y() == i);
                });
            built_points.erase(it, built_points.end());

            for_each(built_points.begin(), built_points.end(), [i](Cell& point) //moves all points above the removed line downward
                {
                    
                    
                    if (point.get_y() > i)
                    point.move(0, -1);
                });

        }
        else
            i++;
    }
    
    return removed_rows; //returns removed rows
}