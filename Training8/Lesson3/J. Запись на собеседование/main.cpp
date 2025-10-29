#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canDo(int k, int n, const vector<long long>& a, const vector<long long>& b) {
    vector<long long> rem = a;
    int i = 0;

    for (int j = 0; j < n; j++) {
        while (i < n && rem[i] == 0) i++;
        if (i < n && i + k < j) return false;

        long long cap = b[j];
        int end = min(n - 1, j + k);
        while (cap > 0 && i <= end) {
            if (rem[i] == 0) {
                i++;
                continue;
            }
            long long take = min(rem[i], cap);
            rem[i] -= take;
            cap -= take;
            if (rem[i] == 0) i++;
        }
    }

    return i >= n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    long long total_a = 0, total_b = 0;
    for (int i = 0; i < n; i++) {
        total_a += a[i];
        total_b += b[i];
    }
    if (total_a > total_b) {
        cout << -1 << '\n';
        return 0;
    }

    int low = 0, high = n;
    while (low < high) {
        int mid = (low + high) / 2;
        if (canDo(mid, n, a, b)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    cout << low << '\n';
    return 0;
}