#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long W, H;
    cin >> n >> W >> H;

    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    auto canPlace = [&](double k) -> bool {
        double total_height = 0.0;
        long long current_b = -1;
        double current_width = 0.0;

        for (int i = 0; i < n; i++) {
            double word_width = k * a[i];
            // Если слово не помещается даже в отдельную строку — невозможно
            if (word_width > W) {
                return false;
            }

            if (current_b == -1) {
                current_b = b[i];
                current_width = word_width;
            } else if (b[i] == current_b) {
                if (current_width + word_width <= W) {
                    current_width += word_width;
                } else {
                    total_height += k * current_b;
                    if (total_height > H) return false;
                    current_width = word_width;
                    // current_b unchanged
                }
            } else {
                total_height += k * current_b;
                if (total_height > H) return false;
                current_b = b[i];
                current_width = word_width;
            }
        }

        total_height += k * current_b;
        return total_height <= H;
    };

    double lo = 0.0, hi = 1e9;
    // 70 итераций достаточно для относительной погрешности < 1e-12
    for (int iter = 0; iter < 70; iter++) {
        double mid = (lo + hi) * 0.5;
        if (canPlace(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    cout << fixed << setprecision(15) << lo << '\n';
    return 0;
}