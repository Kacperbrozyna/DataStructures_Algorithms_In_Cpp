
#include <iostream>
#include <queue>

template<typename T>
struct Node
{
    Node( T data, Node* left = nullptr, Node* right = nullptr )
        : data_( data )
        , left_( left )
        , right_( right ) 
        {}

    T data_;
    Node<T>* left_;
    Node<T>* right_;
};

enum class DFSTraversal
{
    PRE_ORDER_,             // Node, Left, Right
    IN_ORDER_,              // Left, Node, Right
    POST_ORDER_,            // Left, Right, Node
};

template<typename T>
void DepthFirstSearchTraversal( Node<T>* node, DFSTraversal dfs_traversal_option )
{
    if( node == nullptr )
        return;

    switch( dfs_traversal_option )
    {
        case DFSTraversal::PRE_ORDER_:
            std::cout << node->data_ << std::endl;
            DepthFirstSearchTraversal( node->left_, dfs_traversal_option );
            DepthFirstSearchTraversal( node->right_, dfs_traversal_option );
            break;
        case DFSTraversal::IN_ORDER_:
            DepthFirstSearchTraversal( node->left_, dfs_traversal_option );
            std::cout << node->data_ << std::endl;
            DepthFirstSearchTraversal( node->right_, dfs_traversal_option );
            break;
        case DFSTraversal::POST_ORDER_:
            DepthFirstSearchTraversal( node->left_, dfs_traversal_option );
            DepthFirstSearchTraversal( node->right_, dfs_traversal_option );
            std::cout << node->data_ << std::endl;
            break;
        default:
            break;
    }
}

template<typename T>
void BreadthFirstSearch( Node<T>* root )
{
    if( root == nullptr )
        return;

    std::queue<Node<T>*> node_queue;
    node_queue.push( root );
    
    while( node_queue.size() )
    {
        Node<T>* temp_node = node_queue.front();
        std::cout << temp_node->data_ << std::endl;

        if( temp_node->left_)
            node_queue.push( temp_node->left_ );
        
        if( temp_node->right_ )
            node_queue.push( temp_node->right_ );

        node_queue.pop();
    }
}

template<typename T>
Node<T>* Insert( Node<T>* node, T data )
{
    if( !node )
        return new Node<T>{ data };

    if( node->data_ == data )
        return node;

    if( node->data_ < data )
    {
        node->right_ = Insert( node->right_, data );
        return node;
    }

    node->left_ = Insert( node->left_, data );
    return node;
}

template<typename T>
Node<T>* Find( Node<T>* node, T data )
{
    if( !node )
        return nullptr;

    if( node->data_ == data )
        return node;

    if( node->data_ < data )
        return Find( node->right_, data );
    
    return Find( node->left_, data );
}

template<typename T>
Node<T>* InorderSuccessor( Node<T>* node )
{
    Node<T>* current{ node };
    while( current && current->left_ != nullptr )
        current = current->left_;

    return current;
}

template<typename T>
Node<T>* Remove( Node<T>* node, T data )
{
    if( !node )
        return nullptr;
    
    if( node->data_ < data )
    {
        node->right_ = Remove( node->right_, data );
        return node;
    }

    if( node->data_ > data )
    {
        node->left_ = Remove( node->left_, data );
        return node;
    }

    if( node->left_ == nullptr )
    {
        Node<T>* temp = node->right_;
        delete node;
        return temp;
    }
    
    if( node->right_ == nullptr )
    {
        Node<T>* temp = node->left_;
        delete node;
        return temp;
    }

    Node<T>* temp = InorderSuccessor( node );
    if( !temp )
        return nullptr;

    node->data_ = temp->data_;
    node->right_ = Remove( node->right_, node->data_ );

    return node;
}

template<typename T>
size_t Size( Node<T>* node )
{
    if( !node )
        return 0;

    return static_cast<size_t>( 1 ) + Size( node->left_ ) + Size( node->right_ );
}

template<typename T>
int DepthOfNode( Node<T>* node, T data, int depth )
{
    if( !node )
        return -1;
    
    if( node->data_ == data )
        return depth;

    if( node->data_ < data )
        return DepthOfNode( node->right_, data, ++depth ); 

    return DepthOfNode( node->left_, data, ++depth );
}

template<typename T>
int HeightOfNode( Node<T>* node )    //Can find the Height of the Tree by using the root node
{
    if( !node )
        return -1;
    
    return 1 + std::max( HeightOfNode( node->left_ ), HeightOfNode( node->right_ ) );
}

int main()
{
    // Construct a hardcoded binary tree:
    //
    //          1
    //         / \
    //        2   3
    //       /   / \
    //      4   5   6

    Node<int>* root = new Node<int>( 4 );
    Insert( root, 5 );
    Insert( root, 6 );
    Insert( root, 2 );
    Insert( root, 3 );
    Insert( root, 1 );

    std::cout << "PreOrder: " << std::endl;
    DepthFirstSearchTraversal( root, DFSTraversal::PRE_ORDER_ );

    std::cout << "InOrder: " << std::endl;
    DepthFirstSearchTraversal( root, DFSTraversal::IN_ORDER_ );

    std::cout << "PostOrder: " << std::endl;
    DepthFirstSearchTraversal( root, DFSTraversal::POST_ORDER_ );

    std::cout << "Breadth First Search: " << std::endl;
    BreadthFirstSearch( root );

    std::cout << "KB: finding 3, is found: " << ( Find( root, 3 ) != nullptr ) << std::endl;
    std::cout << "KB: finding 6, is found: " << ( Find( root, 3 ) != nullptr ) << std::endl;
    std::cout << "KB: finding -1, is found: " << ( Find( root, -1 ) != nullptr ) << std::endl;

    std::cout << "KB: size of BST: " << Size( root ) << std::endl;

    Remove( root, 3 );
    std::cout << "KB: size of BST: " << Size( root ) << std::endl;
    DepthFirstSearchTraversal( root, DFSTraversal::IN_ORDER_ );

    std::cout << "Depth of node with key 5: " << DepthOfNode( root, 6, 0 ) << std::endl;
    std::cout << "Depth of node with key 10: " << DepthOfNode( root, 10, 0 ) << std::endl;

    std::cout << "Height of the tree: " << HeightOfNode( root ) << std::endl;

    return 0;
}