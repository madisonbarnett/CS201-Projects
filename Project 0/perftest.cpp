#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>

using namespace std;

// Change this to merge or insertion to analyze performance
template< class RandomIt > 
constexpr void insertionsort ( RandomIt first, RandomIt last ) {
    RandomIt j = first+1;
    while (j != last) {
        int key = *j;
        RandomIt i = j - 1;

        while (i >= first && *i > key) {
            *(i+1) = *i;
            i--;
        }
        *(i+1) = key;
        j++;
    }
}

int main(int argc, char *argv[]) {

	std::cout << "Problem Size\tTime Taken (seconds)" << std::endl;
	for (int size = 10; size <= 100000000; size *= 10) {
	
		int *a = new int[size];
        //int *temp = new int[size];
	
		std::generate(a, a+size, std::rand);
		auto starttime = std::chrono::steady_clock::now();
		insertionsort(a, a+size);
		auto endtime = std::chrono::steady_clock::now();
		std::chrono::duration<double> timetaken = endtime - starttime;
		std::cout << size << "\t" << timetaken.count() << std::endl;

		delete[] a;
	}

	return 0;
}