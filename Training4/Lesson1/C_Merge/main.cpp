#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

auto const FASTIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
    }();

    std::vector<int> Read()
    {
        int n;
        std::cin >> n;
        std::vector<int> arr(n);
        for (int& i : arr) {
            std::cin >> i;
        }
        return arr;
    }

    int main()
    {
        auto arr = Read();
        auto arr1 = Read();
        std::vector<int> res(arr.size() + arr1.size());
        std::merge(arr.begin(), arr.end(), arr1.begin(), arr1.end(), res.begin());
        for (int i : res) {
            std::cout << i << ' ';
        }
    }
