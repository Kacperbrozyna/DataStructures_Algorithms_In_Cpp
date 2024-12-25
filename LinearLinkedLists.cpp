#include <memory>
#include <iostream>

/*
My implementation of a linearly linked list
Using shared_ptr instead of raw pointers

To make this list circular linked, the (tail) last_node->next_node_ should point to head_

more stuff that I 
CAN-DO:
Move & Copy Ctor
sorting (insertion sort?)
exchange 2 nodes in a given list
(goes for doubly linked list as well)
*/

template<typename T>
struct Node
{
    T data_;
    std::shared_ptr<Node> next_node_;

    Node( const T& data, std::shared_ptr<Node<T>> next_node )
    : data_( data )
    , next_node_( next_node ) 
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
    void InsertAtBeginning( const T& data )
    {
        std::shared_ptr<Node<T>> new_node{ std::make_shared<Node<T>>( data, head_ ) };
        head_ = new_node;
        ++size_;
    };

    void InsertAtEnd( const T& data )
    {
        std::shared_ptr<Node<T>> new_node{ std::make_shared<Node<T>>( data, nullptr ) };
        ++size_;

        if( !head_ )
        {
            head_ = new_node;
            return;
        }

        std::shared_ptr<Node<T>> tail{ head_ };

        while( tail->next_node_ )
            tail = tail->next_node_;
        
        tail->next_node_ = new_node;
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

        std::shared_ptr<Node<T>> temp{ head_ };
        for( size_t i = 1; i < position; ++i )
        { 
            if( !temp )
            {
                std::cout << "Position out of range" << std::endl;
                return;
            }
            
            temp = temp->next_node_;
        }

        std::shared_ptr<Node<T>> new_node{ std::make_shared<Node<T>>( data, temp->next_node_ ) };
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

        head_ = head_->next_node_;
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
            head_ = nullptr;
            --size_;
            return;
        }

        std::shared_ptr<Node<T>> temp{ head_ };
        while( temp->next_node_->next_node_ )
            temp = temp->next_node_;

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
            DeletAtBeginning();
            return;
        }

        if( position > size_ )
        {
            std::cout << "Position is out of range" << std::endl;
            return;
        }

        std::shared_ptr<Node<T>> temp{ head_ };
        for( size_t i = 1; i < position; ++i )
        {
            temp = temp->next_node_;

            if( !temp || !temp->next_node_ )
            {
                std::cout << "Position out of range" << std::endl;
                return;
            }
        }

        temp->next_node_ = temp->next_node_->next_node_;
        --size_;
    };

    void PrintAllNodes() 
    {
        if( !head_ )
        {
            std::cout << "List is empty" << std::endl;
            return;
        }

        std::shared_ptr<Node<T>> temp{ head_ };

        while( temp )
        {
            std::cout << "Data: " << temp->data_ << std::endl;
            temp = temp->next_node_;
        }
    };

    void Reverse()
    {
        if( !size_ )
            return;

        std::shared_ptr<Node<T>> prev_node, curr_node, next_node;
        curr_node = head_;

        while( curr_node )
        {
            next_node = curr_node->next_node_;
            curr_node->next_node_ = prev_node;
            prev_node = curr_node;
            curr_node = next_node;
        }

        head_ = prev_node;
    };

    void Clear()
    {
        while( head_ )
            head_ = head->next_node_;
            
        size_ = 0;
    }

    size_t Size() const
    {
        return size_;
    }

private:
    std::shared_ptr<Node<T>> head_;
    size_t size_{ 0 };
};

int main()
{
    LinkedList<int> list;

    //Almost like unit tests would be a better alternative...
    for( int i = 0; i < 5; ++i )
        list.InsertAtBeginning( i );


    list.PrintAllNodes();

    list.DeleteAtEnd();
    list.PrintAllNodes();

    list.InsertAtPosition( 10 , 2 );

    list.DeleteAtPosition(4);
    list.PrintAllNodes();

    list.Reverse();
    list.PrintAllNodes();

    list.Clear();
    list.PrintAllNodes();
}
