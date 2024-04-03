#include <cmath>
#include <iostream>

using namespace std;

auto main() -> int {
    unsigned long long n{}, res{};
    cin >> n;
    long double D = sqrt(1.000 + 8.000 * static_cast<long double>(n));
    long double k = D / 2 - 0.500;
    if (static_cast<unsigned long long>(k) - k == 0)
        res = static_cast<unsigned long long>(k);
    else
        res = static_cast<unsigned long long>(k) + 1;
    unsigned long long l = n - res * (res - 1) / 2;
    if (res % 2 == 0)
        cout << res - l + 1 << "/" << l << '\n';
    else
        cout << l << "/" << res - l + 1 << '\n';

    return 0;
}