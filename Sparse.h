#pragma once

#include "List.h"
#include <vector>

class Sparse {
private:
    size_t size;
    std::vector<std::unique_ptr<List>> rows;
public:
    Sparse() : size(0), rows() {};

    explicit Sparse(size_t n);

    void add(size_t row, size_t column, double value);

    void print();

    size_t get_size() const { return size; }

    Sparse(const Sparse &A);

    Sparse(Sparse &&A) noexcept(true);

    Sparse transpose() const;

    friend Sparse operator+(const Sparse &A1, const Sparse &A2);
};

