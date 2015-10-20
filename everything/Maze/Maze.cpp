// Maze.cpp

#include <iostream>
#include <queue>
#include <unordered_set>
#include <set>
#include <memory>
#include <tuple>
#include <algorithm>
#include <iterator>
#include <functional>
#include <array>
using namespace std; //to remove

struct Node
{
    Node( int xSz, int ySz, shared_ptr< Node > const& caller ) : _x( xSz ), _y( ySz ), _caller{ caller } {}
    
    shared_ptr< Node > _caller{ nullptr };
    int _x{ 0 };
    int _y{ 0 };
    int _cost{ 0 };
    int _heuristic{ 0 };
    bool _valid{ true };
};

auto
priorityCondition = []( shared_ptr< Node > const& left, shared_ptr< Node > const& right ) -> bool
{
    return ( left->_cost + left->_heuristic ) > ( right->_cost + right->_heuristic );
};

vector< shared_ptr< Node > >
reconstruct_path( shared_ptr< Node > const& goal )
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
        && ( ( *ar )[ y ][ x ] == ' ' || ( *ar )[ y ][ x ] == 'E' );
}

int
manhattan_dist( shared_ptr< Node > const& node, int xEnd, int yEnd )
{
    return abs( node->_x - xEnd ) + abs( node->_y - yEnd );
}

vector< shared_ptr< Node > >
findNeighbours( char( *ar )[ 10 ][ 9 ], shared_ptr< Node > const& node )
{
    vector< shared_ptr< Node > > neighbours;

    if( inboundAndFree( ar, node->_x + 1, node->_y, 9, 10 ) )
        neighbours.push_back( make_shared< Node >( node->_x + 1, node->_y, node ) );
    if( inboundAndFree( ar, node->_x, node->_y + 1, 9, 10 ) )
        neighbours.push_back( make_shared< Node >( node->_x, node->_y + 1, node ) );
    if( inboundAndFree( ar, node->_x - 1, node->_y, 9, 10 ) )
        neighbours.push_back( make_shared< Node >( node->_x - 1, node->_y, node ) );
    if( inboundAndFree( ar, node->_x, node->_y - 1, 9, 10 ) )
        neighbours.push_back( make_shared< Node >( node->_x, node->_y - 1, node ) );

    return neighbours;
}

class PQueue
    : public priority_queue< shared_ptr< Node >, vector< shared_ptr< Node > >, decltype( priorityCondition ) >
{
public:
    PQueue() : priority_queue< shared_ptr< Node >, vector< shared_ptr< Node > >, decltype( priorityCondition ) >( priorityCondition ) {}

    pair< bool, vector< shared_ptr< Node > >::iterator >
    findByCoord( shared_ptr< Node > const& nodeToFind )
    {
        auto foundIt = find_if( begin( this->c ), end( this->c ), [ &nodeToFind ] ( shared_ptr< Node > const& node )
        {
            return ( node->_x == nodeToFind->_x ) && ( node->_y == nodeToFind->_y );
        } );

        return make_pair( ( foundIt != end( this->c ) ), foundIt );
    }
};

vector< shared_ptr< Node > >
solveMaze( char(*ar)[10][9], int xSz, int ySz, int xEnd, int yEnd )
{
    array< array< shared_ptr< Node >, 10 >, 9 > closedList;
    PQueue openList;

    auto startNode = make_shared< Node >( 1, 1, nullptr );
    startNode->_heuristic = manhattan_dist( startNode, xEnd, yEnd );
    openList.push( startNode );
    
    while( !openList.empty() )
    {
        auto nodeToAnalyze = openList.top();
        openList.pop();

        if( !nodeToAnalyze->_valid ) // automatic deletion upon cost update. See below.
            continue;

        if( ( *ar )[ nodeToAnalyze->_y ][ nodeToAnalyze->_x ] == 'E' ) // exit found, reconstruct path
            return reconstruct_path( nodeToAnalyze );
        else
        {
            for( auto const& neighbour : findNeighbours( ar, nodeToAnalyze ) ) // find all eligible adjacent nodes
            {
                if( closedList[ neighbour->_y ][ neighbour->_x ] ) // node already analyzed, skip
                    continue;

                neighbour->_cost = nodeToAnalyze->_cost + 1;

                bool beingAnalyzed = false;
                vector< shared_ptr< Node > >::iterator foundIt;
                tie( beingAnalyzed, foundIt ) = openList.findByCoord( neighbour );

                if( !beingAnalyzed ) // never encountered, add it to the queue
                {
                    neighbour->_heuristic = manhattan_dist( neighbour, xEnd, yEnd );
                    openList.push( neighbour );
                }
                else
                {
                    if( neighbour->_cost < ( *foundIt )->_cost ) // already being analyzed, but the current path is better, so we update the node (remove and add)
                    {
                        ( *foundIt )->_valid = false; // will be deleted automatically by the pop(). Avoid deleting in the middle of the queue and break the priority.
                        neighbour->_heuristic = manhattan_dist( neighbour, xEnd, yEnd );
                        openList.push( neighbour );
                    }
                }
            }
            closedList[ nodeToAnalyze->_y ][ nodeToAnalyze->_x ] = nodeToAnalyze;
        }
    }

    return vector< shared_ptr< Node > >();
}

ostream&
operator<<( ostream& os, shared_ptr< Node > const& node )
{
    static int i = 0;
    ++i;
    os << "[" << i << "] " << node->_x << " " << node->_y << "  " << node->_cost << " " << node->_heuristic << " " << node->_heuristic + node->_cost;
    return os;
}

int
main()
{
    char ar[10][9] = {
        { '#','#','#','#','#','#','#','#','#' },
        { '#',' ',' ','#',' ',' ',' ',' ','#' },
        { '#',' ',' ','#',' ',' ',' ',' ','#' },
        { '#',' ',' ','#',' ',' ',' ',' ','#' },
        { '#',' ',' ','#',' ',' ',' ',' ','#' },
        { '#',' ',' ','#',' ',' ',' ',' ','#' },
        { '#',' ',' ','#',' ',' ','#','#','#' },
        { '#',' ',' ',' ',' ',' ','#',' ','#' },
        { '#',' ',' ',' ',' ',' ',' ','E','#' },
        { '#','#','#','#','#','#','#','#','#' }
    };

    auto res = solveMaze( &ar, 9, 10, 7, 8 );

    reverse_copy( begin( res ), end( res ), ostream_iterator< shared_ptr< Node > >( cout, "\n" ) );

    return 0;
}