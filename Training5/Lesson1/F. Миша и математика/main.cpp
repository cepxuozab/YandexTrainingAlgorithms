#include <iostream>
#include <vector>
auto main() -> int {
    int n;
    std::cin >> n;
    std::vector<bool> seq(n);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        seq[i] = (x & 1);
    }
    bool curr = seq.front();
    for (int i = 1; i < n; ++i) {
        if (curr) {
            char const ch = seq[i] ? 'x' : '+';
            std::cout << ch;
        } else if (seq[i]) {
            curr = true;
            std::cout << '+';
        } else {
            std::cout << '+';
        }
    }
}
