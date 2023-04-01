#include <iostream>

using namespace std;

int findNearestVertex(int d, int x, int y)
{
    if (x <= 0) {
        return y <= d / 2 ? 1 : 3;
    }
    if (y <= 0) {
        return x <= d / 2 ? 1 : 2;
    }
    return (y <= x) ? 2 : 3;
}

int main()
{
    int d, x, y;
    cin >> d >> x >> y;

    if (x >= 0 && y >= 0 && (y + x) <= d) {
        cout << 0;
    }
    else {
        cout << findNearestVertex(d, x, y);
    }

    return 0;
}
