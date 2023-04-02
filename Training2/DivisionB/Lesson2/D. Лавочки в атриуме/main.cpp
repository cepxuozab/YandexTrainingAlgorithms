#include <iostream>
#include <vector>
#include <stdexcept>

auto main() -> int
{
	if (freopen("input.txt", "r", stdin) == nullptr) {
		throw std::invalid_argument("can't read");
	}
	int L;
	int K;
	std::cin >> L >> K;
	constexpr int SIZE = 10001;
	std::vector<bool> arr(SIZE, false);
	for (int i = 0; i < K; ++i) {
		int x; std::cin >> x;
		arr[x] = true;
	}
	if (L % 2 != 0 && arr[L / 2]) {
		std::cout << L / 2 << std::endl;
		return 0;
	}
	for (int i = (L - 1) / 2; i >= 0; --i) {
		if (arr[i]) {
			std::cout << i << ' ';
			break;
		}
	}
	for (int i = L / 2; i < L; ++i) {
		if (arr[i]) {
			std::cout << i << std::endl;
			break;
		}
	}
}
