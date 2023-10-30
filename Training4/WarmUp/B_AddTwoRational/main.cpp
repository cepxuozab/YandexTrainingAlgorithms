#include <iostream>
#include <numeric>

int main()
{
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    int num = a * d + b * c;
    int denom = b * d;
    int Gcd = std::gcd(num, denom);
    std::cout << num / Gcd << ' ' << denom / Gcd << std::endl;
}
