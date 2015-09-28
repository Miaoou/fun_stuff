// MergeSort.h

#pragma once
#ifndef MERGESORT_H
#define MERGESORT_H

void
merge( int ar[], int arSz )
{
    if( arSz == 1 )
        return;

    int mid = arSz / 2;
    static int* left = new int[ mid ];
    static int* right = new int[ arSz - mid ];

    memcpy( left, ar, mid * sizeof( int ) );
    memcpy( right, &ar[ mid ], ( arSz - mid ) * sizeof( int ) );

    for( int i = 0, j = 0; i < mid && j < ( arSz - mid ); )
    {
        if( j >= mid || left[ i ] < right[ j ] )
            ar[ i + j ] = left[ i++ ];
        else if( i >= mid || left[ i ] >= right[ j ] )
            ar[ i + j ] = right[ j++ ];
    }
}

template< int arSz >
void
merge_sort_c( int( &a )[ arSz ] )
{
    int ar[] = { 1, 2, 5, 3, 4, 7 };
    merge( ar, 6 );
}

template< int arSz >
void
merge_sort_cpp( int( &ar )[ arSz ] )
{
    using namespace std;


}

#endif // MERGESORT_H
