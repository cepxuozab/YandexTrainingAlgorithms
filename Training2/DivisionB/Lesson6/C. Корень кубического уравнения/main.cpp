#include <iomanip>
#include <iostream>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

using namespace std;
double fun(double a, double b, double c, double d, double x)
{
    return a * x * x * x + b * x * x + c * x + d;
}

int main()
{
    double a, b, c, d;
    cin >> a >> b >> c >> d;
    double l = -1, r = 1;
    while ((fun(a, b, c, d, r) * fun(a, b, c, d, l)) >= 0) {
        r *= 2;
        l *= 2;
    }
    for (int i = 0; i < 100; i++) {
        double x = (l + r) / 2;
        double v1 = fun(a, b, c, d, x);
        double v2 = fun(a, b, c, d, r);
        (v1 * v2 <= 0) ? l = x : r = x;
    }
    cout << setprecision(18) << l;
    return 0;
}
