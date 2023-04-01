#include<stdio.h>
auto main() -> int
{
    int p;
    scanf("%d", &p);
    int a = p / 3;
    int b = (p - a) / 2;
    int c = p - b - a;
    if (a + b <= c) {
        puts("-1");
        return 0;
    }
    printf("%d %d %d\n", a, b, c);
    a = b = (p - 1) / 2;
    c = p - a - b;
    printf("%d %d %d\n", a, b, c);
    return 0;
}
