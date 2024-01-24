#pragma once
#include "PreconditionedConjugateGradientsMethod/PCG.h"
#include "Sparse.h"

Sparse five_diag(size_t n);

Sparse F(double A, double B, size_t N,
         const std::function<double(double, double)>& function,
         const std::function<double(double, double)>& accurate_solution);
std::vector<std::vector<double>> U(double A, double B, size_t N,
                                   const std::function<double(double, double)>& accurate_solution);

std::vector<std::vector<double>> reverse(const std::vector<double>& a);

std::vector<double> f(double A, double B, size_t N,
                      const std::function<double(double, double)>& function,
                      const std::function<double(double, double)>& accurate_solution);
std::vector<double> u(double A, double B, size_t N,
                      const std::function<double(double, double)>& accurate_solution);

std::vector<double> solve_poisson_equation_with_precondition(Sparse& matrix, Sparse& L0,
                                           double A, double B, size_t N,
                                           const std::vector<double>& x_0, double eps,
                                           const std::function<double(double, double)>& function,
                                           const std::function<double(double, double)>& accurate_solution);

std::vector<double> solve_poisson_equation(Sparse& matrix,double A, double B, size_t N,
                                           const std::vector<double>& x_0, double eps,
                                           const std::function<double(double, double)>& function,
                                           const std::function<double(double, double)>& accurate_solution);