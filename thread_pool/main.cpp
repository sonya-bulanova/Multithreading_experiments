#include <iostream>s
#include "optimized_thread.h"
#include <chrono>

using namespace std;

mutex coutLocker;
bool make_thread = true;

void quicksort(vector<int>& array, int left, int right)
{
    if (left >= right) return;
    int left_bound = left;
    int right_bound = right;

    long middle = array[(left_bound + right_bound) / 2];

    do {
        while (array[left_bound] < middle) {
            left_bound++;
        }
        while (array[right_bound] > middle) {
            right_bound--;
        }

        if (left_bound <= right_bound) {
            std::swap(array[left_bound], array[right_bound]);
            left_bound++;
            right_bound--;
        }
    } while (left_bound <= right_bound);

    if (make_thread && (right_bound - left > 10000))
    {

        auto f = async(launch::async, [&]() {
            quicksort(array, left, right_bound);
            });
        quicksort(array, left_bound, right);
    }
    else {
        quicksort(array, left, right_bound);
        quicksort(array, left_bound, right);
    }
}

int main()
{
	vector<int> arr;

	for (int i = 0; i <= 300; ++i)
		arr.push_back(rand() % 500);

	RequestHandler_2 rh;

    rh.push_task(quicksort, arr, 0, arr.size() - 1);
	return 0;
}
