#include <iostream>
#include <cmath>

double func(double x) {
    return sin(cos(x*x - x - 1));
}

double lagrangePolinomial(int n, double* y, double* x, double x0)
{
    double result = 0;

    for (int q = 0; q != n; q++)
    {
        double multiply_result = 1.0; 
        for (int q2 = 0; q2 != n; q2++)
        {
            if (q2 != q)
            multiply_result *= (x0 - x[q2]) / (x[q] - x[q2]);
        }
        result += y[q] * multiply_result;
    }

    return result;
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

    std::cout << lagrangePolinomial(n, y_list, x_list, 0.5);

    std::cout << "\n";

    double* x_list2 = calculate_nodes(m);
    double* y_list2 = calculate_y(m, x_list2);

    std::cout << lagrangePolinomial(m, y_list2, x_list2, 0.5);
    std::cout << "\n";

    
    for (int i = 0; i != m; i++)
    {
        double y = func(x_list2[i]); 
        double yl = lagrangePolinomial(n, y_list, x_list, x_list2[i]);
        double error = std::fabs(y - yl);

        std::cout << std::to_string(y) + " " + std::to_string(yl) + " " + std::to_string(error); 
        std::cout << "\n";
    }
    
    double max_error = 0.0;
    for (int i = 0; i != m; i++)

    {
        double y = func(x_list2[i]); 
        double yl = lagrangePolinomial(13, y_list, x_list, x_list2[i]);
        double error = std::fabs(y - yl);

        if (error > max_error) max_error = error;
    }

    if (not max_error > pow(10, -2)) std::cout << "Success";

    delete[] x_list;
    delete[] x_list2;
    delete[] y_list;
    delete[] y_list2;

    return 0;
}
