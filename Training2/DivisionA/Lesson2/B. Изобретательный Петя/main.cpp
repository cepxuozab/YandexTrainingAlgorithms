#include <iostream>
#include <string>

int main() {
	std::string x, z;
	std::cin >> x >> z;
	int xsize = x.size();
	int zsize = z.size();
	int ans = 0;
	for (int zstart = zsize - 1; zstart >= 0; --zstart) {
		int xpos = xsize - 1;
		bool flag = true;
		for (int zpos = zstart; zpos >= 0; --zpos) {
			if (z[zpos] != x[xpos]) {
				flag = false;
				break;
			}
			else {
				xpos = (xpos - 1 + xsize) % xsize;
			}
		}
		if (flag) {
			ans = zstart + 1;
			break;
		}
	}
	for (; ans < zsize; ++ans) {
		std::cout << z[ans];
	}

}