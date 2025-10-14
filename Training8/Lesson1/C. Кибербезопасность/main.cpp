#include <iostream>
#include <string>
#include <vector>

auto main() -> int {
    std::string s;
    std::cin >> s;
    auto n = static_cast<long long>(s.length());

    std::vector<int> freq(26, 0);
    for (char c: s) {
        freq[c - 'a']++;
    }

    long long total = n * (n - 1) / 2;
    long long same = 0;
    for (int i = 0; i < 26; i++) {
        long long f = freq[i];
        same += f * (f - 1) / 2;
    }

    long long distinct_transpositions = total - same;

    // Если есть хотя бы два разных символа, можем получить distinct_transpositions новых паролей
    // плюс исходный пароль
    long long ans = 1 + distinct_transpositions;

    // Но если все символы одинаковы, то distinct_transpositions = 0, и ответ 1.
    // Формула работает.

    std::cout << ans << '\n';

    return 0;
}