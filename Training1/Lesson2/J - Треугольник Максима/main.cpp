#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

int main()
{
    freopen("input.txt", "r", stdin);
    double MIN_FREQ = 30.;
    double MAX_FREQ = 4000.;
    int n;
    std::cin >> n;
    double l = MIN_FREQ;
    double r = MAX_FREQ;
    double pf = 0;
    for (int i = 0; i < n; ++i) {
        double f;
        std::cin >> f;
        if (i > 0) {
            std::string s;
            std::cin >> s;
            double m = (f + pf) / 2.0;
            if ((pf < f) ^ (s == "closer")) {
                r = std::min(r, m);
            } else {
                l = std::max(l, m);
            }
        }
        pf = f;
    }
    std::cout << std::fixed << std::setprecision(9) << l << ' ' << r << '\n';
}
