#include <iostream>
#include <vector>

using namespace std;

/*
   Name: Madison Barnett
   Email: mtbarnett@crimson.ua.edu  
   Course Section: Fall 2024 CS 201 - 002
   Homework #: 0
*/ 

template< class RandomIt > 
constexpr void insertionsort ( RandomIt first, RandomIt last ) {
    // 1st element is already considered sorted, so iterator j begins at 2nd elements and scans through array until reaching last
    RandomIt j = first+1;
    while (j != last) {
        auto key = *j;
        // Iterator i points to right before j to begin comparisons
        RandomIt i = j - 1;

        while (i >= first && *i > key) {
            *(i+1) = *i;
            i--;
        }
        *(i+1) = key;
        j++;
    }
}