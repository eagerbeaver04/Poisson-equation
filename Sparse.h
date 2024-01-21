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
			rows.push_back(std::move(std::make_unique<List<T>>()));
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
};