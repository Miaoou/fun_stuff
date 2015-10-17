// Maze.cpp

#include <iostream>
#include <queue>
#include <vector>
#include <memory>

using namespace std; //to remove

struct Node
{
    Node( int xSz, int ySz ) : _x( xSz ), _y( ySz ) {}
    //Node( Node const& ) = default;
    int _x{ 0 };
    int _y{ 0 };
    int _h{ 0 };
    int _g{ 0 };
    Node* _caller{ nullptr };
};

auto
closestNode = []( shared_ptr< Node > const& left, shared_ptr< Node > const& right ) -> bool
{
    return ( left->_h + left->_g ) > ( right->_h + right->_g );
};

void
solveMaze( char(*ar)[10][9], int xSz, int ySz )
{
    auto start = make_shared< Node >( xSz, ySz );
    vector< shared_ptr< Node > > analyzed;
    priority_queue< shared_ptr< Node >, vector< shared_ptr< Node > >, decltype( closestNode ) > toBeAnalyzed( closestNode );
    toBeAnalyzed.push( move( start ) );

    while( !toBeAnalyzed.empty() )
    {
        auto nodeToAnalyze = toBeAnalyzed.top();
        toBeAnalyzed.pop();

        auto leftNode = make_shared< Node >( nodeToAnalyze->_x, nodeToAnalyze->_y );
    }
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

    solveMaze( &ar, 9, 10 );
}