// quicksort.cpp
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void quicksort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (arr[j] < pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    quicksort(arr, left, i);
    quicksort(arr, i + 2, right);
}

int main() {
    srand(time(nullptr));
    vector<int> arr(10000000);
    for (int& x : arr) x = rand();
    quicksort(arr, 0, arr.size() - 1);
    return 0;
}
