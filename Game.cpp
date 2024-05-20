#include "Game.h"

using namespace std;

Game::Game() // Game constructor
    : run {true}
{
    

    do // do while loop, run the game while regame is still true
    {
        system("cls"); //clears the screen after each game
        board = Board(14, 22); // initializes the board dimensions using the board class constructor
        running(); // main game loop
    } while (regame());
}



void Game::running() //runs in the background while the game is running
{
    while (!game_over()) //while it is not game over 
    {
        curr_piece = Piece(Cell((board.get_width() - 1) / 2, board.get_height() - 2, 'ß')); // sets the composition of the pieces, ß prints a block on the board
        while (!blocksland())
        {
            speedCounter++; // speedCounter increases by 1 with each refresh of the game
            speed = 90;
            if (speedCounter % 2)
            {
                curr_piece.fall_down(); // pieces automatically fall down
                
            }

            ClearScreen();//prevents screen flickering by clearing the screen each time the board is refreshed
            linesbuilt += board.remove_row(); // adds points when a row is removed

            for (int i = 0; i <= linesbuilt; i++) //nested for loops for the scoring system, adds 25 for each piece placed and 100 for each line filled
            {
                for (int j = 0; j <= piececount; j++)
                {
                    score = (i * 100) + (j * 25);
                    
                }
            }
            board.refresh(); //refreshes the board
            refreshall(); //refreshes all points on the board
            draw(); //draws the board
            controls(); // keyboard controls
            Sleep(speed); //controls the speed

        }
    }
    if (game_over() == true)
    {
        score = 0; // resets the game stats when the game is over
        linesbuilt = 0;
        piececount = 0;
    }
   
}


bool Game::game_over() //declares the game over
{
    for (const auto& pnt : board.get_built_points()) // points to all built tiles in the game
        if (pnt.get_y() >= board.get_height() - 1) //if there are built points in y >= height - 1, the game is over
        {
            return true;
        }
    return false;
}




bool Game::regame() //game over screen, asks the player to play again
{
    cout << "     GAME OVER" << endl;
    cout << "Want to play again? (y/n) " << endl;
    char c{};
    bool invalid{ false };
    do {
        cin >> c;
        if (c == 'y') // if 'y' is entered, game restarts
            return true;
        else if (c == 'n') // if 'n' is entered, program terminates
            return false;
        else {
            cout << "Invalid entry!\n"; //other characters are invalid
            invalid = true;
        }
    } while (invalid);
}



bool Game::blocksland() // sends the bodies of pieced that land to built points when they land 
{

    for (const auto& next_piece_pnt : curr_piece.fallenbody()) //const pointer that points to curr_piece.next_fall_down_body()
    {
        //Sets the piece to hit the ground
        if (next_piece_pnt.get_y() == 1)  //if piece hits y = 1
        {
            board.insert_to_built_points(curr_piece.get_body());//sends current piece to built points (tiles that have been built)
            piececount += 1; // adds to piece count
            return true;
        }
      
           
        //Sets piece to hit built points
        for (auto& built_pnt : board.get_built_points()) // if piece lands on top of a built piece
            if (next_piece_pnt == built_pnt) 
            {
                board.insert_to_built_points(curr_piece.get_body()); // sends current piece to built points
                piececount += 1; //adds to piece count
                return true;
            }
           
               
    }

    return false;
}



bool Game::checked_move(enum move_direction dir)
{
    for (const auto& next_piece_pnt : curr_piece.movedbody(dir))
    { 
        if (next_piece_pnt.get_x() == 1 || next_piece_pnt.get_x() == (board.get_width() - 2)) //prohibits pieces from going through the borders
            return false;

        for (const auto& built_pnt : board.get_built_points()) // does not allow built points to move
            if (built_pnt == next_piece_pnt)
                return false;
    }

    curr_piece.move(dir); //otherwise, piece allowed to move
    return true;
}

bool Game::checked_rotate() 
{
    for (const auto& next_piece_pnt : curr_piece.rotatedbody()) // pointer to the rotated body of a the current piece
    {
        if (next_piece_pnt.get_x() == 1 || next_piece_pnt.get_x() == (board.get_width() - 2)) //pieces on the border cannot rotate
            return false;

        for (const auto& built_pnt : board.get_built_points()) // does not allow built points to rotate
            if (built_pnt == next_piece_pnt)
                return false;
    }
    curr_piece.rotate(); //otherwise, piece allowed to rotate
    return true;
}

void Game::refreshall()
{
    final_points = board.get_all_points(); // gathers all tiles
    for (auto &final_pnt : final_points) // pointer to all cells at the end of a game
        for (auto piece_pnt : curr_piece.get_body()) // sets all built cells to final cells
            if (final_pnt == piece_pnt)
                final_pnt = piece_pnt;
}

void Game::draw() //creates the board
{
   
    
    for (int i = (board.get_height() - 1); i >= 0; i--) // double nested for loop
    { 
        for (int j = 0; j < board.get_width(); j++) {
            auto t = find(final_points.begin(), final_points.end(), Cell(j, i)); // uses find function to find all final points within range of for loop
            cout << t->get_type(); // sets all cells on the board to their appropriate type depending on their designation by set_border
        }
        cout <<endl;
    }
    cout << "\n Lines built: " << linesbuilt << endl; //reads out lines built
    cout << "\n Score: " << score << endl; // reads out score
    cout << piececount << " Pieces"; // reads out # of pieces
    
   

}

void Game::controls() //Game controls, uses GetAsyncKeyState
{
    if (GetAsyncKeyState(VK_UP)) // up arrow rotates piece
    {
        checked_rotate();
    }

    else if (GetAsyncKeyState(VK_DOWN)) // down arrow forces piece down
    {
        speed = 10;
    }

    else if (GetAsyncKeyState(VK_RIGHT)) // left and right arrows move piece left and right
    {
        checked_move(move_direction::right);
       
        
    }
    else if (GetAsyncKeyState(VK_LEFT))
    {
        checked_move(move_direction::left);
       
 
    }
}

void Game::ClearScreen() 
{
    // Function which cleans the screen without flickering
    COORD cursorPosition;   cursorPosition.X = 0;   cursorPosition.Y = 0;   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}