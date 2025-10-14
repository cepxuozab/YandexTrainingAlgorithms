#include <iostream>
#include <vector>
using namespace std;

bool isPrime(int n) {
  if (n < 2)
    return false;
  if (n == 2)
    return true;
  if (n % 2 == 0)
    return false;
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0)
      return false;
  }
  return true;
}

int main() {
  int N;
  cin >> N;

  // dp[i] = true если позиция с i спичками выигрышная для текущего игрока
  vector<bool> dp(N + 1, false);

  // Базовый случай: 0 спичек - проигрышная позиция (предыдущий игрок забрал
  // последнюю)
  dp[0] = false;

  // Заполняем dp
  for (int i = 1; i <= N; i++) {
    // Пробуем взять 1, 2 или 3 спички
    for (int take = 1; take <= 3; take++) {
      if (take > i)
        continue; // Нельзя взять больше, чем есть

      int remaining = i - take;

      // Проверяем, что оставшееся количество не простое
      if (!isPrime(remaining)) {
        // Если можем попасть в проигрышную позицию - текущая выигрышная
        if (!dp[remaining]) {
          dp[i] = true;
          break;
        }
      }
    }
  }

  // Если позиция N выигрышная для первого игрока - он побеждает
  cout << (dp[N] ? 1 : 2) << '\n';

  return 0;
}