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
        if(rows[i])
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

Sparse Sparse::transpose() const {
    Sparse new_sparse(size);
    for (int i = 0; i < size; i++)
        for (auto it = rows[i]->begin(); it != rows[i]->end(); it++)
            new_sparse.add((*it).get_column(), i, (*it).get_value());
    return new_sparse;
}

void Sparse::clear()
{
    for(size_t i =0; i <size;i++)
        rows[i].reset();
    rows.clear();
}

Sparse& Sparse::operator =(const Sparse& A)
{
    clear();
    size = A.size;
    for (size_t i = 0; i < size; i++)
        rows.push_back(std::make_unique<List>(*A.rows[i]));
    return *this;
}

Sparse& Sparse::operator =(Sparse&& A) noexcept(true) {
    clear();
    size = A.size;
    for (size_t i = 0; i < size; i++)
        rows.emplace_back(std::move(A.rows[i]));
    return *this;
}

Sparse operator+(const Sparse &A1, const Sparse &A2) {
    size_t size = A1.size;
    if (size != A2.size)
        std::cerr << "Different sizes" << std::endl;
    Sparse new_sparse(A1);
    for (size_t i = 0; i < size; i++)
        for (auto it = A2.rows[i]->begin(); it != A2.rows[i]->end(); it++)
            new_sparse.add(i, (*it).get_column(), (*it).get_value());
    return new_sparse;
}

Sparse operator-(const Sparse &A1, const Sparse &A2) {
    size_t size = A1.size;
    if (size != A2.size)
        std::cerr << "Different sizes" << std::endl;
    Sparse new_sparse(A1);
    for (size_t i = 0; i < size; i++)
        for (auto it = A2.rows[i]->begin(); it != A2.rows[i]->end(); it++)
            new_sparse.add(i, (*it).get_column(), -1 * (*it).get_value());
    return new_sparse;
}

Sparse operator*(double alpha, const Sparse &A2) {
    Sparse new_sparse(A2);
    for (int i = 0; i < new_sparse.size; i++)
        for (auto it = new_sparse.rows[i]->begin(); it != new_sparse.rows[i]->end(); it++)
            (*it).get_value() *= alpha;
    return new_sparse;
}

Sparse operator*(const Sparse &A1, double alpha) {
    return alpha * A1;
}

Sparse& Sparse::operator+=(const Sparse& A)
{
    if (size != A.size)
        std::cerr << "Different sizes" << std::endl;
    for (size_t i = 0; i < size; i++)
        for (auto it = A.rows[i]->begin(); it != A.rows[i]->end(); it++)
            add(i, (*it).get_column(), (*it).get_value());
    return *this;
}

Sparse& Sparse::operator-=(const Sparse& A)
{
    if (size != A.size)
        std::cerr << "Different sizes" << std::endl;
    for (size_t i = 0; i < size; i++)
        for (auto it = A.rows[i]->begin(); it != A.rows[i]->end(); it++)
            add(i, (*it).get_column(), -1 * (*it).get_value());
    return *this;
}

Sparse& Sparse::operator*=(double alpha)
{
    for (int i = 0; i < size; i++)
        for (auto it = rows[i]->begin(); it != rows[i]->end(); it++)
            (*it).get_value() *= alpha;
    return *this;
}

Sparse operator *(const Sparse &A1, const Sparse &A2)
{
    size_t size = A1.size;
    if (size != A2.size)
        std::cerr << "Different size" << std::endl;
    auto new_sparse = Sparse(size);
    auto At = A2.transpose();
    double value;
    List* list1;
    List* list2;
    for(size_t i =0; i < size; i++)
    {
        list1 = A1.rows[i].get();
        for(size_t j=0; j < size; j++)
        {
            value = 0;
            list2 = At.rows[j].get();
            auto it1 = list1->begin();
            auto it2 = list2->begin();
            while (!it1.is_null() && !it2.is_null())
            {
                while (it1 != list1->end() && (*it2).get_column() > (*it1).get_column())
                    it1++;
                if (!it1.is_null())
                    if (it1->get_column() == it2->get_column())
                    {
                        value += it1->get_value() * it2->get_value();
                        it1++;
                    }
                it2++;
            }
            if (value != 0)
                new_sparse.add(i, j, value);
        }
    }
    return new_sparse;
}