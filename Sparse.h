#pragma once

#include "List.h"
#include <vector>

class Sparse
{
private:
	size_t size;
	std::vector<std::unique_ptr<List>> rows;
public:
	Sparse() : size(0), rows() {};
	explicit Sparse(size_t n)
	{
		size = n;
		for (size_t i = 0; i < n; i++)
            rows.emplace_back(std::make_unique<List>());
	}
	void add(size_t row, size_t column, double value)
	{
		if (row > size || column > size)
			std::cerr << "Oversize!" << std::endl;
		rows[row]->add(column, value);
	}
    void add_node(Node* node, size_t row)
    {
        if (row > size || node->get_column() > size)
            std::cerr << "Oversize!" << std::endl;
        rows[row]->add(node->get_column(), node->get_value());
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
            rows.push_back(std::make_unique<List>(*A.rows[i]));
    }
    Sparse(Sparse&& A) noexcept(true)
    {
        size = A.size;
        for(size_t i =0;i < size; i++)
            rows.emplace_back(std::move(A.rows[i]));
    }

    /*Sparse transpose()
    {
        Sparse new_sparse(size);
        for (int i = 0; i < size; i++)
        {
            
        }
        return new_sparse;
    }*/

    friend Sparse operator + (const Sparse& A1, const Sparse& A2);
};

Sparse operator + (const Sparse& A1, const Sparse& A2)
{
    size_t size = A1.size;
    if (size != A2.size)
        std::cerr << "Different sizes" << std::endl;
    Sparse new_sparse(size);
    /*
     *
     */
}