#include <iostream>

auto main() -> int
{
    int m[10];
    for (int& i : m) {
        std::cin >> i;
    }
    int max = 0;
    for (int i = 0; i < 10; i++) {
        if (m[i] == 1) {
            int h1 = 0;
            int h2 = 0;
            int j = i;
            while (j > 0 && m[j] != 2) {
                h1++;
                j--;
            }
            if (m[j] != 2) {
                h1 = 10;
            }
            j = i;
            while (j < 9 && m[j] != 2) {
                h2++;
                j++;
            }
            if (m[j] != 2) {
                h2 = 10;
            }
            if (h1 > h2 || h1 == 0) {
                h1 = h2;
            }
            if (h1 > max) {
                max = h1;
            }
        }
    }
    std::cout << max;
}
