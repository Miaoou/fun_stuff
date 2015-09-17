// InsertionSort.h

#pragma once
#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

template< int arSz >
void
insertion_sort_c( int( &ar )[ arSz ] )
{
    for( int i = 1; i < arSz; ++i )
    {
        int j = i;
        while( ar[ j ] < ar[ j - 1 ] )
        {
            auto tmp = ar[ j ];
            ar[ j ] = ar[ j - 1 ];
            ar[ j - 1 ] = tmp;
            --j;
        }
    }
}

template< int arSz >
void
insertion_sort_cpp( int( &ar )[ arSz ] )
{
    using namespace std;

    for( auto it = begin( ar ) + 1; it != end( ar ); ++it )
        for( auto it2 = it; *it2 < *( it2 - 1 ); --it2 )
            swap( *it2, *( it2 - 1 ) );
}

#endif // INSERTIONSORT_H
