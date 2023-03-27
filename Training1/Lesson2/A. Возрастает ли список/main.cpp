#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    std::vector<int> arr(std::istream_iterator<int>(std::cin), {});
    std::adjacent_difference(arr.begin(), arr.end(), arr.begin());
    auto flag = std::all_of(std::next(arr.begin()), arr.end(), [](int a) { return a > 0; });
    flag ? puts("YES") : puts("NO");
}
