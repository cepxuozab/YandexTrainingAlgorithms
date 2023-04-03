#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

static auto const FastIO = []() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	return nullptr;
}();

long long primes[] = { 126247697, 193877777, 303595777, 384160001, 406586897, 562448657, 655360001 };


struct Fibb {
	std::vector<long long> reminders;
	Fibb() {
		int primesCount = std::size(primes);
		reminders.resize(primesCount);
	};
	Fibb(long long x) {
		int primesCount = std::size(primes);
		reminders.resize(primesCount);
		for (int i = 0; i < primesCount; ++i) {
			reminders[i] = (x % primes[i]);
		}
	}

	void shift(int digit) {
		for (int i = 0; i < (int)std::size(primes); ++i) {
			reminders[i] *= 10;
			reminders[i] += digit;
			reminders[i] %= primes[i];
		}
	}
	Fibb add(Fibb other) {
		Fibb result((int)std::size(primes));
		for (int i = 0; i < (int)std::size(primes); ++i) {
			result.reminders[i] = (reminders[i] + other.reminders[i]) % primes[i];
		}
		return result;
	}

	bool operator <(Fibb const& other) const {
		return std::lexicographical_compare(reminders.begin(), reminders.end(),
			other.reminders.begin(), other.reminders.end());
	}

};

int main() {
	freopen("input.txt", "r", stdin);
	int maxNumberLength = 5000;

	double phi = (sqrt(5) + 1) / 2;
	int needFibsCount = 25000;

	Fibb* fibs = new Fibb[needFibsCount];
	fibs[0] = Fibb(1);
	fibs[1] = Fibb(1);

	for (int i = 2; i < needFibsCount; ++i) {
		fibs[i] = fibs[i - 1].add(fibs[i - 2]);
	}

	std::sort(fibs, fibs + needFibsCount);

	int queries;
	std::cin >> queries;
	while (queries-- > 0) {
		std::string query;
		std::cin >> query;
		Fibb hash;
		for (char digit : query) {
			hash.shift(digit - '0');
		}
		bool Index = std::binary_search(fibs, fibs + needFibsCount, hash);
		Index ? puts("Yes") : puts("No");
	}
}