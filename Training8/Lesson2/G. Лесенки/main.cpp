#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;

    // dp[x] = количество разбиений числа x на различные слагаемые
    vector<long long> dp(N + 1, 0);
    dp[0] = 1; // база

    // Перебираем возможные слагаемые от 1 до N
    for (int num = 1; num <= N; ++num) {
        // Обновляем dp в обратном порядке, чтобы каждое число использовалось не более одного раза
        for (int x = N; x >= num; --x) {
            dp[x] += dp[x - num];
        }
    }

    cout << dp[N] << '\n';
    return 0;
}