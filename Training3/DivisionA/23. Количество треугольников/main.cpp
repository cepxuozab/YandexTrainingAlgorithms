#include <iostream>
#include <cstdint>

int main() {
	uint64_t n;
	std::cin >> n;
	auto res = n * (n + 2) * (2 * n + 1);
	if (n % 2 != 0) res -= 1;
	std::cout << res / 8;
}

