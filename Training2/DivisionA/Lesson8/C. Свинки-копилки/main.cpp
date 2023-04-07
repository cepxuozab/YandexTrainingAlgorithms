#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> arr[i];
    }
    int ans = 0;
    std::vector<int> piggs(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (piggs[i] == 0) {
            int nepig = i;
            while (piggs[nepig] == 0) {
                piggs[nepig] = i;
                nepig = arr[nepig];
            }
            if (piggs[nepig] == i) {
                ans++;
            }
        }
    }
    std::cout << ans;
}
