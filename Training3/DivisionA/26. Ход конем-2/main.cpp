#include <iostream>
#include <vector>

struct Big {
    static const int LEN = 50;
    std::vector<int> num;

    Big(int a = 0) : num(LEN) {

        for (int i = 0; a != 0; a /= 10) {
            num[i] = a % 10;
            i++;
        }
    }

    void normalize() {
        for (int i = 0; i + 1 < LEN; ++i) {
            if (num[i] >= 10) {
                num[i] -= 10;
                ++num[i + 1];
            }
        }

    }

    auto operator+=(Big const &u) -> Big & {
        for (int i = 0; i < LEN; ++i) {
            num[i] += u.num[i];
        }
        normalize();
        return *this;
    }
};

auto operator<<(std::ostream &out, Big const &u) -> std::ostream & {
    int p = Big::LEN - 1;
    for (; p > 0 && !u.num[p]; --p) {}
    for (; p >= 0; --p)
        out << u.num[p];
    return out;
}


auto main() -> int {
    int h, w;
    std::cin >> w >> h;

    std::vector<std::vector<Big> > dp(h + 3, std::vector<Big>(w + 3));
    dp[2][2] = 1;
    int dx[] = {-2, -2, +1, -1};
    int dy[] = {+1, -1, -2, -2};
    for (int i = 0; i < h; ++i) {
        for (int y = i + 2, x = 2; x < w + 2 && y >= 2; x++, y--) {
            for (int d = 0; d < 4; ++d) {
                dp[y][x] += dp[y + dy[d]][x + dx[d]];
            }
        }

    }
    for (int i = 0; i + 1 < w; ++i) {
        for (int y = h + 1, x = i + 3; x < w + 2 && y >= 2; x++, y--) {
            for (int d = 0; d < 4; ++d) {
                dp[y][x] += dp[y + dy[d]][x + dx[d]];
            }
        }
    }


    std::cout << dp[h + 1][w + 1] << '\n';

    return 0;
}