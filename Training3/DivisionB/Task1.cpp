#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

auto CountFrequencies(std::istream& input, std::map<char, int>& frequencies) -> int;

auto MakeGistogramme(int n, std::map<char, int>& frequencies) -> std::vector<std::string>;

void PrintGistogramme(std::vector<std::string> const& gist);

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input file");
        return 1;
    }
    std::map<char, int> frequensies;
    int size = CountFrequencies(std::cin, frequensies);
    PrintGistogramme(MakeGistogramme(size, frequensies));
}

auto CountFrequencies(std::istream& input, std::map<char, int>& frequencies) -> int
{
    int max = -1;
    for (std::string str; getline(input, str);) {
        for (char ch : str) {
            if (ch != ' ') {
                frequencies[ch]++;
                max = std::max(max, frequencies.at(ch));
            }
        }
    }
    return max;
}

auto MakeGistogramme(int n, std::map<char, int>& frequencies) -> std::vector<std::string>
{
    std::vector<std::string> gist(n + 1, std::string(frequencies.size(), ' '));
    for (auto it = gist.rbegin(); it != gist.rend(); ++it) {
        size_t idx = 0;
        for (auto& [key, value] : frequencies) {
            if (it == gist.rbegin()) {
                it->at(idx++) = key;
            } else {
                if (--value >= 0) {
                    it->at(idx) = '#';
                }
                idx++;
            }
        }
    }
    return gist;
}

void PrintGistogramme(std::vector<std::string> const& gist)
{
    size_t idx = 0;
    for (auto const& str : gist) {
        std::cout << str;
        if (idx + 1 != gist.size())std::cout << std::endl;
        idx++;
    }
}
