#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>

static const auto FastIO = []() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	return nullptr; }();

using Level = std::vector<std::string>;

using Cave = std::vector<Level>;

namespace utility {
void PrintCave(Cave const& cave);
}

struct Point {
    int x, y, z;
    Point();
    Point(int a, int b, int c);
};

Point operator+(Point lhs, Point rhs);
bool operator<(Point lhs, Point rhs);
bool operator>=(Point lhs, Point rhs);

std::pair<int, Point> ReadCave(Cave& cave, std::istream& input = std::cin);

int BfsCave(int n, Cave& cave, Point start);

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    Cave cave;
    auto [n, start] = ReadCave(cave);
    std::cout << BfsCave(n, cave, start);
}

Point::Point()
    : x(0)
    , y(0)
    , z(0)
{
}
Point::Point(int a, int b, int c)
    : x(a)
    , y(b)
    , z(c)
{
}
Point operator+(Point lhs, Point rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}

bool operator<(Point lhs, Point rhs)
{
    return lhs.x < rhs.x || lhs.y < rhs.y || lhs.z < rhs.z;
}

bool operator>=(Point lhs, Point rhs)
{
    return lhs.x >= rhs.x || lhs.y >= rhs.y || lhs.z >= rhs.z;
}
std::pair<int, Point> ReadCave(Cave& cave, std::istream& input)
{
    int n;
    input >> n;
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Point start;
    for (int i = 0; i < n; ++i) {
        Level level;
        std::string dummy;
        getline(input, dummy);
        for (int j = 0; j < n; ++j) {
            std::string line;
            getline(input, line);
            level.push_back(line);
            for (int k = 0; k < n; ++k) {
                if (line[k] == 'S') {
                    start = Point(j, k, i);
                }
            }
        }
        cave.push_back(level);
    }
    return { n, start };
}

int BfsCave(int n, Cave& cave, Point start)
{
    std::vector<std::vector<std::vector<int>>> maze;
    maze.resize(n);
    for (auto& level : maze) {
        level.resize(n, std::vector<int>(n, -1));
    }
    std::queue<Point> queue;
    queue.push(start);
    maze[start.z][start.x][start.y] = 0;
    int dx[] = { -1, 1, 0, 0, 0, 0 };
    int dy[] = { 0, 0, -1, 1, 0, 0 };
    int dz[] = { 0, 0, 0, 0, -1, 1 };
    while (!queue.empty()) {
        auto now = queue.front();
        queue.pop();
        auto dist = maze[now.z][now.x][now.y] + 1;
        for (size_t i = 0; i < std::size(dx); ++i) {
            Point curr = now + Point { dx[i], dy[i], dz[i] };
            if (curr < Point(0, 0, 0) || curr >= Point(n, n, n)) {
                continue;
            }
            if (cave[curr.z][curr.x][curr.y] == '.') {
                maze[curr.z][curr.x][curr.y] = dist;
                cave[curr.z][curr.x][curr.y] = '#';
                queue.push(curr);
            }
        }
    }
    int min_path = std::numeric_limits<int>::max();
    for (auto const& line : maze.front()) {
        for (int item : line) {
            if (item != -1) {
                min_path = min_path < item ? min_path : item;
            }
        }
    }
    return min_path;
}

void utility::PrintCave(Cave const& cave)
{
    std::cout << cave.size() << std::endl;
    puts("");
    for (auto const& level : cave) {
        for (auto const& line : level) {
            std::cout << line << std::endl;
        }
        std::cout << std::endl;
    }
}
