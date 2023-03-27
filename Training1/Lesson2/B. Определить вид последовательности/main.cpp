#include <iostream>

int main()
{
    freopen("input.txt", "r", stdin);
    int a, b;
    std::cin >> a >> b;
    bool CONSTANT = a == b;
    bool ASCENDING = a < b;
    bool WEAKLY_ASCENDING = a <= b;
    bool DESCENDING = a > b;
    bool WEAKLY_DESCENDING = a >= b;
    while (true) {
        a = b;
        std::cin >> b;
        if (b == -2'000'000'000) {
            break;
        }
        CONSTANT = CONSTANT && a == b;
        ASCENDING = ASCENDING && a < b;
        WEAKLY_ASCENDING = WEAKLY_ASCENDING && a <= b;
        DESCENDING = DESCENDING && a > b;
        WEAKLY_DESCENDING = WEAKLY_DESCENDING && a >= b;
    }
    if (CONSTANT) {
        puts("CONSTANT");
        return 0;
    }
    if (ASCENDING) {
        puts("ASCENDING");
        return 0;
    }
    if (WEAKLY_ASCENDING) {
        puts("WEAKLY ASCENDING");
        return 0;
    }
    if (DESCENDING) {
        puts("DESCENDING");
        return 0;
    }
    if (WEAKLY_DESCENDING) {
        puts("WEAKLY DESCENDING");
        return 0;
    }
    puts("RANDOM");
    return 0;
}
