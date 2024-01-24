#include "Sparse.h"
#include "PoissonEquation/PoissonEquation.h"

double function_example(double x, double y) {
    return -2 * sin(x) * cos(y);// example
}

double accurate_solution_example(double x, double y)//for values only on edge
{
    return sin(x) * cos(y);
}

int main() {
    size_t N = 25;
    Sparse S = five_diag(N);
    double A = 0;
    double B = M_PI / 10;
    std::vector<double> x_0(N * N, 0);
    x_0[0] = 1;
    double eps = 0.1;
    double droptol = 0.1;
    //S.print();
    Sparse L1 = S.chol();
    //L1.print();
    Sparse L2 = S.ichol();
    //L2.print();
    Sparse L3 = S.chol(droptol);
    std::vector<double> solver0, solver1, solver2, solver3;
    double mistake0, mistake1, mistake2, mistake3;
    std::vector<double> accurate = u(A, B, N, &accurate_solution_example);
    for (int i = 0; i < 8; i++) {
        solver0 = solve_poisson_equation(S, A, B, N, x_0, eps,
                                         &function_example, &accurate_solution_example);
        solver1 = solve_poisson_equation_with_precondition(S, L1, A, B, N, x_0, eps,
                                                           &function_example, &accurate_solution_example);
        solver2 = solve_poisson_equation_with_precondition(S, L2, A, B, N, x_0, eps,
                                                           &function_example, &accurate_solution_example);
        solver3 = solve_poisson_equation_with_precondition(S, L3, A, B, N, x_0, eps,
                                                           &function_example, &accurate_solution_example);

        mistake0 = norm(sub(accurate, solver0));
        mistake1 = norm(sub(accurate, solver1));
        mistake2 = norm(sub(accurate, solver2));
        mistake3 = norm(sub(accurate, solver3));
        std::cout << "i: " << i << ":" << mistake0 << ", " << mistake1 << ", " << mistake2 << ", " << mistake3
                  << std::endl;
        eps /= 10;
    }

    return 0;
}