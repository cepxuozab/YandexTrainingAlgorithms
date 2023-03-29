#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <set>

template <typename T>
void Print(T rng, std::ostream& output)
{
    output << std::ranges::distance(rng) << '\n';
    std::ranges::copy(rng, std::ostream_iterator<int>(output, " "));
    output << '\n';
}
int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    unsigned n, m;
    input >> n >> m;
    std::set<int> girl, boy;
    int x;
    for (unsigned i = 0; i < n && input >> x; ++i)
        girl.insert(x);
    for (unsigned i = 0; i < m && input >> x; ++i)
        boy.insert(x);
    auto rng = girl | std::views::filter([&](int a) { return boy.contains(a); });
    Print(rng, output);
    auto rng1 = girl | std::views::filter([&](int a) { return !boy.contains(a); });
    Print(rng1, output);
    auto rng2 = boy | std::views::filter([&](int a) { return !girl.contains(a); });
    Print(rng2, output);
}
