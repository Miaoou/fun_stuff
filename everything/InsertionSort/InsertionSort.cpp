// InsertionSort.cpp

int
main()
{
    int ar[] = { 5, 2, 4, 13, 0, 44, 0 };
    auto arSz = sizeof( ar ) / sizeof( int );

    for( int i = 1; i < arSz; ++i )
    {
        int j = i;
        while (ar[j] <= ar[j-1])
        {
            auto tmp = ar[j];
            ar[j] = ar[j-1];
            ar[j-1] = tmp;
            --j;
        }
    }

    return 0;
}