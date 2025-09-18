#include <iostream>
#include <cmath>

double func(double x) {
    return sin(cos(x*x - x - 1));
}

double coefx(int i, double* y, double* x)
{
    double sum = 0;
    double wki;

    for (int k = 0; k <= i; ++k) 
    {
        wki = 1.0;
        for (int j = 0; j <= i; ++j)
        {
            if (j == k) continue;
            wki *= x[k] - x[j];
        }

        sum += y[k] / wki;
    }

    return sum;
}

double NewtonPolinomial(int n, double* y, double* x, double x0)
{
    double sum = 0;
    double mult;

    if (n == 0) return sum;

    for (int i = 0; i < n; ++i)
    {
        mult = 1.0;
        for (int j = 0; j < i; ++j)
        {
            mult *= x0 - x[j];
        }

        sum += coefx(i, y, x) * mult;
    }

    return sum;
}

double* calculate_nodes(int size)
{
    double* x_list = new double[size];

    double nod0 = M_PI / size;
    for (int i = 0; i != size; i++) x_list[i] = nod0 * i;

    return x_list;
}

double* calculate_y(int size, double* x_list)
{
    double* y_list = new double[size];

    double nod0 = M_PI / size;
    for (int i = 0; i != size; i++) y_list[i] = func(x_list[i]);

    return y_list;
}

int main()
{
    int n = 10;
    int m = 3 * n;

    double* x_list = calculate_nodes(n);
    double* y_list = calculate_y(n, x_list);

    std::cout << NewtonPolinomial(n, y_list, x_list, 0.5);

    std::cout << "\n";

    double* x_list2 = calculate_nodes(m);
    double* y_list2 = calculate_y(m, x_list2);

    std::cout << NewtonPolinomial(m, y_list2, x_list2, 0.5);
    std::cout << "\n";

    
    for (int i = 0; i != m; i++)
    {
        double y = func(x_list2[i]); 
        double yl = NewtonPolinomial(n, y_list, x_list, x_list2[i]);
        double error = std::fabs(y - yl);

        std::cout << std::to_string(y) + " " + std::to_string(yl) + " " + std::to_string(error); 
        std::cout << "\n";
    }
    
    double max_error = 0.0;
    for (int i = 0; i != m; i++)

    {
        double y = func(x_list2[i]); 
        double yl = NewtonPolinomial(14, y_list, x_list, x_list2[i]);
        double error = std::fabs(y - yl);

        if (error > max_error) max_error = error;
    }

    if (not max_error > pow(10, -1)) std::cout << "Success";

    delete[] x_list;
    delete[] x_list2;
    delete[] y_list;
    delete[] y_list2;

    return 0;
}
