// bst_1.cpp

#include <iostream>
#include <algorithm>

struct Node;

int ar[] = { 5, 2, 4, 13, 0, 44, 0 };
auto arSz = sizeof( ar ) / sizeof( int );

struct Node
{
    int _val = 0;
    Node* _left = nullptr;
    Node* _right = nullptr;
};

void
insert_node_c( Node* top, Node* node )
{
    if( node->_val >= top->_val )
    {
        if( top->_right )
            insert_node_c( top->_right, node );
        else
            top->_right = node;
    }
    else if( node->_val < top->_val )
    {
        if( top->_left )
            insert_node_c( top->_left, node );
        else
            top->_left = node;
    }
}

Node*
create_bst_c()
{
    Node* root = new Node();
    root->_val = ar[ 0 ];

    for( int i = 1; i < ( int )arSz; ++i )
    {
        Node* leaf = new Node();
        leaf->_val = ar[ i ];

        insert_node_c( root, leaf );
    }

    return root;
}

auto
create_bst_cpp() -> Node*
{
    using namespace std;

    auto root = new Node();
    root->_val = ar[ 0 ];

    for_each( begin( ar ) + 1, end( ar ), [ &root ]( auto i )
    {
        auto leaf = new Node();
        leaf->_val = i;

        insert_node_c( root, leaf );
    } );

    return root;
}

auto
operator<<( std::ostream& os, Node* node ) -> std::ostream&
{
    if( !node )
        return os << "not found";

    std::cout << node->_val;

    if( node->_left )
        std::cout << " -> " << node->_left << std::endl;
    if( node->_right )
        std::cout << " -> " << node->_right << std::endl;

    return os;
}

auto
find_node_cpp( Node* node, int val ) -> Node*
{
    if( node->_val == val )
        return node;
    else if( node->_left && val < node->_val )
        return find_node_cpp( node->_left, val );
    else if( node->_right && val >= node->_val )
        return find_node_cpp( node->_right, val );
    else
        return nullptr;
}

int
main()
{
    auto root = create_bst_cpp();
    //std::cout << root << std::endl;
    auto node = find_node_cpp( root, 14 );
    std::cout << node << std::endl;

    return 0;
}