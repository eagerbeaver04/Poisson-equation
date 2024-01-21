#pragma once

#include "List.h"
#include <vector>

template<class T>
class Sparse
{
private:
	size_t size;
	std::vector<std::unique_ptr<List<T>>> rows;
public:
	Sparse() : size(0), rows({}) {};
	explicit Sparse(size_t n)
	{
		size = n;
		for (size_t i = 0; i < n; i++)
            rows.emplace_back(std::make_unique<List<T>>());
	}
	void add(size_t row, size_t column, T value)
	{
		if (row > size || column > size)
			std::cerr << "Oversize!" << std::endl;
		rows[row]->add(column, value);
	}
	void print()
	{
		for (size_t i = 0; i < size; i++)
			rows[i]->print(size);
	}
    size_t get_size()
    {
        return size;
    }
    Sparse(const Sparse& A)
    {
        size = A.size;
        for(size_t i =0;i < size; i++)
        {
            rows.emplace_back(std::make_unique<List<T>>());
            auto node = A.rows[i].get();
            while(node)
            {
                rows[i]->push_back(i, node->get_value());
                node = node->get_next();
            }
        }
    }
    Sparse(Sparse&& A) noexcept(true)
    {
        size = A.size;
        for(size_t i =0;i < size; i++)
            rows.emplace_back(std::move(A.rows[i]));
    }

    Sparse<T> transpose()
    {
        Sparse<T> new_sparse(size);
        for (int i = 0; i < size; i++)
        {
            auto node = rows[i].get();
            while (node)
            {
                new_sparse->add(node->column, i, node->value);
                node = node->next;
            }
        }
        return new_sparse;
    }

    friend  Sparse<T> operator + (const Sparse<T>& A1, const Sparse<T>& A2);
};

template<class T>
Sparse<T> operator + (const Sparse<T>& A1, const Sparse<T>& A2)
{
    size_t size = A1.n;
    if (size != A2.n)
        std::cerr << "Different sizes" << std::endl;
    Sparse<T> new_sparse(size);
    /*
     *
     */
}