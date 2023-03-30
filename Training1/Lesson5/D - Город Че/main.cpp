#include <iostream>
#include <vector>

auto main() -> int
{
	int n, r;
	std::cin >> n >> r;
	std::vector<int>arr(n);
	for (int& i : arr)std::cin >> i;
	int64_t answer = 0;
	int j = 0;
	for (int i = 0; i < n; ++i) {
		while (j < n && arr[j] - arr[i] <= r) {
			j++;
		}
		answer += (n - j);
	}
	std::cout << answer << '\n';
}