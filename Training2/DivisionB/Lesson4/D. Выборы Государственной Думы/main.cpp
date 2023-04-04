#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>


struct S { std::string s; int n, v; double ci, cf; };

bool cmp1(S& lhs, S& rhs) { return lhs.cf == rhs.cf ? lhs.v > rhs.v : lhs.cf > rhs.cf; }
bool cmp2(S& lhs, S& rhs) { return lhs.n < rhs.n; }


int main()
{
    std::ifstream is("input.txt");
    std::ofstream os("output.txt");

    std::vector<S> v;
    std::string str;

    for (int i{}; std::getline(is, str); ++i) {
        size_t off = str.find_last_of(" ") + 1;
        v.push_back({ str.substr(0, off), i, std::stoi(str.substr(off, str.size() - off)), 0., 0. });
    }

    double d{};
    for (auto& it : v) d += it.v;
    d /= 450.;

    int t{};
    for (auto& it : v) {
        it.cf = std::modf(double(it.v) / d, &it.ci);
        t += it.ci;
    }

    std::sort(v.begin(), v.end(), cmp1);
    for (int i{}; i < 450 - t; ++i) ++v[i % v.size()].ci;
    std::sort(v.begin(), v.end(), cmp2);

    for (auto& it : v) os << it.s << int(it.ci) << '\n';

    return 0;
}