#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template< class RandomIt >
void print(RandomIt start, RandomIt end) {
	while (start != end) {
		std::cout << *start << " ";
		++start;
	}
	std::cout << std::endl;
}

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

int main(int argc, char *argv[]) {
    // Temporary storage should match the size of the array/vector you're sorting

    int a0[] = {56, 23, 11, 64, 43};
    vector<int> temp_int_a0(5); // Size matching a0

	std::array<int, 5> a1 = {5, 4, 3, 2, 1};
    vector<int> temp_int_a1(5); // Size matching a1

	std::array<std::string, 5> a2 = {"lion", "dog", "cat", "fox", "pig"};
    vector<string> temp_str(5); // Size matching a2

	std::vector<double> v = {4.2, 3.1, 5.6, 2.8, 1.9};
    vector<double> temp_double(v.size()); // Size matching v

    // Sorting for different types
	insertionsort(a0, a0 + 5);
	print(a0, a0 + 5);

	insertionsort(a1.begin(), a1.end());
	print(a1.begin(), a1.end());

	insertionsort(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

	insertionsort(v.begin(), v.end());
	print(v.begin(), v.end());

	return 0;
}
