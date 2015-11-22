// BrFS.cpp

#include <iostream>
#include <queue>
#include <unordered_set>
#include <set>
#include <memory>
#include <tuple>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std; //to remove

struct Node
{
    Node( int xSz, int ySz, shared_ptr< Node > const& caller ) : _x( xSz ), _y( ySz ), _caller{ caller } {}
    int _x{ 0 };
    int _y{ 0 };
    shared_ptr< Node > _caller{ nullptr };
};

bool
isFreePath( char c )
{
    return ( c == ' ' || c == 'E' );
}

bool
inboundAndFree( char( *ar )[ 10 ][ 9 ], int x, int y, int X, int Y )
{
    return x <= X && x >= 0
        && y <= Y && y >= 0
        && isFreePath( ( *ar )[ y ][ x ] );
}

void
addNeighbours( char( *ar )[ 10 ][ 9 ], queue< shared_ptr< Node > >& queueNodes, shared_ptr< Node >& node )
{
    if( inboundAndFree( ar, node->_x + 1, node->_y, 9, 10 ) )
        queueNodes.push( make_shared< Node >( node->_x + 1, node->_y, node ) );
    if( inboundAndFree( ar, node->_x, node->_y + 1, 9, 10 ) )
        queueNodes.push( make_shared< Node >( node->_x, node->_y + 1, node ) );
    if( inboundAndFree( ar, node->_x - 1, node->_y, 9, 10 ) )
        queueNodes.push( make_shared< Node >( node->_x - 1, node->_y, node ) );
    if( inboundAndFree( ar, node->_x, node->_y - 1, 9, 10 ) )
        queueNodes.push( make_shared< Node >( node->_x, node->_y - 1, node ) );
}

vector< shared_ptr< Node > >
reconstructPath( shared_ptr< Node > goal )
{
    vector< shared_ptr< Node > > path{ goal };
    shared_ptr< Node > node{ goal };
    while( node = node->_caller )
        path.push_back( node );

    return path;
}

vector< shared_ptr< Node > >
solveMaze( char( *ar )[ 10 ][ 9 ], int xSz, int ySz, int xEnd, int yEnd )
{
    auto start = make_shared< Node >( 1, 1, nullptr );
    queue< shared_ptr< Node > > queueNodes;
    queueNodes.push( start );

    while( !queueNodes.empty() )
    {
        auto node = queueNodes.front();
        queueNodes.pop();

        if( ( *ar )[ node->_y ][ node->_x ] == 'E' )
            return reconstructPath( node );

        ( *ar )[ node->_y ][ node->_x ] = '@'; // mark as analyzed
        addNeighbours( ar, queueNodes, node );
    }

    return vector< shared_ptr< Node > >();
}

ostream&
operator<<( ostream& os, shared_ptr< Node > const& node )
{
    static int i = 0;
    ++i;
    os << "[" << i << "] " << node->_x << " " << node->_y;
    return os;
}

int
main()
{
    char ar[ 10 ][ 9 ] = {
        { '#','#','#','#','#','#','#','#','#' },
        { '#',' ',' ','#',' ',' ',' ',' ','#' },
        { '#',' ',' ','#',' ',' ','#',' ','#' },
        { '#',' ',' ','#',' ',' ','#',' ','#' },
        { '#',' ',' ','#',' ',' ','#',' ','#' },
        { '#',' ',' ','#',' ',' ','#',' ','#' },
        { '#',' ',' ','#','E',' ','#',' ','#' },
        { '#',' ',' ',' ',' ',' ','#',' ','#' },
        { '#',' ',' ',' ',' ',' ','#',' ','#' },
        { '#','#','#','#','#','#','#','#','#' }
    };

    auto res = solveMaze( &ar, 9, 10, 7, 8 );

    reverse_copy( begin( res ), end( res ), ostream_iterator< shared_ptr< Node > >( cout, "\n" ) );

    return 0;
}