// BubbleSort.h

#pragma once
#ifndef BUBBLESORT_H
#define BUBBLESORT_H

template< int arSz >
void
bubble_sort_c( int( &ar )[ arSz ] )
{
    for( int i = 1; i < arSz; ++i )
    {
        if( ar[ i ] < ar[ i - 1 ] )
        {
            int tmp = ar[ i ];
            ar[ i ] = ar[ i - 1 ];
            ar[ i - 1 ] = tmp;
            i = 0;
        }
    }
}

template< int arSz >
void
bubble_sort_cpp( int( &ar )[ arSz ] )
{
    using namespace std;

    int* it = nullptr;

    while( ( it = adjacent_find( begin( ar ), end( ar ), greater< int >() ) ) && it != end( ar ) )
        swap( *it, *( it + 1 ) );
}

#endif // BUBBLESORT_H