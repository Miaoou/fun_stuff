// InsertionSort.cpp

#include <array>
#include <iterator>
#include <utility>

int ar[] = { 5, 2, 4, 13, 0, 44, 0 };
auto arSz = sizeof( ar ) / sizeof( int );

void
insertion_sort_c()
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

void
insertion_sort_cpp()
{
    using namespace std;

    for( auto it = begin( ar ) + 1; it != end( ar ); ++it )
        for( auto it2 = it; *it2 < *( it2 - 1 ); --it2 )
            swap( *it2, *( it2 - 1 ) );
}

//int
//main()
//{
//    //insertion_sort_c();
//    insertion_sort_cpp();
//
//    return 0;
//}