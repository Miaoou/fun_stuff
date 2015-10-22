// BST_2.cpp

// find minimum depth of a binary tree
// http://www.geeksforgeeks.org/find-minimum-depth-of-a-binary-tree/
#include <iostream>
#include <algorithm>
#include <numeric>
#include <array>
#include <queue>
using namespace std;

// A BT Node
struct Node
{
    int data;
    struct Node* left, *right;
};

// Utility function to create new Node
Node*
newNode( int data )
{
    Node *temp = new Node;
    temp->data = data;
    temp->left = temp->right = nullptr;
    return ( temp );
}

int
findMinDepth( Node* node )
{
    if( !node->left && !node->right )
        return 1;

    auto leftdepth = findMinDepth( node->left );
    auto rightdepth = findMinDepth( node->right );

    return leftdepth < rightdepth ? ++leftdepth : ++rightdepth;
}

int
findMinDepthOpt( Node* node )
{
    if( !node )
        return 0;

    static int minDepth = 1;
    static queue< Node const* > q;
    q.push( node );

    for( ;; )
    {
        Node const* elt = q.front();
        q.pop();

        if( !elt->left && !elt->right )
            return minDepth;
        else
        {
            if( elt->left )
                q.push( elt->left );
            if( elt->right )
                q.push( elt->right );
        }

        ++minDepth;
    }
}

// Given a number n, print following pattern without using any loop.Input: n = 16 Output : 16, 11, 6, 1, -4, 1, 6, 11, 16
void print_patt( int n )
{
    static int init = n;
    static bool reached = false;

    if( n < 0 )
        reached = true;

    cout << n << endl;

    if( init == n && reached )
        return;

    print_patt( reached ? n + 5 : n - 5 );
}

// How to print above pattern without any extra variable and loop?
void print_patt2( int n )
{
    // Base case (When n becomes 0 or negative)  
    if( n < 0 )
    {
        cout << n << " ";
        return;
    }

    // First print decreasing order
    cout << n << " ";
    print_patt2( n - 5 );

    // Then print increasing order
    cout << n << " ";
}

/*
Given an array that contains both positive and negative integers, find the product of the maximum product subarray. Expected Time complexity is O(n) and only O(1) extra space can be used.
http://www.geeksforgeeks.org/maximum-product-subarray/
*/

int maxProduct( int arr[], int n )
{
    // max positive product ending at the current position
    int max_ending_here = 1;

    // min negative product ending at the current position
    int min_ending_here = 1;

    // Initialize overall max product
    int max_so_far = 1;

    for( int i = 0; i < n; i++ )
    {
        if( arr[ i ] > 0 )
        {
            max_ending_here = max_ending_here*arr[ i ];
            min_ending_here = min( min_ending_here * arr[ i ], 1 );
        }
        else if( arr[ i ] == 0 )
        {
            max_ending_here = 1;
            min_ending_here = 1;
        }
        else
        {
            int temp = max_ending_here;
            max_ending_here = max( min_ending_here * arr[ i ], 1 );
            min_ending_here = temp * arr[ i ];
        }


        if( max_so_far <  max_ending_here )
            max_so_far = max_ending_here;
    }

    return max_so_far;
}

// find longest substring without repeated character
char*
findLongestSubstring( char* str, int sz )
{
    char* sub = "plouf";
    return sub;
}

int
main()
{
    char str[] = "aeiouyaeioabcdefghi";
    findLongestSubstring( str, strlen( str ) );

    //int arr[] = { 6, -3, -10, 0, 2 };
    //cout << maxProduct( arr, 5 ) << endl;

    // Let us construct the Tree shown in the above figure
    Node *root = newNode( 1 );
    root->left = newNode( 2 );
    root->right = newNode( 3 );
    root->left->left = newNode( 4 );
    root->left->right = newNode( 5 );

    cout << findMinDepthOpt( root ) << endl;
}