#pragma once

#include "List.h"
#include <vector>
#include <cmath>
#include <functional>

class Sparse {
private:
    size_t size;
    std::vector<std::unique_ptr<List>> rows;
    void clear();
    void find_by_column(Iterator& begin, Iterator& end, Iterator& it, size_t column);
public:
    Sparse() : size(0), rows() {};

    explicit Sparse(size_t n);

    void add(size_t row, size_t column, double value);

    void print();

    size_t get_size() const { return size; }

    Sparse(const Sparse &A);

    Sparse(Sparse &&A) noexcept(true);

    explicit Sparse(const std::vector<std::vector<double>>& A);

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

    Sparse chol();
    Sparse ichol();
    Sparse chol(double droptol);

    std::vector<double> gauss_down(const std::vector<double>& b);// for lower triangular matrix
    std::vector<double> gauss_up(const std::vector<double>& b);// for upper triangular matrix
    std::vector<double> convert_to_vector();
};

Sparse vec_mul(const std::vector<double>& a,const std::vector<double>& b);

