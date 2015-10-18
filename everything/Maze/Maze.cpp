// Maze.cpp

#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <memory>

using namespace std; //to remove

struct Node
{
    Node( int xSz, int ySz ) : _x( xSz ), _y( ySz ) {}
    //Node( Node const& ) = default;
    int _x{ 0 };
    int _y{ 0 };
    int _cost{ 0 };
    int _heuristic{ 0 };
    shared_ptr< Node > _caller{ nullptr };
};

auto
closestNode = []( shared_ptr< Node > const& left, shared_ptr< Node > const& right ) -> bool
{
    return left->_heuristic < right->_heuristic;
};

bool
operator==( shared_ptr< Node > const& left, shared_ptr< Node > const& right )
{
    return ( left->_x == right->_x ) && ( left->_y == right->_y );
};

vector< shared_ptr< Node > >
reconstruct_path( shared_ptr< Node > goal )
{
    vector< shared_ptr< Node > > path{ goal };
    shared_ptr< Node > node{ goal };
    while( node = node->_caller )
        path.push_back( node );

    return path;
}

bool
inboundAndFree( char( *ar )[ 10 ][ 9 ], int x, int y, int X, int Y )
{
    return x <= X && x >= 0
        && y <= Y && y >= 0
        && ( *ar )[ y ][ x ] == ' ';
}

class PQueue
    : public priority_queue< shared_ptr< Node >, vector< shared_ptr< Node > >, decltype( closestNode ) >
{
public:
    PQueue() : priority_queue< shared_ptr< Node >, vector< shared_ptr< Node > >, decltype( closestNode ) >( closestNode ) {}
    bool alreadyExists( shared_ptr< Node > const& node )
    {
        auto it = find( this->c.begin(), this->c.end(), node );
        return( it != this->c.end() && ( *it )->_cost < node->_cost );
    }
};

int
euclidian( Node const& node, int xEnd, int yEnd )
{
    return abs( node._x - xEnd ) + abs( node._y - yEnd );
}

vector< pair< int, int > >
findNeighbours( Node const& node )
{
    return vector< pair< int, int > >{
        make_pair( node._x + 1, node._y ),
        make_pair( node._x, node._y + 1 ),
        make_pair( node._x - 1, node._y ),
        make_pair( node._x, node._y - 1 )
    };
}

vector< shared_ptr< Node > >
solveMaze( char(*ar)[10][9], int xSz, int ySz, int xEnd, int yEnd )
{
    auto start = make_shared< Node >( 1, 1 );
    unordered_set< shared_ptr< Node > > analyzed;
    PQueue toBeAnalyzed;
    toBeAnalyzed.push( move( start ) );
    
    while( !toBeAnalyzed.empty() )
    {
        auto nodeToAnalyze = toBeAnalyzed.top();
        toBeAnalyzed.pop();

        if( ( *ar )[ nodeToAnalyze->_y ][ nodeToAnalyze->_x ] == 'E' )
            return reconstruct_path( nodeToAnalyze );
        else
        {
            for( auto const& coord : findNeighbours( *nodeToAnalyze ) )
            {
                if( inboundAndFree( ar, coord.first, coord.second, xSz, ySz ) )
                {
                    int xNeighbour, yNeighbour;
                    tie( xNeighbour, yNeighbour ) = coord;
                    auto neighbour = make_shared< Node >( xNeighbour, yNeighbour );

                    auto it = analyzed.find( neighbour );
                    auto exists = it != analyzed.end() && ( *it )->_cost < neighbour->_cost;
                    if( !( exists || toBeAnalyzed.alreadyExists( neighbour ) ) )
                    {
                        neighbour->_caller = nodeToAnalyze;
                        neighbour->_cost = nodeToAnalyze->_cost + 1;
                        neighbour->_heuristic = neighbour->_cost + euclidian( *neighbour, xEnd, yEnd );
                        toBeAnalyzed.push( neighbour );
                    }
                }
            }

            analyzed.insert( nodeToAnalyze );
        }
    }

    return vector< shared_ptr< Node > >();
}

int
main()
{
    char ar[10][9] = {
        { '#','#','#','#','#','#','#','#','#' },
        { '#',' ',' ',' ','#',' ',' ',' ','#' },
        { '#',' ',' ',' ','#',' ',' ',' ','#' },
        { '#',' ',' ',' ',' ',' ',' ',' ','#' },
        { '#',' ',' ',' ',' ',' ',' ',' ','#' },
        { '#',' ',' ',' ','#','#','#',' ','#' },
        { '#',' ',' ',' ','#',' ',' ',' ','#' },
        { '#',' ',' ',' ','#',' ',' ',' ','#' },
        { '#',' ',' ',' ',' ',' ',' ','E','#' },
        { '#','#','#','#','#','#','#','#','#' }
    };

    solveMaze( &ar, 9, 10, 7, 8 );
}