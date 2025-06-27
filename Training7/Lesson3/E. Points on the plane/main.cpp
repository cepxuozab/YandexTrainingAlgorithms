#include <iostream>
using namespace std;

int main() {
    int x, y;
    cin >> x >> y;
    int c = x ^ y;
    cout << c << '\n';

    cin >> x >> c;
    y = c ^ x;
    cout << y << '\n';

    return 0;
}
