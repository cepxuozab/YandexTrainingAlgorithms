#include <fstream>
#include <map>
#include <string>

auto main() -> int
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    std::map<std::string, std::map<std::string, int64_t>> buyers;
    std::string name, goods;
    int cnt;
    for (; input >> name >> goods >> cnt;) {
        buyers[name][goods] += cnt;
    }
    for (auto const& [name, maps] : buyers) {
        output << name << ":\n";
        for (auto const& [key, val] : maps) {
            output << key << ' ' << val << '\n';
        }
    }
    return 0;
}
