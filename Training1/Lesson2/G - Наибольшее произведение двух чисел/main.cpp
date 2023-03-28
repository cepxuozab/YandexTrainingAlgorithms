#include <algorithm>
#include <climits>
#include <iostream>
int main()
{
    freopen("input.txt", "r", stdin);
    int x;
    std::cin >> x;
    int max1 = x, max2 = INT_MIN;
    int min1 = x, min2 = INT_MAX;

    for (; scanf("%d", &x) != EOF;) {
        if (x > max1) {
            max2 = std::exchange(max1, x);
        } else if (x > max2) {
            max2 = x;
        }
        if (x < min1) {
            min2 = std::exchange(min1, x);
        } else if (x < min2) {
            min2 = x;
        }
    }

    if ((long long)max1 * max2 > (long long)min1 * min2) {
        printf("%d %d", std::min(max1, max2), std::max(max1, max2));
    } else {
        printf("%d %d", std::min(min1, min2), std::max(min1, min2));
    }
}
