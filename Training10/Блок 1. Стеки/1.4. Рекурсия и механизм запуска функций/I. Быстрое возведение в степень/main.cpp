#include <iostream>

double binpow(double a, long long n) {
    if (n == 0)
        return 1;
    if (n % 2 == 1)
        return binpow(a, n - 1) * a;
    else {
        double b = binpow(a, n / 2);
        return b * b;
    }
}

int main() {
    double a;
    long long n;
    std::cin >> a >> n;
    std::cout << binpow(a, n);
    return 0;
}