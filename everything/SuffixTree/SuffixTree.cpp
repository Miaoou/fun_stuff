// SuffixTree.cpp

#include <iostream>
#include <vector>

using namespace std;

struct STNode
{
    
    vector< STNode > _children;
};

STNode*
buildSyntaxTree( string const& S )
{
    auto root = new STNode{};

    for( int i = S.size() - 1; i > -1; --i )
    {
        string suffix( begin( S ) + i, end( S ) );

    }

    return nullptr;
}

vector< string >
findPalInTree( STNode* root )
{
    return vector< string >{};
}

vector< string >
findPalindrome( string const& S )
{
    STNode* rootTree = buildSyntaxTree( S );
    return findPalInTree( rootTree );
}

int
main()
{
    string S{ "abcbabba" };
    auto vecPals = findPalindrome( S );

    return 0;
}