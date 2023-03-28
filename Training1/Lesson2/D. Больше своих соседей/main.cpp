#include <algorithm>
#include <iostream>
#include <vector>
void print(std::vector<int64_t> const& a)
{
    for (int64_t i : a) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}
int main()
{
    // freopen("input.txt", "r", stdin);
    int ans = 0;
    std::vector<int> arr;
    int x;
    while (std::cin >> x) {
        arr.push_back(x);
    }
    for (int i = 1; i + 1 < arr.size(); ++i) {
        if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
            ans++;
        }
    }
    std::cout << ans << std::endl;
}
