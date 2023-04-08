#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <numeric>
#include <queue>
#include <ranges>
#include <unordered_set>

using namespace std;
namespace rng = std::ranges;
namespace view = rng::views;

int main()
{
    int N = 9;
    cin >> N;
    vector<int> cubes;
    int i = 1;
    while (i * i * i <= N) {
        cubes.push_back(i * i * i);
        ++i;
    }
    vector<int> dp(N + 1);
    dp[0] = 0;
    dp[1] = 1;
    auto nums = view::iota(2, N + 1);
    for (int num : nums) {
        int min_cube_count = dp[num - 1] + 1;
        auto cube = rng::upper_bound(cubes, num);
        for (auto it = cubes.begin(); it != cube; ++it) {
            if (dp[num - *it] + 1 < min_cube_count)
                min_cube_count = dp[num - *it] + 1;
            dp[num] = min_cube_count;
        }
    }
    cout << dp[N];
}
