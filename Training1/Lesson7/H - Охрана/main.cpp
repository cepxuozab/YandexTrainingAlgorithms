#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>

[[maybe_unused]] auto const FastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

auto main() -> int
{
    assert(freopen("input.txt", "rt", stdin));
    assert(freopen("output.txt", "wt", stdout));

    int const MAX = 10000;
    std::array<short, MAX> used {};
    std::array<short, MAX> paint {};
    std::array<short, MAX> who {};
    std::array<std::pair<short, short>, MAX> arr {};

    int k;
    std::cin >> k;

    for (int iter = 0; iter < k; ++iter) {
        int n;
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i].first >> arr[i].second;
        }

        paint.fill(0);
        who.fill(-1);

        bool fail = false;

        for (int j = 0; j < n; ++j) {
            for (int i = arr[j].first; i < arr[j].second; i++) {
                paint[i]++;
                who[i] = j;
                if (paint[i] > 2) {
                    fail = true;
                    break;
                }
            }
            if (fail) {
                break;
            }
        }

        used.fill(0);

        if (auto it = std::find(paint.begin(), paint.end(), 0); it != paint.end()) {
            fail = true;
        }

        if (!fail) {
            for (int i = 0; i < MAX; ++i) {
                if (paint[i] == 1) {
                    used[who[i]] = 1;
                }
            }
        }

        if (std::count(used.begin(), used.begin() + n, 0) != 0) {
            fail = true;
        }

        !fail
            ? printf("Accepted\n")
            : printf("Wrong Answer\n");
    }
    return 0;
}
