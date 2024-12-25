#include <memory>
#include <iostream>

/*
My implementation of a doubly linked list
Using raw pointers for this implementation

could also store a tail_ in addition to head_ to make "iteration" over the container easier
hence see PrintAllNodes( true ); 
*/

template<typename T>
struct Node
{
    T data_;
    Node<T>* next_node_;
    Node<T>* prev_node_;

    Node( const T& data, Node<T>* next_node, Node<T>* prev_node )
    : data_( data )
    , next_node_( next_node ) 
    , prev_node_( prev_node ) 
    {}

    ~Node()
    {
        std::cout << "Node Removed" << std::endl;
    }
};

template<class T>
class LinkedList
{

public:

    LinkedList() = default;
    ~LinkedList(){ Clear(); };

    void InsertAtBeginning( const T& data )
    {
        Node<T>* new_node{ new Node<T>( data, nullptr, nullptr ) };
        if( head_ )
        {
            new_node->next_node_ = head_;
            head_->prev_node_ = new_node;
        }

        head_ = new_node;
        ++size_;
    };

    void InsertAtEnd( const T& data )
    {
        if( !head_ )
        {
            InsertAtBeginning( data );
            return;
        }

        Node<T>* tail{ head_ };

        while( tail->next_node_ )
            tail = tail->next_node_;
        
        tail->next_node_ = new Node<T>( data, nullptr, tail );
        ++size_;
        
    };

    void InsertAtPosition( const T& data, size_t position )
    {
        if( !head_ || position == 0 )
        {
            InsertAtBeginning( data );
            return;
        }

        if( position > size_ )
        {
            std::cout << "Position is out of range" << std::endl;
            return;
        }

        Node<T>* temp{ head_ };
        for( size_t i = 1; i < position; ++i )
        { 
            if( !temp )
            {
                std::cout << "Position out of range" << std::endl;
                return;
            }
            
            temp = temp->next_node_;
        }

        Node<T>* new_node{ new Node<T>( data, temp->next_node_, temp ) };
        if( temp->next_node_ )
            temp->next_node_->prev_node_ = new_node;

        temp->next_node_ = new_node;
        ++size_;
    };

    void DeleteAtBeginning()
    {
        if( !head_ )
        {
            std::cout << "List is empty" << std::endl;
            return;
        }
        
        Node<T>* temp{ head_ };
        head_ = head_->next_node_;
        head_->prev_node_ = nullptr;

        delete temp;

        --size_;
    };

    void DeleteAtEnd()
    {
        if( !head_ )
        {
            std::cout << "List is empty" << std::endl;
            return;
        }

        if( !head_->next_node_ )
        {
            delete head_;
            head_ = nullptr;

            --size_;

            return;
        }

        Node<T>* temp{ head_ };
        while( temp->next_node_->next_node_ )
            temp = temp->next_node_;

        delete temp->next_node_;
        temp->next_node_ = nullptr;
        --size_;
    };

    void DeleteAtPosition( size_t position )
    {
        if( !head_ )
        {
            std::cout << "List is empty" << std::endl;
            return;
        }

        if( position == 0 )
        {
            DeleteAtBeginning();
            return;
        }

        if( position > size_ )
        {
            std::cout << "Position is out of range" << std::endl;
            return;
        }

        Node<T>* temp{ head_ };
        for( size_t i = 1; i < position; ++i )
        {
            temp = temp->next_node_;

            if( !temp || !temp->next_node_ )
            {
                std::cout << "Position out of range" << std::endl;
                return;
            }
        }

        Node<T>* delete_node{ temp->next_node_ };
        temp->next_node_ = temp->next_node_->next_node_;

        delete delete_node;

        if( temp->next_node_ )
            temp->next_node_->prev_node_ = temp;

        --size_;
    };

    void PrintAllNodes( bool reverse ) const
    {
        if( !head_ )
        {
            std::cout << "List is empty" << std::endl;
            return;
        }

        const Node<T>* temp{ head_ };

        if( !reverse )
        {
            while( temp )
            {
                std::cout << "Data: " << temp->data_ << std::endl;
                temp = temp->next_node_;
            }
        }
        else
        {
            while( temp->next_node_ )
                temp = temp->next_node_;

            const Node<T>* prev_node{ temp };
            while( prev_node )
            {
                std::cout << "Data: " << prev_node->data_ << std::endl;
                prev_node = prev_node->prev_node_;
            }
        }
    };

    void Reverse()
    {
        if( !size_ )
            return;

        Node<T>* curr_node{ head_ };
        Node<T>* temp_node{ nullptr };

        while( curr_node )
        {
            temp_node = curr_node->next_node_;
            curr_node->next_node_ = curr_node->prev_node_;
            curr_node->prev_node_ = temp_node;
        
            if( !temp_node )
            {
                head_ = curr_node;
                break;
            }

            curr_node = temp_node;
        }
    };

    void Clear()
    {
        while( head_ )
        {
            Node<T>* temp = head_->next_node_;

            delete head_;

            head_ = temp;
        }
            
        size_ = 0;
    }

    size_t Size() const
    {
        return size_;
    }

private:
    Node<T>* head_{ nullptr };
    size_t size_{ 0 };
};

int main()
{
    LinkedList<int> list;

    //Almost like unit tests would be a better alternative...
    for( int i = 0; i < 5; ++i )
        list.InsertAtBeginning( i );

    list.PrintAllNodes(true);

    list.DeleteAtEnd();
    list.PrintAllNodes(false);

    list.InsertAtPosition( 10 , 2 );

    list.DeleteAtPosition(4);
    list.PrintAllNodes(false);

    list.Reverse();
    list.PrintAllNodes(false);

    list.Clear();
    list.PrintAllNodes(false);
}
