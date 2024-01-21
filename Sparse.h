#pragma once

#include "List.h"
#include <vector>
#include <cmath>

class Sparse {
private:
    size_t size;
    std::vector<std::unique_ptr<List>> rows;
    void clear();
public:
    Sparse() : size(0), rows() {};

    explicit Sparse(size_t n);

    void add(size_t row, size_t column, double value);

    void print();

    size_t get_size() const { return size; }

    Sparse(const Sparse &A);

    Sparse(Sparse &&A) noexcept(true);

    Sparse transpose() const;

    double norm() const;

    Sparse& operator =(const Sparse& A1);
    Sparse& operator =(Sparse&& A1) noexcept(true) ;
    friend Sparse operator+(const Sparse &A1, const Sparse &A2);
    friend Sparse operator-(const Sparse &A1, const Sparse &A2);
    friend Sparse operator*(double alpha, const Sparse &A);
    friend Sparse operator*(const Sparse &A, double alpha);
    Sparse& operator+=(const Sparse &A);
    Sparse& operator-=(const Sparse &A);
    Sparse& operator*=(double alpha);

    friend Sparse operator *(const Sparse &A1, const Sparse &A2);
    friend std::vector<double> operator *(const Sparse &A1,const std::vector<double>& b);
};

Sparse operator *(const std::vector<double>& a,const std::vector<double>& b);
