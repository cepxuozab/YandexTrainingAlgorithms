#include <iostream>
using namespace std;

int main()
{
    int n, k[64][3];
    cin >> n;
    for (int z = 0; z < n; z++) {
        cin >> k[z][1] >> k[z][2];
        k[z][0] = 4;
    }
    if (n == 1) {
        cout << 4;
        return 0;
    }
    for (int z = 0; z < n - 1; z++)
        for (int x = z + 1; x < n; x++) {
            if ((abs(k[z][1] - k[x][1]) == 1
                    && k[z][2] - k[x][2] == 0)
                || ((abs(k[z][2] - k[x][2]) == 1
                    && k[z][1] - k[x][1] == 0))) {
                k[z][0]--;
                k[x][0]--;
            }
        }
    int s = 0;
    for (int z = 0; z < n; z++)
        s += k[z][0];
    cout << s;

    return 0;
}
