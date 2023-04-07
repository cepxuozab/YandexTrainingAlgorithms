#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ull;

int main() {
    ull n, k;
    cin >> n >> k;
    vector<ull> a(n);
    for (size_t i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    ull bot = 0;
    ull top = a[0];
    while (bot < top) {
        ull x = (bot + top) / 2 + 1;
        ull painted = 0;
        bool can_paint = true;
        for (size_t i = 0; i < n; ++i) {
            if (k < painted + x) {
                can_paint = false;
                break;
            }
            painted += a[i] - min(a[i] - x, painted);
        }
        if (can_paint) {
            bot = x;
        }
        else {
            top = x - 1;
        }
    }
    cout << bot << endl;

    return 0;
}