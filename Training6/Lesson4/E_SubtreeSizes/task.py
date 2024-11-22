import sys

sys.setrecursionlimit(100000)


class Graph:
    def __init__(self, num: int):
        self.adj_list = [[] for _ in range(num + 1)]
        self.sizes = [0] * (num + 1)

    def add_edge(self, a: int, b: int):
        self.adj_list[a].append(b)
        self.adj_list[b].append(a)

    def __count_subtree_sizes(self, s, e):
        self.sizes[s] = 1
        for u in self.adj_list[s]:
            if u == e:
                continue
            self.__count_subtree_sizes(u, s)
            self.sizes[s] += self.sizes[u]

    def get_subtree_sizes(self):
        self.__count_subtree_sizes(1, 0)
        return ' '.join([str(i) for i in self.sizes[1:]])


if __name__ == '__main__':
    n = int(sys.stdin.readline().rstrip())
    graph = Graph(n)
    for _ in range(n - 1):
        from_, to_ = map(int, sys.stdin.readline().rstrip().split())
        graph.add_edge(from_, to_)
    print(graph.get_subtree_sizes())
