#include <cstdio>

int main()
{
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);
    int cnt_b = (b % n != 0) + b / n;
    a > cnt_b ? puts("Yes") : puts("No");
    return 0;
}
