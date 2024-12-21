#include <memory>
#include <iostream>

/*
My implementation of a linearly linked list
Using shared_ptr instead of raw pointers

TODO:
Test it works.. (It does build)
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
        if( !head_ || position == 1 )
        {
            InsertAtBeginning( data );
            return;
        }

        if( position >= size_ )
        {
            std::cout << "Position is out of range" << std::endl;
            return;
        }

        std::shared_ptr<Node> temp{ head_->next_node_ };
        for( size_t i = 2; i < position - static_cast<size_t>( 1 ) && temp; ++i )
            temp = temp->next_node_;

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

        if( position == 1 )
        {
            DeletAtBeginning();
            return;
        }

        if( position >= size_ )
        {
            std::cout << "Position is out of range" << std::endl;
            return;
        }

        std::shared_ptr<Node> temp{ head_ };
        for( size_t i = 1; i < position - static_cast<size_t>( 1 ); ++i )
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
}
