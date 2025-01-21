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
constexpr void mergesort ( RandomIt first, RandomIt last, RandomIt tempstart ) {
    // A = first, p = tempstart, r = number of elements ?
    if (distance(first,last) > 1) {
        RandomIt middle = first + (distance(first, last)/2);

        mergesort(first, middle, tempstart);
        mergesort(middle, last, tempstart);
        //merge(first, tempstart, last);

        copy(first, last, tempstart);
        RandomIt left = tempstart;
        RandomIt right = tempstart + distance(first, middle);
        RandomIt tempEnd = tempstart + distance(first, last);

        RandomIt k = first;

        while (k != last) {
            if (left == tempstart + distance(first, middle)) {
                *k = *right;
                right++;
            }
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


int main(int argc, char *argv[]) {
	int a0[] = {56, 23, 11, 64, 43};
    int temp_array[5];
	std::array<int, 5> a1 = {5, 4, 3, 2, 1};
    array<int, 5> tempA1;
	std::array<std::string, 5> a2 = {"lion", "dog", "cat", "fox", "pig"};
    array<string, 5> tempA2;
	std::vector<double> v = {4.2, 3.1, 5.6, 2.8, 1.9};
    vector<double> tempV(v.size());

	mergesort(a0, a0+5, temp_array);
	print(a0, a0+5);

	mergesort(&a0[0], &a0[5], &temp_array[0]);
	print(&a0[0], &a0[5]);

	mergesort(a1.begin(), a1.end(), tempA1.begin());
	print(a1.begin(), a1.end());

	mergesort(a2.begin(), a2.end(), tempA2.begin());
	print(a2.begin(), a2.end());

	std::reverse(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

	mergesort(a2.begin(), a2.end(), tempA2.begin());
	print(a2.begin(), a2.end());

	mergesort(v.begin(), v.end(), tempV.begin());
	print(v.begin(), v.end());

	return 0;
}