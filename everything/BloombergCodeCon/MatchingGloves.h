// MatchingGloves.h

#pragma once
#ifndef MATCHINGGLOVES_H
#define MATCHINGGLOVES_H

#include <string>
#include <memory>
#include <iterator>

struct Node
{
    Node( std::string s ) : _s{ s } {}
    std::string _s;
    mutable std::shared_ptr< int > _s_count;
};

template< class PredT >
auto
Comp( Node const& s1, Node const& s2 ) -> bool
{
    auto s1rev = std::string{ std::rbegin( s1._s ), std::rend( s1._s ) };
    auto const& s1key = s1._s < s1rev ? s1._s : s1rev;

    auto s2rev = std::string{ std::rbegin( s2._s ), std::rend( s2._s ) };
    auto const& s2key = s2._s < s2rev ? s2._s : s2rev;

    return PredT{}( s1key, s2key );
}

void matching_gloves();

#endif // MATCHINGGLOVES_H
