#include <deque>
#include <iostream>
#include <vector>

void push_back(std::deque<int>& d, int v) {
    while (!d.empty() && d.back() > v) d.pop_back();

    d.push_back(v);
}

void pop_front(std::deque<int>& d, int v) {
    if (d.front() == v) d.pop_front();
}

auto main() -> int {  // NOLINT
    unsigned n, k;
    std::cin >> n >> k;

    std::vector<int> array(n);
    for (int& v : array) std::cin >> v;

    std::deque<int> d;
    unsigned i = 0;
    for (; i < k; ++i) push_back(d, array[i]);

    std::cout << d.front() << '\n';

    for (; i < n; ++i) {
        pop_front(d, array[i - k]);
        push_back(d, array[i]);
        std::cout << d.front() << '\n';
    }
}