#include <iostream>
#include <vector>


auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int x;
    std::cin >> n >> x;    
    
    std::vector<int> pref{0};  

    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a; 
        pref.push_back(pref.back() + (a>=x));
    }

    int m;
    std::cin >> m;

    int left = 0;

    for (int i = 0; i < m; ++i) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int a;
            std::cin >> a; 
            pref.push_back(pref.back() + (a>=x));

        } else if (type == 2) {
            left++;

        } else if (type == 3) {
            int k;
            std::cin >> k;
            // first k people: indices [left, left + k)
            int ans = pref[left + k] - pref[left];
            std::cout << ans << '\n';
        }
    }

    return 0;
}