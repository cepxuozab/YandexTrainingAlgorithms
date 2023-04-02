#include <iostream>
#include <stdexcept>


auto main() -> int
{
	if (freopen("input.txt", "r", stdin) == nullptr) {
		throw std::invalid_argument("can't read");
	}
	int n;
	std::cin >> n;
	int max = 0;
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		int x; std::cin >> x;
		max = max > x ? max : x;
		sum += x;
	}
	std::cout << sum - max << std::endl;
	return 0;
}
