#include <iostream>

auto IsIntersect(int p, int v, int q, int m) -> bool {
    return abs(p - q) <= v + m;
}

auto main() -> int {
    int P, V, Q, M;
    std::cin >> P >> V >> Q >> M;
    if (IsIntersect(P, V, Q, M)) {
        std::cout << std::max(P + V, Q + M) - std::min(P - V, Q - M) + 1;
    } else {
        std::cout << 2 * (V + M + 1);
    }
}