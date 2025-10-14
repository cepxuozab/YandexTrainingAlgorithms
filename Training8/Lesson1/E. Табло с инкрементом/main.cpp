#include <iostream>

int main() {
    long long n, k;
    std::cin >> n >> k;

    for (long long i = 0; i < k;) {
        int last_digit = n % 10;
        if (last_digit == 0) {
            break;
        }
        if (last_digit == 5 && i + 1 <= k) {
            n += 5;
            break;
        }

        // Если осталось много шагов и мы в цикле 2,4,8,6
        if (k - i >= 4 && (last_digit == 2 || last_digit == 4 || last_digit == 8 || last_digit == 6)) {
            // Проверяем, что действительно в устойчивом цикле
            long long cycles = (k - i) / 4;
            n += cycles * 20;
            i += cycles * 4;
        } else {
            // Делаем один шаг
            n += last_digit;
            i++;
        }
    }

    std::cout << n << std::endl;
    return 0;
}