// DeFS.cpp

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

vector< shared_ptr< Node > >
reconstructPath( shared_ptr< Node > goal )
{
    vector< shared_ptr< Node > > path{ goal };
    shared_ptr< Node > node{ goal };
    while( node = node->_caller )
        path.push_back( node );

    return path;
}

shared_ptr< Node >
getNextNeighbour( char( *ar )[ 10 ][ 9 ], shared_ptr< Node > const& current )
{
    if( inboundAndFree( ar, current->_x + 1, current->_y, 9, 10 ) )
        return make_shared< Node >( current->_x + 1, current->_y, current );
    if( inboundAndFree( ar, current->_x, current->_y + 1, 9, 10 ) )
        return make_shared< Node >( current->_x, current->_y + 1, current );
    if( inboundAndFree( ar, current->_x - 1, current->_y, 9, 10 ) )
        return make_shared< Node >( current->_x - 1, current->_y, current );
    if( inboundAndFree( ar, current->_x, current->_y - 1, 9, 10 ) )
        return make_shared< Node >( current->_x, current->_y - 1, current );

    return nullptr;
}

//bool
//equalNodes( shared_ptr< Node > const& left, shared_ptr< Node > const& right )
//{
//    if( !left || !right )
//        return false;
//
//    return ( left->_x == right->_x ) && ( left->_y == right->_y );
//}

vector< shared_ptr< Node > >
solveMaze( char( *ar )[ 10 ][ 9 ], int xSz, int ySz, int xEnd, int yEnd )
{
    queue< shared_ptr< Node > > queueNode;

    auto start = make_shared< Node >( 1, 1, nullptr );
    queueNode.push( start );

    while( !queueNode.empty() )
    {
        auto current = queueNode.front();
        queueNode.pop();

        if( ( *ar )[ current->_y ][ current->_x ] == 'E' )
            return reconstructPath( current );

        ( *ar )[ current->_y ][ current->_x ] = '@'; // mark as analyzed

        shared_ptr< Node > neighbour;
        while( neighbour = getNextNeighbour( ar, current ) )
        {
            queueNode.push( neighbour );
            break;
        }
        
        if( !neighbour )
            queueNode.push( current->_caller );
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
        { '#',' ',' ','#',' ',' ','#',' ','#' },
        { '#',' ',' ',' ',' ',' ','#','E','#' },
        { '#',' ',' ',' ',' ',' ','#',' ','#' },
        { '#','#','#','#','#','#','#','#','#' }
    };

    auto res = solveMaze( &ar, 9, 10, 7, 8 );

    reverse_copy( begin( res ), end( res ), ostream_iterator< shared_ptr< Node > >( cout, "\n" ) );

    return 0;
}