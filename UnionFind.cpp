#include <iostream>
#include <numeric>

/*
Solving the connectivity problem using union find algorithms.

Assuming pair P,Q -> Connect Object P to Object Q
Givin a series of pairs 
Decide whether a pair is connected, if not then connect the pair.
*/

constexpr int MAX = 10;

//NM instructions to process M union operations among N objects
void QuickFindAlgorithm()
{
    int p,q;
    std::array<int, static_cast<size_t>( MAX )> ids;
    std::iota( ids.begin(), ids.end(), 0);

    while( std::cin >> p >> q )
    {
        int t = ids[p];

        //Pair is already connected
        if( t == ids[q] )
        {
            std::cout << "Pair already connected \n" << std::endl;
            continue;
        }
        
        /*
        Go through each object and assign it to object q if it is equal to object p

        Given array      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
        Connect 1,3
        Array will be    { 0, 3, 2, 3, 4, 5, 6, 7, 8, 9 }
        Connect 3,9
        Array will be    { 0, 9, 2, 9, 4, 5 ,6, 7, 8, 9 }
        */
        for( int i = 0; i < MAX; ++i )
        {
            if( ids[i] == t )
            {
                ids[i] = ids[q];
                std::cout << "Connected Pair: " << i << " " << q << std::endl;
            }
        }
    }
};

/* 
For the price of improving the union operation the find operation will take longer
compared to the algorithm above, the objects here might need to take several links to get to the root unlike the other algoritm
The worst case scenario is if the union operation links a set of pairs where n-1 points to n-2 and so forth which forms a straight line
meaning the find opertion could check each link (n-1).
*/ 
void QuickUnionAlgorithm()
{
    int p,q;
    std::array<int, static_cast<size_t>( MAX )> ids;
    std::iota( ids.begin(), ids.end(), 0);

    while( std::cin >> p >> q )
    {
        //Pair is already connected
        if( ids[p] == ids[q] )
        {
            std::cout << "Pair already connected \n" << std::endl;
            continue;
        }

        /*
        Go through object p and assign it to the root ( object points at itself )

        Given array      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
        Connect 3,4
        Array will be    { 0, 1, 2, 4, 4, 5, 6, 7, 8, 9 }
        Connect 4,9
        Array will be    { 0, 1, 2, 4, 9, 5 ,6, 7, 8, 9 }
        Connect 4,9
        Array will be    { 0, 1, 9, 4, 9, 5 ,6, 7, 8, 9 }
        */
        int t = q;

        while( t != ids[t] )
        {
            t = ids[t];
        }

        ids[p] = t;

        std::cout << "P is now pointing to root: " << ids[p] << std::endl;
    }
}

int main()
{
   //QuickFindAlgorithm();
   QuickUnionAlgorithm();
}