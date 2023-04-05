#include <algorithm>
#include <iostream>
#include <vector>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

using namespace std;

bool success(vector<int64_t> const& x, int64_t len, int k)
{
    int const size = x.size();
    int ndx = 0, beg_ndx = 0;
    while (k > 0) {
        k--;
        long long gap = x[ndx] - x[beg_ndx];
        while (gap < len && ndx + 1 < size) {
            ndx++;
            gap = x[ndx] - x[beg_ndx];
        }
        if (ndx + 1 == x.size() && gap <= len) {
            return true;
        }
        if (gap == len && ndx + 1 < size) {
            ndx++;
        }
        beg_ndx = ndx;
    }
    return false;
}

int main()
{
    //freopen("input.txt", "r", stdin);
    int n, k;
    cin >> n >> k;
    vector<int64_t> x(n);
    for (auto& xx : x) {
        cin >> xx;
    }

    sort(x.begin(), x.end());
    x.resize(unique(x.begin(), x.end()) - x.begin());
    int64_t l_min = 0;
    int64_t l_max = (x.back() - x.front()) / k + 1;
    while (l_min < l_max) {
        int64_t l_mid = (l_min + l_max) / 2;
        success(x, l_mid, k) ? l_max = l_mid : l_min = l_mid + 1;
    }
    cout << l_min << endl;

    return 0;
}
