// MergeSort.h

#pragma once
#ifndef MERGESORT_H
#define MERGESORT_H

int*
merge( int left[], int right[], int totalSz )
{
    int* ar = new int[ totalSz ];
    int mid = totalSz / 2;

    int i = 0;
    int j = 0;
    while( i < mid && j < mid )
    {
        if( left[ i ] < right[ j ] )
            ar[ i + j ] = left[ i++ ];
        else if( left[ i ] >= right[ j ] )
            ar[ i + j ] = right[ j++ ];
    }

    while( i < mid )
        ar[ i + j ] = left[ i++ ];

    while( j < mid )
        ar[ i + j ] = right[ j++ ];

    return ar;
}

int*
merge_sort_c( int ar[], int arSz )
{
    if( arSz == 1 )
        return ar;

    int mid = arSz / 2;
    int* left = new int[ mid ];
    int* right = new int[ mid ];

    memcpy( left, ar, mid * sizeof( int ) );
    memcpy( right, &ar[ mid ], mid * sizeof( int ) );
    
    left = merge_sort_c( left, mid );
    right = merge_sort_c( right, mid );

    return merge( left, right, arSz );
}

template< int arSz >
void
merge_sort_cpp( int( &ar )[ arSz ] )
{
    using namespace std;


}

#endif // MERGESORT_H
