#include <memory>
#include <iostream>

/*
My implementation of a linearly linked list
Using shared_ptr instead of raw pointers

To make this list circular linked, the last node (tail) should point to head_

TODO:
Change to template
*/

struct Node
{
    int data_;
    std::shared_ptr<Node> next_node_;

    Node( int data, std::shared_ptr<Node> next_node )
    : data_( data )
    , next_node_( next_node ) 
    {}

    ~Node()
    {
        std::cout << "Node Removed" << std::endl;
    }
};

class LinkedList
{
public:
    void InsertAtBeginning( int data )
    {
        std::shared_ptr<Node> new_node{ std::make_shared<Node>( data, head_ ) };
        head_ = new_node;
        ++size_;
    };

    void InsertAtEnd( int data )
    {
        std::shared_ptr<Node> new_node{ std::make_shared<Node>( data, nullptr ) };
        ++size_;

        if( !head_ )
        {
            head_ = new_node;
            return;
        }

        std::shared_ptr<Node> tail{ head_ };

        while( tail->next_node_ )
            tail = tail->next_node_;
        
        tail->next_node_ = new_node;
    };

    void InsertAtPosition( int data, size_t position )
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

        std::shared_ptr<Node> temp{ head_ };
        for( size_t i = 1; i < position; ++i )
        { 
            if( !temp )
            {
                std::cout << "Position out of range" << std::endl;
                return;
            }
            
            temp = temp->next_node_;
        }

        std::shared_ptr<Node> new_node{ std::make_shared<Node>( data, temp->next_node_ ) };
        temp->next_node_ = new_node;
        ++size_;
    };

    void DeletAtBeginning()
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

        std::shared_ptr<Node> temp{ head_ };
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

        std::shared_ptr<Node> temp{ head_ };
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

        std::shared_ptr<Node> temp{ head_ };

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

        std::shared_ptr<Node> prev_node, curr_node, next_node;
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
        //should cause a cascade of deletes due to smart pointers;
        head_ = nullptr;
        size_ = 0;
    }

    size_t Size()
    {
        return size_;
    }

private:
    std::shared_ptr<Node> head_;
    size_t size_{ 0 };
};

int main()
{
    LinkedList list;

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
