#include <fstream>
#include <ranges>
#include <unordered_map>

auto main() -> int
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    std::unordered_map<int, int> bloks;
    int n;
    input >> n;
    for (int i = 1; i <= n; ++i) {
        int width, height;
        input >> width >> height;
        auto& curr = bloks[width];
        curr = curr < height ? height : curr;
    }
    long long ans = 0;
    for (int value : bloks | std::views::values) {
        ans += value;
    }
    output << ans << '\n';
    return 0;
}
