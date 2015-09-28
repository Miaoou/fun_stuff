// InsertionSort.h

#pragma once
#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

template< int arSz >
void
insertion_sort_c( int( &a )[ arSz ] )
{
    for( int i = 1, j = 0; i < arSz; ++i )
    {
        int key = a[ i ]; // element to insert
        for( j = i - 1; j >= 0 && a[ j ] > key; --j )
            a[ j + 1 ] = a[ j ]; // shift every element between the insert position and the element to insert

        a[ j + 1 ] = key; // insert element
    }
}

template< int arSz >
void
insertion_sort_cpp( int( &ar )[ arSz ] )
{
    using namespace std;

    for( auto it = begin( ar ); it != end( ar ); ++it )
        rotate( upper_bound( begin( ar ), it, *it ), it, it + 1 );
}

#endif // INSERTIONSORT_H
