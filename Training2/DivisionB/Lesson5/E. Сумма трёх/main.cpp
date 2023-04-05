#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
[[maybe_unused]] static auto const fastIO = []() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	return nullptr;
}();

auto Read() -> std::vector<int64_t> {
	int n;
	std::cin >> n;
	std::vector<int64_t> arr(n);
	for (auto& i : arr) {
		std::cin >> i;
	}
	return arr;
}

int main() {

	int64_t sum;
	std::cin >> sum;
	std::vector<int64_t> A(Read());
	std::vector<int64_t> B(Read());
	std::unordered_map<int64_t, int> dict;
	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		int64_t x;
		std::cin >> x;
		if (x > sum) {
			continue;
		}
		dict.emplace(x, i);
	}
	for (int i = 0; i < (int)A.size(); ++i) {
		auto a = A[i];
		for (int j = 0; j < (int)B.size(); ++j) {
			auto b = B[j];
			if (auto it = dict.find(sum - a - b); it != dict.end()) {
				std::cout << i << ' ' << j << ' ' << it->second << '\n';
				return 0;
			}
		}
	}
	std::cout << "-1\n";
	return 0;
}