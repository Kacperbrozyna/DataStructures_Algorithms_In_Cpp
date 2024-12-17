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
    std::iota( ids.begin(), ids.end(), 0 );

    while( std::cin >> p >> q )
    {
        int t = ids[p];

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
    std::iota( ids.begin(), ids.end(), 0 );

    while( std::cin >> p >> q )
    {
        //Find the roots of P and Q
        int root_q = ids[q];
        while( root_q != ids[root_q] )
            root_q = ids[root_q];

        while( p != ids[p] )
            p = ids[p];

        if( ids[p] == ids[root_q] )
        {
            std::cout << "Pair already connected \n" << std::endl;
            continue;
        }

        /*
        Point object p to the root of object q ( when the object points at itself = root )

        Given array      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
        Connect 3,4
        Array will be    { 0, 1, 2, 4, 4, 5, 6, 7, 8, 9 }
        Connect 4,9
        Array will be    { 0, 1, 2, 4, 9, 5 ,6, 7, 8, 9 }
        Connect 2,3
        Array will be    { 0, 1, 9, 4, 9, 5 ,6, 7, 8, 9 }
        */

        ids[p] = root_q;

        std::cout << "P is now pointing to root: " << ids[p] << std::endl;
    }
}

/*
To counteract the worst case scenario we add an extra array that holds the amount of children that the root has.
When we come to connecting objects together we compare the number of children that root of P and root of Q has,
depending on this connect the object with less children to the object with more.
*/
void WeightedQuickUnionAlgorithm()
{
    int p, q, id[MAX], sz[MAX];

    std::array<int, static_cast<size_t>( MAX )> ids;
    std::array<int, static_cast<size_t>( MAX )> children_objects;

    std::iota( ids.begin(), ids.end(), 0 );
    std::fill( children_objects.begin(), children_objects.end(), 1 );

    while( std::cin >> p >> q )
    {

        //Find the roots of P and Q
        while( q != ids[q] )
            q = ids[q];

        while( p != ids[p] )
            p = ids[p];

        if( ids[p] == ids[q] )
        {
            std::cout << "Pair already connected \n" << std::endl;
            continue;
        }

        //Connect the root with the lesser amount of children to the one with more
        if( children_objects[p] < children_objects[q] )
        {
            children_objects[q] += children_objects[p];
            ids[p] = q;
            std::cout << "Root of P is now pointing to root of Q: " << ids[p] << " which now has " << children_objects[q] << " children" << std::endl;
        }
        else
        {
            children_objects[p] += children_objects[q];
            ids[q] = ids[p];
            std::cout << "Root of Q is now pointing to root of P: " << ids[q] << " which now has " << children_objects[p] << " children" << std::endl;
        }
    }
}

int main()
{
   //QuickFindAlgorithm();
   //QuickUnionAlgorithm();
   WeightedQuickUnionAlgorithm();
}