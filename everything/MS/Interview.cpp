#include <iostream>
#include <array>

using namespace std; //to remove

enum Direction
{
    left = 1, // move left (x-1)
    down = 2, // move down (y-1)
    right = 3, // move right (x+1)
    up = 4  // move up (y+1)
};

class IMaze

{
public:
    // Will create a session and a maze.  The maze will be no larger than 100 by 100 units in size.  The mouse and 
    //a piece of cheese will be positioned at random locations within the maze.
    void Initialize();

    // Will attempt to move the mouse in one direction.  If the move was successful, returns true.  If there was a 
    // wall and the move failed, returns false.
    bool Move( Direction tryMovingMouseInThisDirection );

    // Will return true if the mouse and cheese are at the same location, false otherwise.
    bool Success();

};

int
moveMouse( array< array< char, 200 >, 200 >& map, IMaze& maze, int& xCurrent, int& yCurrent )
{    
    if( map[ yCurrent ][ xCurrent + 1 ] != '@' && maze.Move( Direction::right ) ) // todo: check bounds
    {
        map[ yCurrent ][ ++xCurrent ] = '@';
        return maze.Success() ? 1 : 0;
    }
    if( map[ yCurrent ][ xCurrent - 1 ] != '@' && maze.Move( Direction::left ) )
    {
        map[ yCurrent ][ --xCurrent ] = '@';
        return maze.Success() ? 1 : 0;
    }
    if( map[ yCurrent + 1 ][ xCurrent ] != '@' && maze.Move( Direction::up ) )
    {
        map[ ++yCurrent ][ xCurrent ] = '@';
        return maze.Success() ? 1 : 0;
    }    
    if( map[ yCurrent - 1 ][ xCurrent ] != '@' && maze.Move( Direction::down ) )
    {
        map[ --yCurrent ][ xCurrent ] = '@';
        return maze.Success() ? 1 : 0;
    }
    
    // manage case where we are in a dead end. Go back to '@'.
    if( maze.Move( Direction::right ) ) // todo: check bounds
    {
        ++xCurrent;
        return 0;
    }
    if( maze.Move( Direction::left ) )
    {
        --xCurrent = '@';
        return 0;
    }
    if( maze.Move( Direction::up ) )
    {
        ++yCurrent = '@';
        return 0;
    }
    if( maze.Move( Direction::down ) )
    {
        --yCurrent = '@';
        return 0;
    }

    return -1;
}


void FindCheese( IMaze maze )
{
    array< array< char, 200 >, 200 > map; // analyzed nodes
    int xInit = 100, yInit = 100; // safe position in the middle of the map
    int found = 0;
    while( found = moveMouse( map, maze, xInit, yInit ) < 0 )
    {
        if( found == -1 )
            break;
    }// Depth First Search
    
    if( found > 0 )
        cout << "Found at: " << xInit << " " << yInit << endl;
    else
        cout << "Not found" << endl;
}


int main()
{
    IMaze maze;
    maze.Initialize();
    FindCheese( maze );
}




