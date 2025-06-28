#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

int main() {
    // Read input
    int N, M;
    std::cin >> N >> M;
    
    std::vector<int> m(N);
    for (auto& mass : m) std::cin >> mass;
    
    // Initialize DP array (true/false for possible weights)
    std::vector<bool> dp(M + 1, false);
    dp[0] = true;  // Base case: zero weight
    
    // Process each gold bar
    for (int bar : m) {
        // Update possible weights in reverse order
        for (int w = M; w >= bar; --w) {
            if (dp[w - bar]) {
                dp[w] = true;
            }
        }
    }
    
    // Find the maximum possible weight
    int max_gold = M;
    while (max_gold >= 0 && !dp[max_gold]) {
        --max_gold;
    }
    
    std::cout << max_gold << '\n';
    
    return 0;
}