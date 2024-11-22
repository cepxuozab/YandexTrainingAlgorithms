#include <iostream>
#include <vector>

class Graph {
  std::vector<std::vector<int>> adj_list;
  std::vector<int> cnt;

 public:
  Graph(int n) : adj_list(n + 1), cnt(n + 1) {}
  void AddEdge(int a, int b) {
    adj_list[a].push_back(b);
    adj_list[b].push_back(a);
  }

  std::vector<int> SizeAllSubtree() {
    NumberOfNodes(1, 0);
    return {std::next(cnt.begin()), cnt.end()};
  }

 private:
  void NumberOfNodes(int s, int e) {
    cnt[s] = 1;
    for (int u : adj_list[s]) {
      if (u == e) continue;
      NumberOfNodes(u, s);
      cnt[s] += cnt[u];
    }
  }
};

int main() {
  int n;
  std::cin >> n;
  Graph graph(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    std::cin >> a >> b;
    graph.AddEdge(a, b);
  }
  for (int i : graph.SizeAllSubtree()) {
    std::cout << i << ' ';
  }
}
