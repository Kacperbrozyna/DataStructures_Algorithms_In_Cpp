#include <iostream>
#include <queue>

template<typename T>
struct Node
{
    Node( T data, Node<T>* left = nullptr, Node<T>* middle = nullptr, Node<T>* right = nullptr )
        : data_( data )
        , left_( left )
        , middle_( middle )
        , right_( right ) 
        {}

    T data_;
    Node<T>* left_;
    Node<T>* middle_;
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
            DepthFirstSearchTraversal( node->middle_, dfs_traversal_option );
            DepthFirstSearchTraversal( node->right_, dfs_traversal_option );
            break;
        case DFSTraversal::IN_ORDER_:
            DepthFirstSearchTraversal( node->left_, dfs_traversal_option );
            std::cout << node->data_ << std::endl;
            DepthFirstSearchTraversal( node->middle_, dfs_traversal_option );
            DepthFirstSearchTraversal( node->right_, dfs_traversal_option );
            break;
        case DFSTraversal::POST_ORDER_:
            DepthFirstSearchTraversal( node->left_, dfs_traversal_option );
            DepthFirstSearchTraversal( node->middle_, dfs_traversal_option );
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

        if( temp_node->middle_ )
            node_queue.push( temp_node->middle_ );
        
        if( temp_node->right_ )
            node_queue.push( temp_node->right_ );

        node_queue.pop();
    }
}

template<typename T>
Node<T>* Insert(Node<T>* node, T data) {
    if (!node)
        return new Node<T>(data);

    if (data < node->data_) 
    {
        node->left_ = Insert(node->left_, data);
    } 
    else if (data > node->data_) 
    {
        node->right_ = Insert(node->right_, data);
    } 
    else 
    {
        node->middle_ = Insert(node->middle_, data);
    }

    return node;
}

template<typename T>
Node<T>* Find(Node<T>* node, int data) {
    if( !node )
    { 
        return nullptr;
    }

    if( data < node->data_ ) 
    { 
        return Find(node->left_, data);
    }

    if( data > node->data_ ) 
    {
        return Find(node->right_, data);
    }

    return node; 
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
Node<T>* Remove( Node<T>* node, char data )
{
    if( !node )
    {
        return nullptr;
    }

    if( data < node->data_ ) 
    {
        node->left_ = Remove(node->left_, data);
    } 
    else if( data > node->data_ ) 
    {
        node->right_ = Remove(node->right_, data);
    } 
    else 
    {
        if (node->middle_) {
            Node<T>* temp = node->middle_;
            delete node;
            return temp; 
        }

        if (!node->left_) {
            Node<T>* temp = node->right_;
            delete node;
            return temp;
        }
        if (!node->right_) {
            Node<T>* temp = node->left_;
            delete node;
            return temp;
        }

        Node<T>* temp = InorderSuccessor(node->right_);
        node->data_ = temp->data_;
        node->right_ = Remove(node->right_, temp->data_);
    }

    return node;
}

template<typename T>
size_t Size( Node<T>* node )
{
    if( !node )
        return 0;

    return static_cast<size_t>( 1 ) + Size( node->left_ ) + Size( node->right_ ) + Size( node->middle_ );
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
    
    return 1 + std::max( std::max( HeightOfNode( node->left_ ), HeightOfNode( node->right_ ) ), HeightOfNode( node->middle_ ) );
}

int main()
{
    Node<int>* root = new Node<int>( 4 );
    root = Insert(root, 20);
    root = Insert(root, 10);
    root = Insert(root, 20); // This goes to the middle of the first 20
    root = Insert(root, 30);

    std::cout << "PreOrder: " << std::endl;
    DepthFirstSearchTraversal( root, DFSTraversal::PRE_ORDER_ );

    std::cout << "InOrder: " << std::endl;
    DepthFirstSearchTraversal( root, DFSTraversal::IN_ORDER_ );

    std::cout << "PostOrder: " << std::endl;
    DepthFirstSearchTraversal( root, DFSTraversal::POST_ORDER_ );

    std::cout << "Breadth First Search: " << std::endl;
    BreadthFirstSearch( root );

    std::cout << "Finding 10, is found: " << ( Find( root, 10 ) != nullptr ) << std::endl;
    std::cout << "Finding 30, is found: " << ( Find( root, 30 ) != nullptr ) << std::endl;
    std::cout << "Finding -1, is found: " << ( Find( root, -1 ) != nullptr ) << std::endl;

    std::cout << "Size of BST: " << Size( root ) << std::endl;

    Remove( root, 10 );
    std::cout << "Size of BST after removal of 10: " << Size( root ) << std::endl;
    DepthFirstSearchTraversal( root, DFSTraversal::IN_ORDER_ );

    std::cout << "Depth of node with key -2: " << DepthOfNode( root, -2, 0 ) << std::endl;
    std::cout << "Depth of node with key 30: " << DepthOfNode( root, 30, 0 ) << std::endl;

    std::cout << "Height of the tree: " << HeightOfNode( root ) << std::endl;

    return 0;
}