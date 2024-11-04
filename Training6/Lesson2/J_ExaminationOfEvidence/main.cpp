#include <iostream>
#include <vector>

template <typename T>
auto operator>>(std::istream& in, std::vector<T>& v) -> std::istream& {
    for (auto& item : v) in >> item;
    return in;
}

auto main() -> int {  // NOLINT
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    std::cin >> a;
    int m, k;
    std::cin >> m >> k;
    std::vector<int> x(m);
    std::cin >> x;

    std::vector<int> left(n, 0);
    int cnt = 0;
    for (int i = 1; i < n; i++) {
        if (a[i - 1] < a[i])
            left[i] = left[i - 1];
        else if (a[i - 1] > a[i]) {
            left[i] = i;
            cnt = 0;
        } else {
            cnt++;
            left[i] = left[i - 1];
            while (cnt > k) {
                cnt -= a[left[i]] == a[left[i] + 1];
                left[i]++;
            }
        }
    }

    for (int xi : x) {
        std::cout << left[xi - 1] + 1 << ' ';
    }
    std::cout << '\n';
}