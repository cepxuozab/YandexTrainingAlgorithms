#include <iostream>
#include <vector>
#include<numeric>

[[maybe_unused]] static auto const fastIO = []() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	return nullptr;
}();

using Type = int64_t;

auto ReadVector(unsigned n) -> std::vector<Type>;

auto main() -> int
{
	if (freopen("input.txt", "r", stdin) == nullptr) {
		throw std::invalid_argument("can't read");
	}
	if (freopen("output.txt", "w", stdout) == nullptr) {
		throw std::invalid_argument("can't write");
	}

	unsigned n;
	unsigned m;
	std::cin >> n >> m;
	auto numbers = ReadVector(n);
	std::partial_sum(numbers.begin(), numbers.end(), numbers.begin());
	for (unsigned i = 0; i < m; ++i) {
		size_t left;
		size_t right;
		std::cin >> left >> right;
		left--, right--;
		if (left == 0) {
			std::cout << numbers[right] << '\n';
		}
		else {
			std::cout << numbers[right] - numbers[left - 1] << '\n';
		}
	}

}
auto ReadVector(unsigned n) -> std::vector<Type>
{
	std::vector<Type> arr(n);
	for (auto& a : arr) {
		std::cin >> a;
	}
	return arr;
}
