#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <iterator>
#include <algorithm>
#include <limits>

using namespace std;

/*
   Name: Madison Barnett
   Email: mtbarnett@crimson.ua.edu  
   Course Section: Fall 2024 CS 201 - 002
   Homework #: 0
*/ 

template< class RandomIt > 
constexpr void mergesort ( RandomIt first, RandomIt last, RandomIt tempstart ) {
    //Calculate middle and assign it to an iterator
    if (distance(first,last) > 1) {
        RandomIt middle = first + (distance(first, last)/2);

        //Recursively call mergesort until all items are separated
        mergesort(first, middle, tempstart);
        mergesort(middle, last, tempstart);

        //Merge subarrays using tempstart iterator pointing to temp memory
        copy(first, last, tempstart);
        RandomIt left = tempstart;
        RandomIt right = tempstart + distance(first, middle);
        RandomIt tempEnd = tempstart + distance(first, last);

        RandomIt k = first;

        while (k != last) {
            //if all of left subarray is already sorted
            if (left == tempstart + distance(first, middle)) {
                *k = *right;
                right++;
            }
            //if all of right subarray is already sorted
            else if (right == tempEnd) {
                *k = *left;
                left++;
            }
            else if (*left <= *right) {
                *k = *left;
                left++;
            }
            else {
                *k = *right;
                right++;
            }
            k++;
        }
    }
}
