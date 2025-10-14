#include <iostream>
#include <array>
using namespace std;

long long countRemainder(long long start, int secs) {
    for (int i = 0; i < secs; ++i)
        start += start % 10;
    return start;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    int k;
    cin >> n >> k;

    static const array<int, 10> penalties = {{
        -1, 1, 0, 2, 3, -1, 1, 4, 2, 3
    }};

    long long res = n;

    if (k != 0) {
        int x = res % 10;
        res -= x;
        if (penalties[x] != -1) {
            long long d = countRemainder(x, penalties[x]);
            int diff = k - penalties[x];
            long long f = (diff / 4) * 20LL;
            long long i = countRemainder(2, diff % 4) - 2;
            res += d + f + i;
        } else {
            res += static_cast<long long>(x) * 2;
        }
    }

    cout << res << '\n';
    return 0;
}