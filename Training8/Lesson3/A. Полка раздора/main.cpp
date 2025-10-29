#include <iostream>
#include <cmath>


int main() {
    int a, b, S;
    std::cin >> a >> b >> S;

    auto D = (a - b) * (a - b) + 4 * S;
    int root = sqrt(D);

    if (root * root != D) {
        std::cout << -1 << '\n';
        return 0;
    }

    auto L = (a + b + root);
    if (L % 2 != 0) {
        std::cout << -1 << '\n';
        return 0;
    }

    L /= 2;

    if (L > a && L > b) {
        std::cout << L << '\n';
    } else {
        std::cout << -1 << '\n';
    }

    return 0;
}