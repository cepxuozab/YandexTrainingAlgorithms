#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

template <typename T>
void ReadVector(std::vector<T>& arr);

int IsPossibleSorted(std::vector<double> const& containers);

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("can't open input.txt");
        return 1;
    }
    unsigned test;
    std::cin >> test;
    for (unsigned i = 0; i < test; ++i) {
        std::vector<double> containers;
        ReadVector(containers);
        std::cout << IsPossibleSorted(containers) << std::endl;
    }
    return 0;
}

template <typename T>
void ReadVector(std::vector<T>& arr)
{
    unsigned n;
    std::cin >> n;
    arr.resize(n);
    for (auto& elem : arr) {
        std::cin >> elem;
    }
}

int IsPossibleSorted(std::vector<double> const& containers)
{
    if (containers.size() < 2) {
        return 1;
    }
    std::vector<double> answer, bottom { containers.front() };
    for (size_t i = 1; i < containers.size(); ++i) {
        auto const& container = containers[i];
        while (!bottom.empty() && bottom.back() < container) {
            answer.push_back(bottom.back());
            bottom.pop_back();
        }
        bottom.push_back(container);
    }
    answer.insert(answer.end(), bottom.rbegin(), bottom.rend());
    return std::ranges::is_sorted(answer);
}
