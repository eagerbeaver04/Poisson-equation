#include "PoissonEquation.h"

Sparse F(double A, double B, size_t N,
         const std::function<double(double, double)> &function,
         const std::function<double(double, double)> &accurate_solution) {
    double h = (B - A) / (N + 1);
    Sparse new_sparse(N);
    double y, x;
    double value = 0;
    int k = 1;
    for (int i = 1; i < N + 1; i++) {
        x = A + i * h;
        for (int j = 1; j < N + 1; j++) {
            value = 0;
            y = A + j * h;
            value -= h * h * function(x, y);
            if (i == 1)
                value += accurate_solution(x - h, y);
            else if (i == N)
                value += accurate_solution(x + h, y);
            if (j == 1)
                value += accurate_solution(x, y - h);
            else if (j == N)
                value += accurate_solution(x, y + h);
            new_sparse.add(i - 1, j - 1, value);
        }
    }
    return new_sparse;
}

std::vector<std::vector<double>> U(double A, double B, size_t N,
                                   const std::function<double(double, double)> &accurate_solution)// for checking
{
    double h = (B - A) / (N + 1);
    std::vector<std::vector<double> > f(N, std::vector<double>(N));
    double y, x;
    int k = 1;
    for (int i = 1; i < N + 1; i++) {
        x = A + i * h;
        for (int j = 1; j < N + 1; j++) {
            y = A + j * h;
            f[i - 1][j - 1] = accurate_solution(x, y);
        }
    }
    return f;
}

Sparse five_diag(size_t N) {
    int size = pow(N, 2);
    Sparse S(size);
    for (int k = 0; k < size; k++) {
        S.add(k, k, 4);
        if (k < size - 1 && (k / N) == ((k + 1) / N)) {
            S.add(k, k + 1, -1);
            S.add(k + 1, k, -1);
        }
        if (k + N < size) {
            S.add(k, k + N, -1);
            S.add(k + N, k, -1);
        }
    }
    return S;
}

std::vector<std::vector<double>> reverse(const std::vector<double> &a) {
    size_t size = a.size();
    size_t n = sqrt(size);
    int k, j;
    std::vector<std::vector<double> > A(n, std::vector<double>(n));
    for (int i = 0; i < size; i++) {
        k = i / n;
        j = i % n;
        A[k][j] = a[i];
    }
    return A;
}

std::vector<double> f(double A, double B, size_t N,
                      const std::function<double(double, double)> &function,
                      const std::function<double(double, double)> &accurate_solution) {
    return F(A, B, N, function, accurate_solution).convert_to_vector();
}

std::vector<double> u(double A, double B, size_t N,
                      const std::function<double(double, double)> &accurate_solution) {
    size_t size = pow(N, 2);
    std::vector<double> vector_mat(size);
    std::vector<std::vector<double>> matrix = U(A, B, N, accurate_solution);
    int k = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            vector_mat[k] = matrix[i][j];
            k++;
        }
    }
    return vector_mat;
}

std::vector<double> solve_poisson_equation_with_precondition(Sparse &matrix, Sparse &L0,
                                                             double A, double B, size_t N,
                                                             const std::vector<double> &x_0, double eps,
                                                             const std::function<double(double, double)> &function,
                                                             const std::function<double(double,
                                                                                        double)> &accurate_solution) {
    return pcg_pred(matrix, f(A, B, N, function, accurate_solution),
                    x_0, eps, L0);
}

std::vector<double> solve_poisson_equation(Sparse &matrix, double A, double B, size_t N,
                                           const std::vector<double> &x_0, double eps,
                                           const std::function<double(double, double)> &function,
                                           const std::function<double(double, double)> &accurate_solution) {
    return pcg(matrix, f(A, B, N, function, accurate_solution),
               x_0, eps);
}