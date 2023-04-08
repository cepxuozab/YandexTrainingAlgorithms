#include <cstdint>
#include <iostream>
#include <map>
#include <string>
static const auto FastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr; }();

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    std::string word;
    std::getline(std::cin, word);
    std::map<char, int64_t> dict;
    size_t const size = word.length();
    for (size_t i = 0; i < size; ++i) {
        int64_t sum = (size - i) * (i + 1);
        dict[word[i]] += sum;
    }
    for (auto const& [key, value] : dict) {
        std::cout << key << ": " << value << std::endl;
    }
}
