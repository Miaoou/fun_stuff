// Sorting.cpp

#include "Common.h"
#include "BubbleSort.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"

int ar[] = { 5, 2, 4, 13, 0, 44, 0 };

int
main()
{
    int ar1[] = { 1, 3, 5, 2, 4, 7, 0, 6 };
    
    //int* arSorted = merge_sort_c( ar1, sizeof( ar1 ) / sizeof( ar[ 0 ] ) );
    merge_sort_cpp( ar1 );

    return 0;
}