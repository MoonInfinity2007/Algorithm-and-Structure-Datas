#include <iostream>
#include <iomanip>

int main() {
    double a, b, c, d;
    std::cin >> a >> b >> c >> d;
    auto f = [&](double x) -> double {
        return a*x*x*x + b*x*x + c*x + d;
    };
    double left = -1e10, right = 1e10;
    for (int i = 0; i < 10000; ++i) {
        double mid = (left + right) / 2;
        if (f(left) * f(mid) > 0) left = mid;
        else right = mid;
    }
    std::cout << std::setprecision(10) << std::fixed;
    std::cout << (left + right) / 2;
    return 0;
}