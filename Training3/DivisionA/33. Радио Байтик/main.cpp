#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>

struct Point {
    int x, y;
};

inline int Distance(Point lhs, Point rhs)
{
    int dx = lhs.x - rhs.x;
    int dy = lhs.y - rhs.y;
    return dx * dx + dy * dy;
}

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    int n;
    std::cin >> n;
    std::vector<Point> points;
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        points.push_back({ x, y });
    }
    int left = 0;
    int right = 20000 * 20000 * 2 + 1;
    std::vector<int> ansColor;
    while (left + 1 < right) {
        int mid = left + (right - left) / 2;
        const int UNDEF = 0;
        std::vector<int> color(n, UNDEF);
        std::vector<int> stack;
        bool good = true;
        for (int i = 0; i < n && good; ++i) {
            if (color[i] == UNDEF) {
                stack.push_back(i);
                color[i] = 1;
                while (!stack.empty() && good) {
                    int cur = stack.back();
                    stack.pop_back();
                    for (int next = 0; next < n; ++next) {
                        if (next != cur && Distance(points[cur], points[next]) < mid) {
                            if (color[next] == UNDEF) {
                                color[next] = 3 - color[cur];
                                stack.push_back(next);
                            } else if (color[next] == color[cur]) {
                                good = false;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (good) {
            left = mid;
            ansColor = color;
        } else {
            right = mid;
        }
    }
    printf("%.9f\n", std::sqrt(left) / 2);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", ansColor[i]);
    }
}
