// InsertionSort.h

#pragma once
#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

template< int arSz >
void
insertion_sort_c( int( &a )[ arSz ] )
{
    for( int i = 1; i < arSz; ++i )
    {
        int key = a[ i ];
        int j = i - 1;
        
        while( j >= 0 && a[ j ] > key )
        {
            a[ j + 1 ] = a[ j ];
            --j;
        }

        a[ j + 1 ] = key;
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
