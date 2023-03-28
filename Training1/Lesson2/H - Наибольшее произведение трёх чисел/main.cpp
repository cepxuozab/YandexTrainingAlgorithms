#include <climits>
#include <iostream>

int main()
{
    freopen("input.txt", "r", stdin);

    int min1 = INT_MAX, min2 = INT_MAX;
    int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
    for (int n; scanf("%d", &n) != EOF;) {
        if (n <= min1) {
            min2 = min1;
            min1 = n;
        }
        else if (n <= min2) {
            min2 = n;
        }

        if (n >= max1) {
            max3 = max2;
            max2 = max1;
            max1 = n;
        }
        else if (n >= max2) {
            max3 = max2;
            max2 = n;
        }
        else if (n >= max3) {
            max3 = n;
        }
    }
    if ((long long)max1 * (long long)max2 * max3 > (long long)min1 * (long long)min2 * max1) {
        std::cout << max1 << ' ' << max2 << ' ' << max3 << std::endl;
    }
    else {
        std::cout << min1 << ' ' << min2 << ' ' << max1 << std::endl;
    }
}
