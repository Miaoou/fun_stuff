// MatchingGloves.cpp

#include "MatchingGloves.h"
#include "Common.h"

using namespace std;

int _count = 0;

void
matching_gloves()
{
    auto f = [] ( Node const& s1, Node const& s2 )-> bool
    {
        auto eq = Comp< equal_to< string > >( s1, s2 );
        if( eq )
        {
            if( !s1._s_count )
                s1._s_count.reset( new int{ 1 } );

            if( !s2._s_count )
            {
                s2._s_count = s1._s_count;
                ++*s1._s_count;

                if( !( *s1._s_count % 2 ) )
                    ++_count;
            }
        }

        return Comp< less< string > >( s1, s2 );
    };

    multiset< Node, decltype( f ) > s{ f };

    s.emplace( "bcd" );
    s.emplace( "erty" );
    s.emplace( "ytre" );
    //s.insert( "opipo" );
    s.emplace( "dcb" );

    if( s.empty() )
    {
        cout << 0 << endl;
        return;
    }

    if( _count == 0 )
    {
        cout << -1 << endl;
        return;
    }
}