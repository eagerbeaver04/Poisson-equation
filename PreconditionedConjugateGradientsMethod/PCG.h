#pragma once
#include "Sparse.h"
std::vector<double> pcg(const Sparse& A,const std::vector<double>& b,
                             const std::vector<double>& x_0, double epsilon);
