#include "iostream"
#include "vector"

auto Read(unsigned n) -> std::vector<int>;

auto BestIntervals(std::vector<int> const& alley, int k) -> std::pair<int, int>;
auto main() -> int
{
    // freopen("input.txt", "r", stdin);

    unsigned n;
    unsigned k;
    std::cin >> n >> k;
    auto const [start, end] = BestIntervals(Read(n), k);
    std::cout << start << ' ' << end << std::endl;
}

auto Read(unsigned n) -> std::vector<int>
{
    std::vector<int> arr(n);
    for (int& i : arr) {
        std::cin >> i;
    }
    return arr;
}

auto BestIntervals(std::vector<int> const& alley, int k) -> std::pair<int, int>
{
    int n = alley.size();
    int trees = 0;
    int tail = 0;
    int head = 0;
    int tailbest = 1;
    int headbest = alley.size();
    std::vector<int> map(k, 0);
    while (head < n) {
        int i = alley[head++];
        trees += static_cast<int>((map[i - 1]++)) == 0;
        if (trees == k) {
            do {
                i = alley[tail++];
            } while (--map[i - 1] != 0);
            trees--;
            if (head - tail < headbest - tailbest) {
                tailbest = tail;
                headbest = head;
            }
        }
    }
    return { tailbest, headbest };
}
