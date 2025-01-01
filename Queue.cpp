#include <iostream>
#include <list>

/*
FIFO ( First in, first out ) data structure. 

Two different approaches:
Array -> assuming fixed size, but can change to dynamically adjusting structure i.e a vector
LinkedList

Not much difference from the stack just accessing which data first differently
The array queue uses two indexes instead of 1 like in the stack
*/

constexpr size_t ARRAY_QUEUE_SIZE_ = 100;

enum class StackOpertaions
{
    WRITE_ = 0,
    READ_,
    COUNT_,
};

/*
Using 2 different indexs (front and rear) to push and pop the correct positions
*/
template<class T, size_t N>
class ArrayQueue
{
public:
    void Push( const T& data )
    {
        if( rear_index_ >= capacity_ )
        {
            std::cout << "Stack out of space" << std::endl;
            return;
        }

        array_[rear_index_++] = data;

        if( front_index_ == -1 )
            front_index_ = 0;
    };

    void Pop()
    {
        if( Empty() )
        {
            std::cout << "Cannot pop further" << std::endl;
        }

        ++front_index_;

        //resetting indexs if we have no more data
        if( front_index_ > static_cast<int>( rear_index_ - 1 ) )
        {
            front_index_ = -1;
            rear_index_ = 0;
        }
    };

    const T& Data()
    {
        return array_[front_index_];
    }

    bool Empty()
    {
        return front_index_ == -1;
    }

private:
    T array_[N];
    int front_index_{ -1 };
    size_t rear_index_{ 0 };
    size_t capacity_{ N };
};


/*
Used std::list for quickness
Using own implementation of linked list (LinearLinkedList.cpp) would mean using:
InsertAtEnd() for Push();
DeleteAtBeginning() for Pop();
Would need to add function for getting data at front( head_->Print()? )

Only difference between this and stack is Push() to the back rather than at the front
*/
template<class T>
class LinkedlistQueue
{
public:
    void Push( const T& data )
    {
        list_.push_back( data );
    };

    void Pop()
    {
        if( list_.empty() )
        {
            std::cout << "Cannot pop further" << std::endl;
            return;
        }

        list_.pop_front();
    };

    const T& Data()
    {
        return list_.front();
    }

private:
    std::list<T> list_;
};

int main()
{
    ArrayQueue<size_t, ARRAY_QUEUE_SIZE_> array_queue;
    LinkedlistQueue<size_t> linked_list_queue;

    for( size_t i = 0; i < static_cast<size_t>( StackOpertaions::COUNT_ ); ++i )
    {
        for( size_t j = 0; j < ARRAY_QUEUE_SIZE_ ; ++j )
        {
            if( i == static_cast<size_t>( StackOpertaions::WRITE_ ) )
            {
                array_queue.Push( j );
                linked_list_queue.Push( j );
            }
            else
            {
                std::cout << "Array Queue Data: " << array_queue.Data() << std::endl;
                std::cout << "Linked List Queue Data: " << linked_list_queue.Data() << "\n" << std::endl;

                array_queue.Pop();
                linked_list_queue.Pop();
            }
        }
    }
}