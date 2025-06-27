#include <iostream>
#include <vector>

class FenwickTree {
private:
  std::vector<long long> tree;
  int size;

public:
  FenwickTree(int n) : tree(n + 1, 0), size(n) {}

private:
  // Прибавить значение на позиции i
  void add(int i, long long value) {
    while (i <= size) {
      tree[i] += value;
      i += i & -i;
    }
  }

  // Префиксная сумма [1, r]
  long long prefixSum(int r) const {
    long long result = 0;
    while (r > 0) {
      result += tree[r];
      r -= r & -r;
    }
    return result;
  }

public:
  // Сумма на отрезке [l, r]
  long long rangeSum(int l, int r) const {
    return prefixSum(r) - prefixSum(l - 1);
  }

  // Получить значение на позиции i
  long long get(int i) const { return rangeSum(i, i); }

  // Присвоить новое значение на позиции i
  void assign(int i, long long value) {
    long long current = get(i);
    add(i, value - current);
  }
};

int main() {
  int n, k;
  std::cin >> n >> k;

  FenwickTree ft(n);

  while (k--) {
    char command;
    std::cin >> command;

    if (command == 'A') {
      int i;
      long long value;
      std::cin >> i >> value;
      ft.assign(i, value);
    } else if (command == 'Q') {
      int l, r;
      std::cin >> l >> r;
      std::cout << ft.rangeSum(l, r) << '\n';
    }
  }

  return 0;
}
