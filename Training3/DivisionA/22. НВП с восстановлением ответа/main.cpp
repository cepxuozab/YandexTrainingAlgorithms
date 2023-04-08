#include <algorithm>
#include <iostream>
#include <vector>
#include <ranges>
#include <iterator>
int main()
{
    int n;
    std::cin >> n;
    std::vector<int> sequence(n), dp(n, 1), prev(n, -1);
    for (int& elem : sequence) {
        std::cin >> elem;
    }
    for (int i = 1; i < n; ++i) {
        int j = i;
        int j_max_seq = j;
        int max_seq_count = 0;
        while (j >= 0) {
            if (sequence[j] < sequence[i] and dp[j] > max_seq_count) {
                j_max_seq = j;
                max_seq_count = dp[j];
            }
            j--;
        }
        if (j_max_seq != i) {
            dp[i] += dp[j_max_seq];
            prev[i] = j_max_seq;
        }
    }
    int max_i = std::max_element(dp.begin(), dp.end()) - dp.begin();
    std::vector<int> answer{ sequence[max_i] };
    for (int i_prev = prev[max_i]; i_prev != -1; i_prev = prev[i_prev]) {
        answer.push_back(sequence[i_prev]);
    }
    std::ranges::reverse_copy(answer, std::ostream_iterator<int>(std::cout, " "));
}
