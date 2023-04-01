#include <iostream>
#include <stdexcept>


auto main() -> int
{
	if (freopen("input.txt", "r", stdin) == nullptr) {
		throw std::invalid_argument("can't read");
	}
	short d, m, y;
	std::cin >> d >> m >> y;

	std::cout << (d > 12 || m > 12 || d == m);
	return 0;
}
