#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

constexpr double PI = 3.1415926535897932384626433832795; // Констнанта PI
constexpr double EPS = 1e-15; 

// Метод для упрощённого вывода матрицы 

void printMatrix(const std::vector<std::vector<double>>& M) {
    std::cout << std::fixed << std::setprecision(6);
    for (std::size_t i = 0; i < M.size(); ++i) {
        for (std::size_t j = 0; j < M[i].size(); ++j) {
            std::cout << std::setw(12) << M[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// Задание 2. Оперции над векторами

void printVector(const std::vector<double>& v) {
    std::cout << std::fixed << std::setprecision(9);
    for (double x : v) std::cout << std::setw(14) << x << "\n";
}

std::vector<double> matVecMultiply(const std::vector<std::vector<double>>& A,
    const std::vector<double>& x) {
    std::size_t n = A.size();
    std::vector<double> y(n, 0.0);
    for (std::size_t i = 0; i < n; ++i) {
        double s = 0.0;
        for (std::size_t j = 0; j < n; ++j) s += A[i][j] * x[j];
        y[i] = s;
    }
    return y;
}

std::vector<double> vecSub(const std::vector<double>& u, const std::vector<double>& v) {
    std::size_t n = u.size();
    std::vector<double> r(n);
    for (std::size_t i = 0; i < n; ++i) r[i] = u[i] - v[i];
    return r;
}

double euclideanNorm(const std::vector<double>& v) {
    double s = 0.0;
    for (double x : v) s += x * x;
    return std::sqrt(s);
}

bool forwardGaussColPivot(std::vector<std::vector<double>>& A, std::vector<double>& rhs, std::vector<int>& perm) 
{
    std::size_t n = A.size();
    perm.resize(n);
    for (std::size_t i = 0; i < n; ++i) perm[i] = static_cast<int>(i);

    for (std::size_t k = 0; k < n; ++k) { // Проход по столбцам и строкам
        std::size_t best_j = k;
        double best_val = std::fabs(A[k][k]); 
        for (std::size_t j = k + 1; j < n; ++j) {
            double val = std::fabs(A[k][j]);
            if (val > best_val) { best_val = val; best_j = j; } // Ищем столбец best_j >= k, в котором |A[k][j]| максимально.
        }

        if (best_val < EPS) { // Надёжность алгоритма падает если ведущий элемент очень мал
            return false;
        }


        if (best_j != k) { // Перестановка столбцов, если выбранный столбец не равен k
            for (std::size_t i = 0; i < n; ++i) {
                std::swap(A[i][k], A[i][best_j]);
            }
            std::swap(perm[k], perm[best_j]);
        }

        double pivot = A[k][k]; // Нормировка ведущей строки
        for (std::size_t j = k + 1; j < n; ++j) A[k][j] /= pivot;
        rhs[k] /= pivot;
        A[k][k] = 1.0; 

        for (std::size_t i = k + 1; i < n; ++i) { // Исключаю элементы под диагональю обнулением элементов в столбце k
            double factor = A[i][k];
            if (std::fabs(factor) < EPS) {
                A[i][k] = 0.0; // Если близко к нулю, то лучше к нему и приравнять
                continue;
            }
            for (std::size_t j = k + 1; j < n; ++j) {
                A[i][j] -= factor * A[k][j];
            }
            rhs[i] -= factor * rhs[k];
            A[i][k] = 0.0;
        }
    }
    return true;
}

std::vector<double> backSubstUpper(const std::vector<std::vector<double>>& U, // Обратная подстановка для верхней треугольной матрицы U
    const std::vector<double>& rhsU) {
    int n = static_cast<int>(U.size());
    std::vector<double> xperm(n, 0.0);
    for (int ii = n - 1; ii >= 0; --ii) {
        double s = 0.0;
        for (int j = ii + 1; j < n; ++j) s += U[ii][j] * xperm[j];
        xperm[ii] = rhsU[ii] - s;
    }
    return xperm;
}

int main() {
    std::size_t n = 4;
    std::vector<std::vector<double>> A = {
        {7 * PI, 1, 2, 3},
        {0, 6 * PI, 3, 1},
        {2, 1, 4 * PI, 2},
        {3, 3, 3, 7 * PI}
    };
    std::vector<double> b = { 3, 5, 2, 3 };
    std::vector<std::vector<double>> A_orig = A;
    std::vector<double> b_orig = b;

    std::cout << "Original matrix A:" << std::endl;
    printMatrix(A_orig);

    std::cout << std::endl;

    std::cout << "Original vector b:" << std::endl;
    printVector(b_orig);

    std::cout << std::endl;

    std::cout << "After elimination (diagonal = 1):" << std::endl;
    printMatrix(A);

    std::cout << std::endl;

    std::cout << "Right-hand side after elimination:" << std::endl;
    printVector(b);

    std::vector<int> perm;
    forwardGaussColPivot(A, b, perm);
    std::vector<double> x_perm = backSubstUpper(A, b);

    std::vector<double> x(n, 0.0); // Восстановление решения в исходном порядке переменных:
    for (std::size_t k = 0; k < n; ++k) x[perm[k]] = x_perm[k];

    std::cout << std::endl;

    std::cout << "Column permutation (perm[k] = original index of variable in column k):" << std::endl;;
    for (std::size_t i = 0; i < n; ++i) {
        std::cout << perm[i] << (i + 1 == n ? "\n" : " ");
    }

    std::cout << std::endl;

    std::cout << "Solution x (in original variable order):" << std::endl;
    printVector(x);

    std::vector<double> Ax = matVecMultiply(A_orig, x); // Проверка
    std::vector<double> residual = vecSub(Ax, b_orig);
    double rnorm = euclideanNorm(residual);

    std::cout << std::endl;

    std::cout << "r = A*x - b:" << std::endl;;
    printVector(residual);

    std::cout << std::endl;

    std::cout << "Euclidean norm " << std::setprecision(12) << rnorm << std::endl;

    return 0;
}
