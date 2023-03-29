#include <fstream>
#include <string>
#include <unordered_map>

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    int n;
    input >> n;
    std::unordered_map<std::string, int> leng;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int m;
        input >> m;
        for (int j = 0; j < m; ++j) {
            std::string str;
            input >> str;
            ++leng[str];
            if (leng[str] == n) {
                ans++;
            }
        }
    }
    output << ans << '\n';
    for (auto const& [str, num] : leng) {
        if (num == n) {
            output << str << '\n';
        }
    }
    output << leng.size() << '\n';
    for (auto const& [str, num] : leng) {
        output << str << '\n';
    }
}
