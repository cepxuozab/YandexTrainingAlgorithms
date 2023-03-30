#include <algorithm>
#include <array>
#include <climits>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

auto make_vector(int L, int x1, int d, int a, int c, int m) -> std::vector<int>
{
    std::vector<int> arr{ x1 };
    arr.resize(L);
    for (int i = 1; i < L; ++i) {
        arr[i] = arr[i - 1] + d;
        d = ((a * d + c) % m);
    }

    return arr;
}

int findMedianSortedArrays(std::vector<int> const& nums1, std::vector<int> const& nums2)
{
    int N1 = nums1.size();
    int N2 = nums2.size();

    int lo = 0;
    int hi = N2 * 2;
    while (lo <= hi) {
        int mid2 = (lo + hi) / 2;
        int mid1 = N1 + N2 - mid2;

        int L1 = (mid1 == 0) ? INT_MIN : nums1[(mid1 - 1) / 2];
        int L2 = (mid2 == 0) ? INT_MIN : nums2[(mid2 - 1) / 2];
        int R1 = (mid1 == N1 * 2) ? INT_MAX : nums1[(mid1) / 2];
        int R2 = (mid2 == N2 * 2) ? INT_MAX : nums2[(mid2) / 2];

        if (L1 > R2) {
            lo = mid2 + 1;
        }
        else if (L2 > R1) {
            hi = mid2 - 1;
        }
        else {
            return std::max(L1, L2);
        }
    }
    return -1;
}


auto main() -> int
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n;
    int L;
    std::cin >> n >> L;
    std::vector<std::vector<int>> arrays;
    arrays.reserve(n);
    int x;
    int d;
    int a;
    int c;
    int m;

    for (int i = 0; i < n; ++i) {
        std::cin >> x >> d >> a >> c >> m;
        arrays.emplace_back(make_vector(L, x, d, a, c, m));
    }
    std::vector<int> tmp;

    for (int i = 0; i < n; ++i) {
        auto const& a = arrays[i];
        for (int j = i + 1; j < n; ++j) {
            std::cout << findMedianSortedArrays(a, arrays[j]) << '\n';
        }
    }
    return 0;
}