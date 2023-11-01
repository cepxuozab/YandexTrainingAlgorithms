#include <cstdio>

void TestCase()
{
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);
    int min_per_each = n / a;
    int rest = n % a;
    if (rest % min_per_each == 0) {
        rest / min_per_each <= b - a ? puts("YES") : puts("NO");
    } else {
        rest / min_per_each + 1 <= b - a ? puts("YES") : puts("NO");
    }
}
int main()
{
    int t;
    scanf("%d ", &t);
    while (t > 0) {
        TestCase();
        t--;
    }
}
