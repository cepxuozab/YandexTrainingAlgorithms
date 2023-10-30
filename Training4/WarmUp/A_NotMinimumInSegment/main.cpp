#include <iostream>
#include <vector>
int main()
{
    int n, q;
    std::cin >> n >> q;
    std::vector<int> arr(n);
    for (int& a : arr) {
        std::cin >> a;
    }
    for (int i = 0; i < q; ++i) {
        int l, r;
        std::cin >> l >> r;
        int mini = arr[l];
        bool found = false;
        for (int j = l; j <= r; ++j) {
            if (arr[j] != mini) {
                std::cout << (arr[j] < mini ? mini : arr[j]) << std::endl;
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "NOT FOUND" << std::endl;
        }
    }
}
