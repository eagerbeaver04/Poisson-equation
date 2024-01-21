#pragma once

#include <iostream>
#include <memory>
template<class T>
class Node
{
private:
	size_t column;
	T value;
	std::unique_ptr<Node<T>> next;
public:
	Node() : column(), value(), next(nullptr) {};
	Node(size_t column_, T value_) : column(column_), value(value_), next(nullptr) {};
	void set_next(std::unique_ptr<Node<T>> data) { next = std::move(data); };
	const Node<T>* get_next() const { return next.get(); }
	size_t get_column() { return column; }
    T get_value() { return value; }
	void print(size_t size)
	{
		Node<T>* tmp = this;
		size_t prev_column = -1;
		size_t current_column;
		while (tmp != nullptr)
		{
			current_column = tmp->column;
			for (int i = 0; i < static_cast<int>(current_column - prev_column - 1); i++)
				std::cout << T() << " ";
			std::cout << tmp->value << " ";
			tmp = tmp->next.get();
			prev_column = current_column;
		}
		for (size_t i = current_column; i < size-1; i++)
			std::cout << T() << " ";
	}
	void add(size_t column_, T data)
	{
		Node<T>* tmp = this;
		Node<T>* tmp_next = next.get();

		while (tmp_next != nullptr)
		{
			if (tmp->column <= column_ && tmp_next->column >= column_)
			{
				if (tmp->column == column_)
				{
					tmp->value += data;
					return;
				}
				if (tmp_next->column == column_)
				{
					tmp_next->value += data;
					return;
				}
				auto newNode = std::make_unique<Node<T>>(column_, data);
				newNode->next = std::move(tmp->next);
				tmp->next = std::move(newNode);
				return;
			}
			tmp = tmp->next.get();
			tmp_next = tmp->next.get();
		}
		auto newNode = std::make_unique<Node<T>>(column_, data);
		tmp->next = std::move(newNode);
	}
};