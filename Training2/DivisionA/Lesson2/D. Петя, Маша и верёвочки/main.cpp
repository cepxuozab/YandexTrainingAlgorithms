#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
int main()
{
    int n;
    std::cin >> n;
    std::vector<int> ropes(n);
    for (auto& rope : ropes) {
        std::cin >> rope;
    }
    int max_length = *std::max_element(ropes.begin(), ropes.end());
    int total_length = std::reduce(ropes.begin(), ropes.end());
    int diff = total_length - max_length;
    if (max_length > diff) {
        std::cout << max_length - diff << std::endl;
    } else {
        std::cout << total_length << std::endl;
    }
    return 0;
}
