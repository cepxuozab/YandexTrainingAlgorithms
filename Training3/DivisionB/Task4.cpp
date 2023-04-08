#include <iostream>
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
    int n, k, row, position;
    std::cin >> n >> k >> row >> position;
    int odd = k % 2;
    int nextRow = row + k / 2;
    int prevRow = row - k / 2;
    int nextPosition = position;
    int prevPosition = position;
    if (odd == 1) {
        if (position + 1 > 2) {
            nextRow++;
            nextPosition = 1;
        } else {
            nextPosition = 2;
        }
        if (position - 1 < 1) {
            prevRow--;
            prevPosition = 2;
        } else {
            prevPosition = 1;
        }
    }
    std::string res = "-1";
    bool prevValid = prevRow > 0;
    bool nextValid = (nextRow - 1) * 2 + nextPosition - 1 < n;

    if (prevValid && nextValid) {
        int dPrev = row - prevRow;
        int dNext = nextRow - row;
        if (dPrev < dNext) {
            res = std::to_string(prevRow) + " " + std::to_string(prevPosition);
        } else {
            res = std::to_string(nextRow) + " " + std::to_string(nextPosition);
        }
    } else if (!prevValid && nextValid) {
        res = std::to_string(nextRow) + " " + std::to_string(nextPosition);
    } else if (prevValid) {
        res = res = std::to_string(prevRow) + " " + std::to_string(prevPosition);
    }
    std::cout << res << std::endl;
}
