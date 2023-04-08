#include <iostream>
#include <stack>
#include <vector>


int main() {
	if (freopen("input.txt", "r", stdin) == nullptr) {
		puts("Can't open input.txt");
		return 1;
	}
	int n;
	std::cin >> n;
	std::vector<int> wagons(n);
	for (auto& wagon : wagons) {
		std::cin >> wagon;
	}
	int out = 0;
	std::stack<int> depo;
	for (int wagon : wagons) {
		depo.push(wagon);
		while (!depo.empty() && depo.top() == out + 1) {
			out++;
			depo.pop();
		}
	}
	depo.empty() ? puts("YES") : puts("NO");
}
