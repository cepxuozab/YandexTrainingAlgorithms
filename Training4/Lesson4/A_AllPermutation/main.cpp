#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    int i = 1;
    for (int& a : arr)
        a = i++;
    do {
        for (int a : arr) {
            std::cout << a;
        }
        std::cout << '\n';
    } while (std::next_permutation(arr.begin(), arr.end()));
}
