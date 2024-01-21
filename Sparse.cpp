#include "Sparse.h"

Sparse::Sparse(size_t n) {
    size = n;
    for (size_t i = 0; i < n; i++)
        rows.emplace_back(std::make_unique<List>());
}

void Sparse::add(size_t row, size_t column, double value) {
    if (row > size || column > size)
        std::cerr << "Oversize!" << std::endl;
    rows[row]->add(column, value);
}

void Sparse::print() {
    for (size_t i = 0; i < size; i++)
        rows[i]->print(size);
}

Sparse::Sparse(const Sparse &A) {
    size = A.size;
    for (size_t i = 0; i < size; i++)
        rows.push_back(std::make_unique<List>(*A.rows[i]));
}

Sparse::Sparse(Sparse &&A) noexcept(true) {
    size = A.size;
    for (size_t i = 0; i < size; i++)
        rows.emplace_back(std::move(A.rows[i]));
}

Sparse Sparse::transpose() const
{
    Sparse new_sparse(size);
    for (int i = 0; i < size; i++)
    {
        for(auto it = rows[i]->begin(); it!=rows[i]->end(); it++)
            new_sparse.add((*it).get_column(), i, (*it).get_value());
    }
    return new_sparse;
}

Sparse operator+(const Sparse &A1, const Sparse &A2) {
    size_t size = A1.size;
    if (size != A2.size)
        std::cerr << "Different sizes" << std::endl;
    Sparse new_sparse(size);
    /*
     *
     */
}