#pragma once
#include "PreconditionedConjugateGradientsMethod/PCG.h"
#include "Sparse.h"

double function(double x, double y);
double accurate_solution(double x, double y);//for values only on edge
Sparse five_diag(size_t n);

Sparse F(double A, double B, size_t N);
std::vector<std::vector<double>> U(double A, double B, size_t N);

std::vector<std::vector<double>> reverse(const std::vector<double>& a);

std::vector<double> f(double A, double B, size_t N);
std::vector<double> u(double A, double B, size_t N);
