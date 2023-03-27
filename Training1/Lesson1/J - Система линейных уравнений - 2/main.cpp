#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

int const NOSOLUTION = 0;
int const EQUOTION = 1;
int const ONE_SOLUTION = 2;
int const ANY_Y = 3;
int const ANY_X = 4;
int const MANY_SOLUTIONS = 5;
double const EPSILON = 1.e-7;
int const PRESISION = 8;

bool IsZero(double x)
{
    return std::fabs(x) < EPSILON;
}

void OneSolution(double a, double b, double c);

void ManySolution(double a, double b, double c);

int main()
{
    double a1, b1, a2, b2, c1, c2;
    std::cin >> a1 >> b1 >> a2 >> b2 >> c1 >> c2;
    if (IsZero(a1) && IsZero(b1) && IsZero(a2) && IsZero(b2)) {
        if (IsZero(c1) && IsZero(c2)) {
            std::cout << MANY_SOLUTIONS << std::endl;
        } else {
            std::cout << NOSOLUTION << std::endl;
        }
        return 0;
    }
    if (IsZero(a1) && IsZero(b1)) {
        if (!IsZero(c1)) {
            std::cout << NOSOLUTION << std::endl;
        } else {
            ManySolution(a2, b2, c2);
        }
        return 0;
    }
    if (IsZero(a2) && IsZero(b2)) {
        if (!IsZero(c2)) {
            std::cout << NOSOLUTION << std::endl;
        } else {
            ManySolution(a1, b1, c1);
        }
        return 0;
    }

    double const determ = a1 * b2 - a2 * b1;
    if (!IsZero(determ)) {
        double x_determ = b2 * c1 - b1 * c2;
        double y_determ = a1 * c2 - a2 * c1;
        OneSolution(x_determ, y_determ, determ);
    } else {
        if (!IsZero(a1 * c2 - a2 * c1) || !IsZero(b1 * c2 - b2 * c1)) {
            std::cout << NOSOLUTION << std::endl;
        } else {
            ManySolution(a1, b1, c1);
        }
    }
}

void OneSolution(double a, double b, double c)
{
    std::cout << ONE_SOLUTION << ' ';
    std::cout << std::fixed
              << std::setprecision(PRESISION)
              << a / c << ' '
              << b / c << std::endl;
}

void ManySolution(double a, double b, double c)
{
    if (IsZero(a) && IsZero(b) && !IsZero(c)) {
        std::cout << NOSOLUTION << std::endl;
        return;
    }
    if (IsZero(a) && IsZero(b) && IsZero(c)) {
        std::cout << MANY_SOLUTIONS << std::endl;
        return;
    }
    if (IsZero(a)) {
        std::cout << ANY_X << ' ';
        std::cout << std::fixed
                  << std::setprecision(PRESISION)
                  << c / b;
        return;
    }
    if (IsZero(b)) {
        std::cout << ANY_Y << ' ';
        std::cout << std::fixed
                  << std::setprecision(PRESISION)
                  << c / a;
        return;
    }
    std::cout << EQUOTION << ' ';
    std::cout << std::fixed
              << std::setprecision(PRESISION)
              << -a / b << ' ' << c / b;
}
