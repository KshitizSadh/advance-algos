#include <bits/stdc++.h>
using namespace std;

template <typename RandomIt, typename Compare>
RandomIt partition(RandomIt first, RandomIt last, RandomIt pivotIt, Compare comp) {
    using std::swap;
    swap(*(last - 1), *pivotIt);

    auto store = first;
    for (auto it = first; it != last - 1; ++it) {
        if (comp(*it, *(last - 1))) {
            swap(*store, *it);
            ++store;
        }
    }
    swap(*store, *(last - 1));
    return store;
}

template <typename RandomIt, typename Compare = std::less<>>
typename std::iterator_traits<RandomIt>::value_type
randomized_select(RandomIt first, RandomIt last, size_t k, Compare comp = Compare()) {
    static random_device rd;
    static mt19937 gen(rd());

    while (true) {
        size_t n = last - first;
        if (n == 1) return *first;

        uniform_int_distribution<size_t> dist(0, n - 1);
        RandomIt pivotIt = first + dist(gen);

        RandomIt mid = partition(first, last, pivotIt, comp);
        size_t pivotIndex = mid - first;

        if (k == pivotIndex)
            return *mid;
        else if (k < pivotIndex)
            last = mid;
        else {
            k -= (pivotIndex + 1);
            first = mid + 1;
        }
    }
}

int main() {
    vector<int> data = {7, 2, 9, 4, 1, 6};
    size_t k = 2;

    int value = randomized_select(data.begin(), data.end(), k);
    cout << k << "-th smallest element = " << value << "\n";
}
