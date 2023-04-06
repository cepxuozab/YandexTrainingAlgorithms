#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ull;

int main() {
    int n;
    cin >> n;
    vector<ull> v(n), s(n);
    for (size_t i = 0; i < n; ++i) {
        cin >> v[i];
        s[i] = v[i] * v[i];
    }

    ull res = 0;
    for (size_t i = 2; i < n; ++i) {
        if (v[i] - v[0] == 0) {
            continue;
        }
        for (size_t j = 0; j < i - 1; ++j) {
            auto left =
                upper_bound(v.begin() + j + 1, v.begin() + i, v[i] - v[j]);
            if (left == v.begin() + i) {
                continue;
            }
            auto right =
                lower_bound(s.begin() + j + 1, s.begin() + i, s[i] - s[j]);
            if (right == s.begin() + j + 1) {
                continue;
            }
            --right;
            res += distance(s.begin(), right) - distance(v.begin(), left) + 1;
        }
    }
    cout << res << endl;

    return 0;
}