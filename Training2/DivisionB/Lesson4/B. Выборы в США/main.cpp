#include <iostream>
#include <map>
#include <string>

static auto const FastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main()
{
    freopen("input.txt", "r", stdin);
    std::string name;
    int voute;
    std::map<std::string, int> voutes;
    while (std::cin >> name >> voute) {
        voutes[name] += voute;
    }
    for (auto const& [key, value] : voutes) {
        std::cout << key << ' ' << value << '\n';
    }
    return 0;
}
