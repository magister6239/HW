#include <iostream>
#include <cmath>

double y_exact(double x) {
    return std::exp(x * x);
}

double max_err(int N, double a, double b, double y0) {
    double h = (b - a) / N;
    double x = a;
    double y = y0;
    double max = std::fabs(y - y_exact(x));

    for (int i = 0; i < N; ++i) {
        double ynext = y + h * (2.0 * x * y);
        x += h;
        y = ynext;
        double e = std::fabs(y - y_exact(x));
        if (e > max) max = e;
    }
    return max;
}

int main() {
    const double a = 0, b = 1, y0 = 1;
    int N = 32;
    double h = (b - a) / N;

    std::cout << "j        x_j    y_pred     y_real    error\n";
    double x = a, y = y0;
    std::cout << 0 << " " << x << " " << y << " " << y_exact(x) << " " << std::fabs(y - y_exact(x)) << "\n";
    for (int j = 0; j < N; ++j) {
        double ynext = y + h * (2 * x * y);
        x += h;
        y = ynext;
        std::cout << (j + 1) << "           " << x << "           " << y << "           " << y_exact(x) << "           " << std::fabs(y - y_exact(x)) << "\n";
    }

    int found = -1;
    for (int N = 1; N <= 65536; ++N) {
        if (max_err(N, a, b, y0) < 1e-2) {
            found = N;
            break;
        }
    }

    if (found > 0)
        std::cout << found;
    else
        std::cout << "No dice";

    return 0;
}
