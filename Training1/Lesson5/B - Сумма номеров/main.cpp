#include "iostream"
#include "unordered_map"
#include "vector"

auto Read(unsigned n) -> std::vector<int>;

auto SumNumbers(std::vector<int> const& arr, int sum) -> int;

auto main() -> int
{
    // freopen("input.txt", "r", stdin);
    unsigned n;
    int k;
    std::cin >> n >> k;
    std::cout << SumNumbers(Read(n), k) << '\n';
    return 0;
}

auto Read(unsigned n) -> std::vector<int>
{
    std::vector<int> arr(n);
    for (int& i : arr) {
        std::cin >> i;
    }
    return arr;
}

auto SumNumbers(std::vector<int> const& arr, int sum) -> int
{
    std::unordered_map<int, int> prevSum;
    int res = 0;
    int currsum = 0;
    for (int num : arr) {
        currsum += num;
        res += currsum == sum ? 1 : 0;
        if (auto it = prevSum.find(currsum - sum); it != prevSum.end()) {
            res += it->second;
        }
        prevSum[currsum]++;
    }
    return res;
}
