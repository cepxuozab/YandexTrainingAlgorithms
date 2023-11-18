#include <iostream>
#include <vector>
using namespace std;


void rec(int size, int x, std::vector<bool>& lines, std::vector<bool>& diag1, std::vector<bool>& diag2, int& count) {
	if (x == size) {
		count++;
		return;
	}

	for (int y = 0; y < size; y++) {
		// If position threatened, go to next
		if (lines[y] || diag1[y + x] || diag2[y - x + size])
			continue;

		// position queen
		lines[y] = true;
		diag1[y + x] = true;
		diag2[y - x + size] = true;

		// search for next queen
		rec(size, x + 1, lines, diag1, diag2, count);

		// deposition queen
		lines[y] = false;
		diag1[y + x] = false;
		diag2[y - x + size] = false;
	}
}

int main(int argc, char** args)
{
	int size ;
	std::cin >> size;
	int count = 0;
	std::vector<bool> lines(size,false);
	std::vector<bool> diag1(size * 2,false);
	std::vector<bool> diag2(size * 2, false);;

	rec(size, 0, lines, diag1, diag2, count);
	cout << count << endl;
}
