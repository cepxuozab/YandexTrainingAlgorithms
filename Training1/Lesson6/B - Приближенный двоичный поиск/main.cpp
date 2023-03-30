#include <algorithm>
#include <fstream>
#include <vector>

auto findClosestElements(std::vector<int> const& A, int x) -> int;

auto main() -> int
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    int n;
    int k;
    input >> n >> k;
    std::vector<int> arr(n);
    for (int& i : arr) {
        input >> i;
    }
    for (int i = 0, x; i < k && input >> x; ++i) {
        output << findClosestElements(arr, x) << '\n';
    }
    return 0;
}

auto findClosestElements(std::vector<int> const& A, int x) -> int
{
    size_t left = 0;
    size_t right = A.size() - 1;

    while (left < right) {
        size_t mid = (left + right) / 2;
        (x - A[mid] > A[mid + 1] - x) ? left = mid + 1 : right = mid;
    }
    return A[left];
}
