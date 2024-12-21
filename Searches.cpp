#include <iostream>
#include <random>

constexpr size_t ARRAY_SIZE = 100;

//Standard search looking over a container
int SequentialSearch( const std::array<int, ARRAY_SIZE>& numb_array, int numb_to_find )
{
    for( size_t i = 0; i < ARRAY_SIZE; ++i )
    {
        if( numb_array[i] == numb_to_find )
            return i;
    }

    return -1;
}

int BinarySearch( std::array<int, ARRAY_SIZE>& numb_array, int numb_to_find )
{
    //For a binary seach to work we need to make sure the container is sorted.
    std::sort( numb_array.begin(), numb_array.end() );

    int left = 0;
    int right = static_cast<int>( ARRAY_SIZE - 1 );

    while( left <= right )
    {
        int mid = ( left + right ) / 2;

        if( numb_array[mid] == numb_to_find )
            return mid;
        else if( numb_array[mid] < numb_to_find )
            left = mid + 1;
        else
            right = mid - 1; 
    }

    return -1;
}

int main()
{
    std::array<int, ARRAY_SIZE> number_array;
    std::iota( number_array.begin(), number_array.end(), 0 );

    std::random_device rd;
    std::mt19937 random_engine;

    std::shuffle( number_array.begin(), number_array.end(), random_engine );

    int number_to_find;

    while( std::cin >> number_to_find )
    {
        //int index = SequentialSearch( number_array, number_to_find );
        int index = BinarySearch( number_array, number_to_find );

        if( index )
            std::cout << "Found number at index: " << index << std::endl;
        else
            std::cout << "Did not find " << number_to_find << std::endl;
    }
}