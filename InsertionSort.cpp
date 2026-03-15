#include <vector>
#include <iostream>

template<typename T> 
void InsertionSort( std::vector<T>& vector_to_insert_into, T&& data_to_insert )
{
    vector_to_insert_into.push_back( data_to_insert );

    size_t current_index = vector_to_insert_into.size() - 1;
    while( current_index > static_cast<size_t>( 0 ) && vector_to_insert_into[current_index] < vector_to_insert_into[current_index - 1] )
    {
        std::swap( vector_to_insert_into[current_index], vector_to_insert_into[current_index - 1] );
        current_index--;
    }
};

int main()
{
    std::vector<int> insertion_vector;
    std::vector<int> sorted_vector{ 5,8,36,89,100 };
    std::vector<int> numbers_to_insert_from{ 100,5,8,36,89 };

    for( auto&& it : numbers_to_insert_from )
    {
        InsertionSort(insertion_vector, std::move( it ) );
    }

    std::cout << "Did Insertion sort work? " << ( insertion_vector == sorted_vector ) << std::endl;
}