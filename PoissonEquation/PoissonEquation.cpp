#include "PoissonEquation.h"

double function(double x, double y)
{
    return -2 * sin(x) * cos(y);// example
}

double accurate_solution(double x, double y)
{
    return sin(x) * cos(y);
}

Sparse F(double A, double B, size_t N)
{
    double h = (B - A) / (N+1) ;
    Sparse new_sparse(N);
    double y, x; double value=0;
    int k = 1;
    for (int i = 1; i < N+1; i++)
    {
        x = A + i * h;
        for (int j = 1; j < N+1; j++)
        {
            value = 0;
            y = A + j * h;
            value-= h*h*function(x, y);
            if (i == 1)
                value += accurate_solution(x - h, y );
            if (i == N)
                value += accurate_solution(x + h, y );
            if (j == 1)
                value += accurate_solution(x, y - h);
            if (j == N)
                value += accurate_solution(x , y + h);
            new_sparse.add(i-1, j -1, value);
        }
    }
    return new_sparse;
}

std::vector<std::vector<double>> U(double A, double B, size_t N)// for checking
{
    double h = (B - A) / (N + 1);
    std::vector < std::vector<double> > f(N, std::vector <double>(N));
    double y, x;
    int k = 1;
    for (int i = 1; i < N + 1; i++)
    {
        x = A + i * h;
        for (int j = 1; j < N + 1; j++)
        {
            y = A + j * h;
            f[i - 1][j - 1] = accurate_solution(x, y);
        }
    }
    return f;
}

Sparse five_diag(size_t N)
{
    int size = pow(N, 2);
    Sparse S(size);
    for (int k = 0; k < size; k++)
    {
        S.add(k, k, 4);
        if (k < size - 1 && (k / N) == ((k+1) / N))
        {
            S.add(k, k + 1, -1);
            S.add(k + 1, k, -1);
        }
        if (k + N < size)
        {
            S.add(k, k + N, -1);
            S.add(k + N, k, -1);
        }
    }
    return S;
}