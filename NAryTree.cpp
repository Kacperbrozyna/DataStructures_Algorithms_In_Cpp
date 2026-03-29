#include <iostream>
#include <queue>

template<typename T>
struct Node
{
    Node( T data )
        : data_( data )
        {}

    T data_;
    std::vector<std::unique_ptr<Node<T>>> children_;

    void InsertRoot(T data)
    {
        children_.push_back( std::make_unique<Node<T>>( data ) );
    }

    bool Insert(T parent_value, T data)
    {
        Node<T>* found_node{ FindNode(this, parent_value ) };
        if( !found_node )
        {
            return false;
        }

        found_node->children_.push_back( std::make_unique<Node<T>>( data ) );

        return true;
    }

    Node<T>* Find( T data )
    {
        return FindNode( this, data ); 
    }

    size_t Size( Node<T>* node )
    {
        if( !node )
        {
            return 0;
        }

        size_t total{ 1 };

        for( const auto& child : node->children_ )
        {
            total += Size( child.get() );
        }

        return total;
    }

    template<typename T>
    bool RemoveNode(Node<T>* node, const T& value)
    {
        if( !node )
        {
            return false;
        }

    for(auto it = node->children_.begin(); it != node->children_.end(); ++it)
    {
            if( (*it)->data_ == value)
            {
                node->children_.erase(it);
                return true;
            }

            if( RemoveNode( it->get(), value ) )
                return true;
        }

        return false;   
    }

private:
    Node<T>* FindNode( Node<T>* node, T data )
    {
        if( node == nullptr )
        {
            return nullptr;
        }

        if( node->data_ == data )
        {
            return node;
        }

        for( auto& child : node->children_)
        {
            Node<T>* child_node{ FindNode(child.get(), data) };
            if( child_node )
            {
                return child_node;
            }
        }

        return nullptr;
    };
};

enum class DFSTraversal
{
    PRE_ORDER_,             // Node, Children
    POST_ORDER_,            // Children, Node
};

template<typename T>
void DepthFirstSearchTraversal( Node<T>* node, DFSTraversal dfs_traversal_option )
{
    if( node == nullptr )
        return;

    if( dfs_traversal_option == DFSTraversal::PRE_ORDER_ )
    {
        std::cout << node->data_ << std::endl;
    }

    for( const auto& node : node->children_ )
    {
        DepthFirstSearchTraversal( node.get(), dfs_traversal_option );
    }

    if( dfs_traversal_option == DFSTraversal::POST_ORDER_ )
    {
        std::cout << node->data_ << std::endl;
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
        const Node<T>* temp_node = node_queue.front();
        std::cout << temp_node->data_ << std::endl;

        for( const auto& node : temp_node->children_ )
        {
            if( !node )
            {
                continue;
            }

            node_queue.push( node.get() );
        }

        node_queue.pop();
    }
}

template<typename T>
int DepthOfNode(Node<T>* node, const T& value, int depth)
{
    if( !node)
    {
        return -1;
    }

    if( node->data_ == value )
    {
        return depth;
    }

    for( auto& child : node->children_ )
    {
        int result = DepthOfNode(child.get(), value, depth + 1);
        if( result != -1 )
        {
            return result;
        }
    }

    return -1;
}

template<typename T>
int HeightOfNode(Node<T>* node)
{
    if( !node )
        return -1;

    int max_child_height = -1;

    for( auto& child : node->children_ )
    {
        max_child_height = std::max(max_child_height, HeightOfNode( child.get() ) );
    }

    return 1 + max_child_height;
}

int main()
{
    std::unique_ptr<Node<int>> root = std::make_unique<Node<int>>(4);
    root->InsertRoot( 8 );

    root->Insert(8, 20);
    root->Insert(8, 10);

    root->Insert(20, 25);
    root->Insert(20, 30);

    root->Insert(30, 50);

    std::cout << "PreOrder: " << std::endl;
    DepthFirstSearchTraversal( root.get(), DFSTraversal::PRE_ORDER_ );

    std::cout << "PostOrder: " << std::endl;
    DepthFirstSearchTraversal( root.get(), DFSTraversal::POST_ORDER_ );

    std::cout << "Breadth First Search: " << std::endl;
    BreadthFirstSearch( root.get() );

    std::cout << "Finding 10, is found: " << ( root->Find( 10 ) != nullptr ) << std::endl;
    std::cout << "Finding 30, is found: " << ( root->Find( 30 ) != nullptr ) << std::endl;
    std::cout << "Finding -1, is found: " << ( root->Find( -1 ) != nullptr ) << std::endl;

    std::cout << "Size of BST: " << root->Size( root.get() ) << std::endl;

    root->RemoveNode( root.get(), 10 );
    std::cout << "Size of BST after removal of 10: " << root->Size( root.get() ) << std::endl;

    std::cout << "Depth of node with key -2: " << DepthOfNode( root.get(), -2, 0 ) << std::endl;
    std::cout << "Depth of node with key 30: " << DepthOfNode( root.get(), 30, 0 ) << std::endl;

    std::cout << "Height of the tree: " << HeightOfNode( root.get() ) << std::endl;
    return 0;
}