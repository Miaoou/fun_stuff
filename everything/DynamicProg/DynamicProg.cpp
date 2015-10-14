// DynamicProg

#include <numeric>

int**
rearrange( int* a, int sz, int k )
{
    int** r = new int*[ 3 ];

    int average = 0;
    for( int i = 0; i < sz; ++i )
        average += a[ i ];

    average /= k;

    int max = 0;
    int* part = nullptr;

    for( int i = sz - 1, j = 0, nPart = 0; i >= 0; --i )
    {
        if( !part )
            part = new int[ sz ];

        max += a[ i ];
        part[ j ] = a[ i ];
        ++j;

        if( max >= average )
        {
            r[ nPart++ ] = part;
            part = nullptr;
            j = 0;
            max = 0;
        }
    }

    return r;
}

int
main()
{
    int a[] = { 100,200,300,400,500,600,700,800,900 };
    int** r = rearrange( a, 9, 3 );

    return 0;
}