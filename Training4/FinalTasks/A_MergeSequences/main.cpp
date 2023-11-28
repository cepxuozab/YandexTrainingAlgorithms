#include <cstdint>
#include <iostream>

int main()
{
    int x;
    std::cin >> x;
    uint64_t a = 1, b = 1;
    int now = 1;
    uint64_t elA = 1, elB = 1;
    uint64_t el = 1;
    while (now <= x) {
        if (elA == elB) {
            el = elA;
            a++, b++;
            elA = a * a;
            elB = b * b * b;
        } else if (elA < elB) {
            el = elA;
            a++;
            elA = a * a;
        } else {
            el = elB;
            b++;
            elB = b * b * b;
        }
        now++;
    }
    std::cout << el << std::endl;
}
