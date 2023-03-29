
#include <iostream>
#include <string>
#include <unordered_map>

auto main() -> int
{
    
    unsigned n;
    std::cin >> n;
    std::unordered_map<std::string, std::string> dict;
    for (unsigned i = 0; i < n; ++i) {
        std::string a;std::string b;
        std::cin >> a >> b;
        dict.emplace(a, b);
        dict.emplace(b, a);
    }
    std::string word;
    std::cin >> word;
    std::cout << dict.at(word) << '\n';
}
