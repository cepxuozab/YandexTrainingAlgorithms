#include <bitset>
#include <iostream>
#include <vector>


int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  size_t n;
  int k;
  std::cin >> n >> k;
  std::vector<std::bitset<1001>> xy(n + 1);
  std::vector<std::bitset<1001>> yz(n + 1);
  std::vector<std::bitset<1001>> xz(n + 1);

  while (k--) {
    size_t x, y, z;
    std::cin >> x >> y >> z;
    xy[x][y] = 1;
    yz[y][z] = 1;
    xz[x][z] = 1;
  }

  for (size_t x = 1; x < xy.size(); ++x) {
    for (size_t y = 1; y < xy.size(); ++y) {
      if (xy[x][y] == 0) {
        auto projection = yz[y] | xz[x];
        if (projection.count() < n) {
          for (size_t z = 1; z <= n; ++z) {
            if (projection[z] == 0) {
              std::cout << "NO" << '\n';
              std::cout << x << ' ' << y << ' ' << z << '\n';
              return 0;
            }
          }
        }
      }
    }
  }

  std::cout << "YES" << '\n';

  return 0;
}