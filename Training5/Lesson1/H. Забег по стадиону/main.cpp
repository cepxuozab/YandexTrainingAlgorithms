#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>
auto main() -> int {
    int64_t L, x1, v1, x2, v2;
    std::cin >> L >> x1 >> v1 >> x2 >> v2;
    x1 = x1 % L;
    x2 = x2 % L;

    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(v1, v2);
    }
    double t{};
    bool flag = true;
    if (v1 + v2 != 0 && x1 != x2) {
        double t3 = 0, t4 = 0;
        int k = 0;
        while (t3 <= 0. && t4 <= 0.) {
            t3 = 1.0 * (k * L - (x1 + x2) % L) / (v1 + v2);
            t4 = 1.0 * (-k * L - (x1 + x2) % L) / (v1 + v2);
            k += 1;
        }
        if (t3 * t4 < 0) {
            t = std::max(t3, t3);
        } else {
            t = std::min(t3, t4);
        }
    } else {
        if (((x1 + x2) % L == 0 || (x1 - x2) % L == 0) || x1 == x2) {
            t = 0;
        } else {
            if ((v1 == -v2) && v1 == 0) {
                flag = false;
            } else {
                if (v1 < 0) {
                    t = 1.0 * (L - x2 + x1) / (v2 - v1);
                } else {
                    t = 1.0 * (x2 - x1) / (v1 - v2);
                }
            }
        }
    }
    if (v1 != v2 && flag) {
        double t1 = 0;
        double t2 = 0;
        int k = 0;
        while (t1 <= 0 && t2 <= 0) {
            t1 = 1.0 * (k * L - (x1 - x2)) / (v1 - v2);
            t2 = 1.0 * (-k * L - (x1 - x2)) / (v1 - v2);
            k += 1;
        }
        double tmp = t1 * t2 < 0 ? std::max(t1, t2) : std::min(t1, t2);
        t = std::min(t, tmp);
    }
    if (flag) {
        std::cout << "YES\n";
        std::cout << std::setprecision(12) << std::fixed << t;
    } else {
        std::cout << "NO\n";
    }
}
