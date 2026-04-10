#include <iostream>
#include <vector>
#include <string>

auto main() -> int {
	int n, m, k;
	std::cin >> n >> m >> k;

	std::vector<std::string> windows(n);
	std::string buffer;
	int cur = 0;

	for (int i = 0; i < m; ++i) {
		std::string cmd;
		std::cin >> cmd;

		if (cmd == "Next") {
			cur = (cur + 1) % n;
		} else if (cmd == "Backspace") {
			if (!windows[cur].empty()) {
				windows[cur].pop_back();
			}
		} else if (cmd == "Copy") {
			std::string &w = windows[cur];
			int len = w.size();
			int start = std::max(0, len - k);
			buffer = w.substr(start);
		} else if (cmd == "Paste") {
			windows[cur] += buffer;
		} else {
			// это буква
			windows[cur] += cmd;
		}
	}

	const std::string &w = windows[cur];

	if (w.empty()) {
		std::cout << "Empty\n";
	} else {
		int len = w.size();
		int start = std::max(0, len - k);
		std::cout << w.substr(start) << "\n";
	}

	return 0;
}