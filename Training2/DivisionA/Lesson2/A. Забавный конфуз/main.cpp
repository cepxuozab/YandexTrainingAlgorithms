#include <iostream>
#include <vector>
#include <algorithm>

auto main() -> int {
	int n, k;
	std::cin >> n >> k;
	std::vector<int64_t> arr(n);
	for (int64_t& i : arr) std::cin >> i;
	auto const [a, b] = std::minmax_element(arr.begin(), arr.end());
	std::cout << (*b - *a) << std::endl;
	return 0;
}