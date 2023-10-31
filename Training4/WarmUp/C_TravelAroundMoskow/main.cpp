#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>


int main()
{
    double x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    double r1 = std::hypot(x1, y1);
    double r2 = std::hypot(x2, y2);
    double dot = x1 * x2 + y1 * y2; //;// # Dot product between[x1, y1] and [x2, y2]
    double det = x1 * y2 - y1 * x2; //     # Determinant
    double angle = atan2(det, dot); //  # atan2(y, x) or atan2(sin, cos)
    double dist1 = r1 + r2;
    double dist2 = std::abs(r2 - r1) + std::abs(std::min(r2, r1) * angle);
    std::cout << std::setprecision(12) << std::min(dist1, dist2);
}
