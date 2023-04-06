#include <iostream>

using namespace std;

typedef unsigned long long ull;

int main() {
    ull l_x = 0, r_x = 1000000000;
    while (l_x != r_x) {
        int ans;
        cout << l_x << " " << 0 << endl;
        cin >> ans;
        cout << r_x << " " << 0 << endl;
        cin >> ans;
        if (ans) {
            l_x = (r_x + l_x) / 2 + 1;
        }
        else {
            r_x = (r_x + l_x) / 2;
        }
    }
    ull l_y = 0, r_y = 1000000000;
    while (l_y != r_y) {
        int ans;
        cout << l_x << " " << l_y << endl;
        cin >> ans;
        cout << l_x << " " << r_y << endl;
        cin >> ans;
        if (ans) {
            l_y = (r_y + l_y) / 2 + 1;
        }
        else {
            r_y = (r_y + l_y) / 2;
        }
    }
    cout << "A " << l_x << " " << l_y << endl;

    return 0;
}