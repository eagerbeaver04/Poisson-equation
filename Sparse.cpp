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
        if (rows[i])
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

void Sparse::clear() {
    for (size_t i = 0; i < size; i++)
        rows[i].reset();
    rows.clear();
}

Sparse &Sparse::operator=(const Sparse &A) {
    clear();
    size = A.size;
    for (size_t i = 0; i < size; i++)
        rows.push_back(std::make_unique<List>(*A.rows[i]));
    return *this;
}

Sparse &Sparse::operator=(Sparse &&A) noexcept(true) {
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

Sparse &Sparse::operator+=(const Sparse &A) {
    if (size != A.size)
        std::cerr << "Different sizes" << std::endl;
    for (size_t i = 0; i < size; i++)
        for (auto it = A.rows[i]->begin(); it != A.rows[i]->end(); it++)
            add(i, (*it).get_column(), (*it).get_value());
    return *this;
}

Sparse &Sparse::operator-=(const Sparse &A) {
    if (size != A.size)
        std::cerr << "Different sizes" << std::endl;
    for (size_t i = 0; i < size; i++)
        for (auto it = A.rows[i]->begin(); it != A.rows[i]->end(); it++)
            add(i, (*it).get_column(), -1 * (*it).get_value());
    return *this;
}

Sparse &Sparse::operator*=(double alpha) {
    for (int i = 0; i < size; i++)
        for (auto it = rows[i]->begin(); it != rows[i]->end(); it++)
            (*it).get_value() *= alpha;
    return *this;
}

Sparse operator*(const Sparse &A1, const Sparse &A2) {
    size_t size = A1.size;
    if (size != A2.size)
        std::cerr << "Different size" << std::endl;
    auto new_sparse = Sparse(size);
    auto At = A2.transpose();
    double value;
    List *list1;
    List *list2;
    Iterator begin1, end1, begin2, it1, it2;
    for (size_t i = 0; i < size; i++) {
        list1 = A1.rows[i].get();
        begin1 = list1->begin();
        end1 = list1->end();
        for (size_t j = 0; j < size; j++) {
            value = 0;
            begin2 = At.rows[j]->begin();
            it1 = begin1;
            it2 = begin2;
            while (!it1.is_null() && !it2.is_null()) {
                while (it1 != end1 && (*it2).get_column() > (*it1).get_column())
                    it1++;
                if (!it1.is_null())
                    if (it1->get_column() == it2->get_column()) {
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

std::vector<double> operator*(const Sparse &A1, const std::vector<double> &b) {
    size_t size = b.size();
    if (size != A1.size)
        std::cerr << "Different size " << std::endl;
    std::vector<double> new_vec(size);
    double value;
    Iterator begin;
    Iterator end;
    for (size_t i = 0; i < size; i++)
    {
        value=0;
        begin = A1.rows[i]->begin();
        end = A1.rows[i]->end();
        for (auto it = begin; it != end; it++)
            value+= (*it).get_value() * b[(*it).get_column()];
        new_vec[i] = value;
    }
    return new_vec;
}

Sparse vec_mul(const std::vector<double>& a, const std::vector<double>& b)
{
    size_t size = a.size();
    if (size != b.size())
        std::cerr << "Different size " << std::endl;
    double value;
    Sparse new_sparse(size);
    for(size_t i=0; i < size; i ++)
    {
        value = a[i];
        for(size_t j =0; j < size; j++)
            new_sparse.add(i, j, value * b[j]);
    }
    return new_sparse;
}

double scalar_mul(const std::vector<double>& a, const std::vector<double>& b)
{
    double value=0;
    for(double i : a)
        for(double j : b)
            value+=i*j;
    return value;
}

double Sparse::norm() const
{
    Iterator begin, end, it;
    double norma=0;
    for(size_t i=0; i < size; i++)
    {
       begin = rows[i]->begin();
       end = rows[i]->end();
       for(it= begin; it!=end; it++)
            norma+= pow((*it).get_value(),2);
    }
    return sqrt(norma);
}

Sparse::Sparse(const std::vector<std::vector<double>>& A)
{
    size = A[0].size();
    for (size_t i = 0; i < size; i++)
        rows.push_back(std::make_unique<List>());
    for(size_t i =0; i < size; i++)
        for(size_t j=0; j < size; j++)
            if(A[i][j] !=0)
                add(i,j,A[i][j]);
}

/*
void Sparse::find_by_column(Iterator& begin, Iterator& end, Iterator& it, size_t column)
{
    for (it = begin; it != end; it++)
    {
        if (it->get_column() > column){
            it = end;
            return;
        }
        if (it->get_column() == column)
            return;
    }
}*/
