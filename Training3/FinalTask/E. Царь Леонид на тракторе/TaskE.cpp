#include <algorithm>
#include <queue>
#include <iostream>
#include <ranges>
#include <tuple>
#include <vector>

[[maybe_unused]] static const auto FastIo = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

struct Vertex {
    int h=0, w=0;
};
int Distance(std::vector<std::vector<int>>& field, Vertex start, Vertex end);

int main()
{
    freopen("input.txt", "r", stdin);
    int h, w;
    std::cin >> h >> w;
    std::vector<std::vector<int>> field(h + 2, std::vector<int>(w + 2));
    for (int i = 0; i <= h + 1; i++) {
        field[i][0] = -1;
        field[i][w + 1] = -1;
    }

    for (int i = 0; i <= w + 1; i++) {
        field[0][i] = -1;
        field[h + 1][i] = -1;
    }
    for (int i = h; i >= 1; i--) {
        std::string line;
        std::cin >> line;
        for (int j = 1; j <= w; j++) {
            if (line[j - 1] == 'X')
                field[i][j] = -1;
        }
    }
    Vertex start, end;
    std::cin >> start.w >> start.h >> end.w >> end.h;
    int distance = Distance(field, start, end);
    distance = (distance == 0) ? 1 : distance;
    std::cout << distance;
}

int Distance(std::vector<std::vector<int>>& field, Vertex start, Vertex end) {
    int dh[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    int dw[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    std::queue<Vertex> bfs;
    bfs.push(start);
    while (!bfs.empty()) {
        Vertex head = bfs.front();
        bfs.pop();
        int value = field[head.h][head.w] + 1;
        for (int i = 0; i < 8; i++) {
            int h = head.h;
            int w = head.w;
            bool proceed = true;
            while (proceed) {

                h = h + dh[i];
                w = w + dw[i];
                if (field[h][w] == -1) {
                    proceed = false;
                    continue;
                }

                if (field[h][w] == 0) {
                    field[h][w] = value;
                    bfs.push(Vertex(h, w));
                }

                if (h == end.h && w == end.w)
                    return field[h][w];

            }
        }
    }
    return -1;
}
