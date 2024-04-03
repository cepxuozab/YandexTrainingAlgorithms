#include <iostream>
#include <vector>

int FindDifference(int *mas, int size, int k) {
    int dif = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && j <= k+i; j++) {
            if (mas[j] - mas[i] > dif)
                dif = mas[j] - mas[i];
        }
    }
    return dif;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> arr(n);
    for (int &a: arr) {
        std::cin >> a;
    }
    std::cout << FindDifference(arr.data(), n, k);
    
}
