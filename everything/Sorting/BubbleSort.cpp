/// BubbleSort.cpp

#include <iterator>
#include <algorithm>
#include <functional>

int ar[] = { 5, 2, 4, 13, 0, 44, 0 };
auto arSz = sizeof( ar ) / sizeof( int );

void
bubble_sort_c()
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

void
bubble_sort_cpp()
{
    using namespace std;

    int* it = nullptr;

    while( ( it = adjacent_find( begin( ar ), end( ar ), greater< int >() ) ) && it != end( ar ) )
        swap( *it, *( it + 1 ) );
}

//int
//main()
//{
//    //bubble_sort_c();
//    bubble_sort_cpp();
//
//    return 0;
//}