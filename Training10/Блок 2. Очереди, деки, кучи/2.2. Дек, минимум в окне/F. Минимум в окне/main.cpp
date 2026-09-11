#include <iostream>
#include <ranges>
#include <set>
#include <vector>

auto main() -> int {
    int n, k;
    std::cin >> n >> k;
    std::multiset<int> st;
    std::vector<int> arr(n);
    for (auto i : std::ranges::views::iota(0, k)) {
        int x;
        std::cin >> x;
        arr[i] = x;
        st.insert(x);
    }
    for (auto i : std::views::iota(k, n)) {
        std::cout << *st.begin() << '\n';
        int x;
        std::cin >> x;
        arr[i] = x;
        st.erase(st.find(arr[i - k]));
        st.insert(x);
    }
    std::cout << *st.begin();
    return 0;
}