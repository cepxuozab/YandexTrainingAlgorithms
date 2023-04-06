#include <iostream>
#include <vector>
#include <string>
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
	if (!freopen("input.txt", "r", stdin)) {
		throw std::invalid_argument("can't read");
	}
	int n;
	int m;
	std::cin >> n >> m;
	std::vector<std::pair<int, int>> a, b;
	a.reserve(n);
	for (int i = 0; i < n; ++i) {
		int x;
		std::cin >> x;
		a.emplace_back(i + 1, x);
	}
	b.reserve(m);
	for (int i = 0; i < m; ++i) {
		int x;
		std::cin >> x;
		b.emplace_back(i + 1, x);
	}
	auto compare = [](std::pair<int, int> const& lhs, std::pair<int, int> const& rhs)
	{
		return lhs.second < rhs.second;
	};
	std::sort(a.begin(), a.end(), compare);
	std::sort(b.begin(), b.end(), compare);
	std::vector<std::string> answer;
	int i = 0;
	int j = (m / 2);
	int k = 0;
	while ((j < m) && (k < n)) {
		while (k < n && a[k].second <= b[i].second) k++;
		if (k == n) break;
		while (j < m && a[k].second >= b[j].second) j++;
		if (j == m) break;
		answer.push_back(
			std::to_string(a[k].first)
			+ " " + std::to_string(b[i].first)
			+ " " + std::to_string(b[j].first)
		);
		i++;
		j++;
		k++;

	}
	std::cout << answer.size() << '\n';
	for (auto const& str : answer) {
		std::cout << str << '\n';
	}

}