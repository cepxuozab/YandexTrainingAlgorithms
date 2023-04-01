#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

typedef int16_t Type;

auto BodySwap(Type a, Type b, std::vector<Type>& bodies)
{
	std::cout << a << ' ' << b << '\n';
	std::swap(bodies[b], bodies[a]);
	return bodies[b];
}

auto main() -> int
{
	int n;
	int m;
	std::cin >> n >> m;
	std::vector<Type> bodies(n + 1);
	std::iota(bodies.begin(), bodies.end(), 0);
	for (int i = 0; i < m; ++i) {
		Type a, b;
		std::cin >> a >> b;
		std::swap(bodies[b], bodies[a]);
	}
	for (int i = 1; i < n - 1; ++i) {
		if (bodies[i] != i) {
			int now = i;
			while (bodies[now] != i) {
				now = BodySwap(now, n - 1, bodies);
			}
			now = BodySwap(now, n, bodies);
			now = BodySwap(now, n, bodies);
			BodySwap(bodies[n - 1], n - 1, bodies);
		}
	}
	if (bodies[n - 1] == n) {
		BodySwap(n - 1, n, bodies);
	}
}