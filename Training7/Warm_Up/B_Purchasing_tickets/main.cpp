#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

pair<int, vector<vector<int>>> read_input()
{
    int n;
    cin >> n;
    vector<vector<int>> buy_time(n, vector<int>(3));
    for (int i = 0; i < n; ++i)
    {
        cin >> buy_time[i][0] >> buy_time[i][1] >> buy_time[i][2];
    }
    return {n, buy_time};
}

int tickets(int n, vector<vector<int>> &buy_time)
{
    const int max_t = numeric_limits<int>::max();
    vector<int> dp(n + 3, max_t);

    // Дополняем `buy_time` и `dp`
    buy_time.push_back({max_t, max_t, max_t});
    buy_time.push_back({max_t, max_t, max_t});
    buy_time.push_back({0, 0, 0});
    dp[n + 2] = 0;

    for (int i = 0; i < n; ++i)
    {
        int t_a = (i - 1 >= 0 ? dp[i - 1] : 0) + buy_time[i][0];
        int t_b =
            (i - 2 >= 0 ? dp[i - 2] : 0) + buy_time[i - 1 >= 0 ? i - 1 : 0][1];
        int t_c =
            (i - 3 >= 0 ? dp[i - 3] : 0) + buy_time[i - 2 >= 0 ? i - 2 : 0][2];
        dp[i] = min({t_a, t_b, t_c});
    }

    return dp[n - 1];
}

int main()
{
    auto [n, buy_time] = read_input();
    cout << tickets(n, buy_time) << endl;
    return 0;
}
