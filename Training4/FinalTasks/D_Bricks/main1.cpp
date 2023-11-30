#include <algorithm>
#include <iostream>
#include <vector>

class Bricks {
    std::vector<int> answer;

public:
    std::pair<int, std::vector<int>> CheckBricks(std::vector<int>& a, int n);

private:
    void RecursiveCount(std::vector<int>& a, int i, int n, std::vector<int>& buffer);
};

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<int> arr(m);
    for (int& a : arr) {
        std::cin >> a;
    }
    Bricks bricks;
    auto [size, answer] = bricks.CheckBricks(arr, n);
    std::cout << size << std::endl;
    for (int i : answer) {
        std::cout << i << ' ';
    }
}

std::pair<int, std::vector<int>> Bricks::CheckBricks(std::vector<int>& a, int n)
{
    long long sum = 0;
    for (int i : a) {
        sum += i;
    }
    if (sum * 2 < n) {
        return { -1, {} };
    }
    std::sort(a.rbegin(), a.rend());
    std::vector<int> buffer;
    RecursiveCount(a, 0, n, buffer);
    return { (int)answer.size(), answer };
}

void Bricks::RecursiveCount(std::vector<int>& a, int i, int n, std::vector<int>& buffer)
{
    if (n == 0) {
        if (answer.empty() || buffer.size() < answer.size()) {
            answer = buffer;
        }
        return;
    }
    if (i == a.size() || n < 0 || (!answer.empty() && buffer.size() > answer.size())) {
        return;
    }
    buffer.push_back(a[i]);
    buffer.push_back(a[i]);
    RecursiveCount(a, i + 1, n - 2 * a[i], buffer);
    buffer.pop_back();
    RecursiveCount(a, i + 1, n - a[i], buffer);
    buffer.pop_back();
    RecursiveCount(a, i + 1, n, buffer);
}
