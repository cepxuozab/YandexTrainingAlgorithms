#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class HashCalc {
    int len_;
    std::vector<int> order_;
    int64_t p = 1'000'000'007;
    int x = 257;
    std::vector<int64_t> hash1, hash2, pow;

public:
    HashCalc(std::vector<int> order);
    int binarySearch(int i);

private:
    void FillHashAndPowArray();
    bool isEqual(int k, int i);
};

int main()
{
    int n;
    std::cin >> n;
    std::string str;
    std::cin >> str;
    std::vector<int> order { 0 };
    std::transform(str.begin(), str.end(), std::back_inserter(order), [](char ch) { return (int)ch; });
    auto hc = HashCalc(order);
    for (int i = 1; i <= n; i++) {
        std::cout << hc.binarySearch(i) << ' ';
    }
}

HashCalc::HashCalc(std::vector<int> order)
    : len_(order.size())
    , order_(std::move(order))
    , hash1(len_)
    , hash2(len_)
    , pow(len_)
{
    FillHashAndPowArray();
}

int HashCalc::binarySearch(int i)
{
    int min = 0, max = i;
    while (min < max) {
        int middle = (min + max + 1) / 2;
        auto ans = isEqual(middle, i);
        if (ans) {
            min = middle;
        } else {
            max = middle - 1;
        }
    }
    return min;
}

void HashCalc::FillHashAndPowArray()
{
    pow[0] = 1;
    for (int i = 1; i < len_; i++) {
        hash1[i] = (hash1[i - 1] * x + order_.at(i) + p) % p;
        hash2[i] = (hash2[i - 1] * x + order_.at(len_ - i) + p) % p;
        pow[i] = (pow[i - 1] * x) % p;
        if (pow[i] < 0) {
            pow[i] += p;
        }
    }
}
bool HashCalc::isEqual(int k, int i)
{
    return (hash1[k] + hash2[len_ - i - 1] * pow[k] + p) % p == (hash2[len_ - i + k - 1]) % p;
}
