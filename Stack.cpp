#include <iostream>
#include <list>

/*
LIFO ( Last in, first out ) data structure. 

Two different approaches:
Array -> assuming fixed size, but can change to dynamically adjusting structure i.e a vector
LinkedList
*/

constexpr size_t ARRAY_STACK_SIZE_ = 100;

enum class StackOpertaions
{
    WRITE_ = 0,
    READ_,
    COUNT_,
};

/*
Using an index to move around the array in this implementation
*/
template<class T, size_t N>
class ArrayStack
{
public:
    void Push( const T& data )
    {
        if( index_ >= static_cast<int>( capacity_ ) )
        {
            std::cout << "Stack out of space" << std::endl;
            return;
        }

        array_[++index_] = data;
    };

    void Pop()
    {
        if( index_ < 0 )
        {
            std::cout << "Cannot pop further" << std::endl;
        }

        --index_;
    };

    const T& Data()
    {
        return array_[index_];
    }

private:
    T array_[N];
    int index_{ -1 };
    size_t capacity_{ N };
};


/*
Used std::list for quickness
Using own implementation of linked list (LinearLinkedList.cpp) would mean using:
InsertAtBeginning() for Push();
DeleteAtBeginning() for Pop();
Would need to add function for getting data at front( head_->Print()? )
*/
template<class T>
class LinkedlistStack
{
public:
    void Push( const T& data )
    {
        list_.push_front( data );
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
    ArrayStack<size_t, ARRAY_STACK_SIZE_> array_stack;
    LinkedlistStack<size_t> linked_list_stack;

    for( size_t i = 0; i < static_cast<size_t>( StackOpertaions::COUNT_ ); ++i )
    {
        for( size_t j = 0; j < ARRAY_STACK_SIZE_ ; ++j )
        {
            if( i == static_cast<size_t>( StackOpertaions::WRITE_ ) )
            {
                array_stack.Push( j );
                linked_list_stack.Push( j );
            }
            else
            {
                std::cout << "Array Stack Data: " << array_stack.Data() << std::endl;
                std::cout << "Linked List Stack Data: " << linked_list_stack.Data() << "\n" << std::endl;

                array_stack.Pop();
                linked_list_stack.Pop();
            }
        }
    }
}