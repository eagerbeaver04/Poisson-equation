#pragma once
#include "Sparse.h"
#include "Matrix.h"
vector pcg(const Sparse& A,const vector& b,
                             const vector& x_0, double epsilon);

vector pcg_pred(const Sparse& A,const vector& b,
                        const vector& x_0, double epsilon);