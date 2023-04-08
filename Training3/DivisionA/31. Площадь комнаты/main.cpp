#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

auto ReadLabyrinth() -> std::vector<std::string>;

using Graph = std::vector<std::vector<int>>;

Graph BuildGraph(std::vector<std::string> const &Labyrinth);

void Dfs(Graph const &graph, std::vector<short> &visited, size_t now);

auto CalculateArea(Graph const &graph, size_t start) -> int;

int main() {
  auto const labyrinth = ReadLabyrinth();
  int x, y;
  std::cin >> x >> y;
  size_t start = x - 1 + (y - 1) * (labyrinth.size() - 1);
  std::cout << CalculateArea(BuildGraph(labyrinth), start);
  return 0;
}

auto ReadLabyrinth() -> std::vector<std::string> {
  unsigned n;
  std::cin >> n;
  std::vector<std::string> labyrinth;
  labyrinth.resize(n);
  for (auto &str : labyrinth) {
    std::cin >> str;
  }
  return labyrinth;
}
auto BuildGraph(const std::vector<std::string> &Labyrinth) -> Graph {
  size_t size = Labyrinth.size();
  Graph graph(size * size);
  int dx[] = {-1, 1, 0, 0};
  int dy[] = {0, 0, -1, 1};
  for (size_t i = 1; i + 1 < size; ++i) {
    for (size_t j = 1; j + 1 < size; ++j) {
      for (size_t k = 0; k < std::size(dx); ++k) {
        size_t INeib = i + dx[k];
        size_t JNeib = j + dy[k];
        char c1 = Labyrinth[i][j];
        char c2 = Labyrinth[INeib][JNeib];
        if (c1 == '.' && c2 == '.') {
          graph[i + j * (size - 1)].push_back(INeib + JNeib * (size - 1));
        }
      }
    }
  }
  return graph;
}
void Dfs(const Graph &graph, std::vector<short> &visited, size_t now) {
  visited[now] = 1;
  for (int v : graph[now]) {
    if (visited[v] == 0) {
      Dfs(graph, visited, v);
    }
  }
}

auto CalculateArea(const Graph &graph, size_t start) -> int {
  std::vector<short> visited(graph.size() * graph.size(), 0);
  Dfs(graph, visited, start);
  return std::reduce(visited.begin(), visited.end());
}
