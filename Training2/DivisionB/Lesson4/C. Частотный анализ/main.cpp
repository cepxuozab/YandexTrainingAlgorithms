#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

static auto const FastIO = []() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	return nullptr;
}();

int main() {
	freopen("input.txt", "r", stdin);
	std::unordered_map<std::string, int> maps;
	for (std::string str; std::cin >> str;) {
		maps[str]++;
	}
	std::vector<std::pair<std::string, int>> words(maps.begin(), maps.end());
	auto const compare = [](std::pair<std::string, int> const& lhs,
		std::pair<std::string, int>const& rhs)
	{
		return lhs.second == rhs.second ? lhs.first<rhs.first : lhs.second>rhs.second;
	};
	std::sort(words.begin(), words.end(), compare);
	for (auto const& [word, cnt] : words) {
		std::cout << word << '\n';
	}
	return 0;
}