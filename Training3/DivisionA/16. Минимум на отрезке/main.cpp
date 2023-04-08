#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    int n, k;
    std::cin >> n >> k;
    std::multiset<int> st;
    std::vector<int> arr(n);
    for (int i = 0; i < k; ++i) {
        int x;
        std::cin >> x;
        arr[i] = x;
        st.insert(x);
    }
    for (int i = k; i < n; ++i) {
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
