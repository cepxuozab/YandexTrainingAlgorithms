#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>


void solve()
{
    int n;
    if (!(std::cin >> n)) return;


    std::vector<int64_t> a(n);
    for (auto& i : a)std::cin >> i;


    int l = 1;
    int r = n;

    int64_t left_sum = a[0];
    int64_t right_sum = a[n - 1];

    int64_t best_diff = std::abs(left_sum - right_sum);
    int best_l = l;
    int best_r = r;


    while (l + 1 < r)
    {
        if (left_sum < right_sum)
        {
            l += 1;
            left_sum += a[l - 1];
        }
        else
        {
            r -= 1;
            right_sum += a[r - 1];
        }

        int64_t diff = std::abs(left_sum - right_sum);
        if (diff < best_diff)
        {
            best_diff = diff;
            best_l = l;
            best_r = r;
        }
    }


    std::cout << best_diff << " " << best_l << " " << best_r << "\n";
}

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}
