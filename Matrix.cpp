#include "Matrix.h"

void print(const vector& a)
{
    for(auto i : a)
        std::cout << i << " ";
    std::cout << "\n";
}

double scalar_mul(const vector& a, const vector& b)
{
    double value = 0;
    for (double i: a)
        for (double j: b)
            value += i * j;
    return value;
}

vector sum(const vector& a, const vector& b)
{
    size_t size = a.size();
    vector c(size, 0);
    if(size != b.size())
    {
        std::cerr << "Different size " << std::endl;
        return c;
    }
    for (size_t i = 0;i < size;i++)
        c[i] = a[i] + b[i];
    return c;
}

vector sub(const vector& a, const vector& b)
{
    size_t size = a.size();
    vector c(size, 0);
    if(size != b.size())
    {
        std::cerr << "Different size " << std::endl;
        return c;
    }
    for (size_t i = 0;i < size;i++)
        c[i] = a[i] - b[i];
    return c;
}

vector mul(const vector& a, double f)
{
    vector c(a);
    for (int i = 0; i < a.size();i++)
        c[i] *= f;
    return c;
}

vector mul(double f, const vector& a)
{
    return mul(a, f);
}