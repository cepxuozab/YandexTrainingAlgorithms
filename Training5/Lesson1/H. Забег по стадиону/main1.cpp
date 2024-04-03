#include <iostream>
#include <optional>
#include <vector>
#include <algorithm>
#include <iomanip>

auto EqualDistance(int L, int x1, int x2, int v1, int v2) -> std::optional<double> {
    if (x1 == x2)return 0;
    if (v1 == 0 && v2 == 0) return std::nullopt;
    if (v1 < 0 && v2 < 0) {
        v1 = abs(v1), v2 = abs(v2);
        x1 = L - x1, x2 = L - x2;
    }
    if (x2 > x1) {
        std::swap(x1, x2), std::swap(v1, v2);
    }
    std::vector<double> pos;
    if (v1 != -v2) {
        double t1 = static_cast<double>(L - x1 - x2) / (v1 + v2);
        if (t1 > 0)pos.push_back(t1);
        double t3 = static_cast<double>(2 * L - x1 - x2) / (v1 + v2);
        if (t3 > 0)pos.push_back(t3);
    }
    if (v1 < 0 || v2 < 0) {
        auto t2 = static_cast<double>(L - x1 + x2) / (v1 - v2);
        if (t2 > 0) pos.push_back(t2);

    }
    if (v2 > v1) {
        auto t4 = static_cast<double>(x1 - x2) / (v2 - v1);
        pos.push_back(t4);
    }
    if (pos.empty()) return std::nullopt;
    return std::ranges::min(pos);
}

void PrintDistance(std::optional<double> res) {
    if (res) {
        puts("YES");
        std::cout << std::setprecision(12) << std::fixed << res.value();
    } else {
        puts("NO");
    }
}

auto main() -> int {
    int L, x1, x2, v1, v2;
    std::cin >> L >> x1 >> v1 >> x2 >> v2;
    PrintDistance(EqualDistance(L, x1, x2, v1, v2));
}