#pragma once

#include "Node.h"

template<class T>
class List
{
private:
	std::unique_ptr<Node<T>> head;
	Node<T>* tail;
public:
	List() : head(nullptr), tail(nullptr) {};
	void push_back(size_t column, T data)
	{
		auto tmp = std::make_unique<Node<T>>(column, data);
		if (head)
		{
			tail->set_next(std::move(tmp));
			tail = const_cast<Node<T>*>(tail->get_next()); 
		}
		else
		{
			head = std::move(tmp);
			tail = head.get();
		}
	}
	void print(size_t size)
	{
		if (head)
			head->print(size);
		else
			for (size_t i = 0; i < size; i++)
				std::cout << T() << " ";
		std::cout << std::endl;
	}
	void add(size_t column, T data)
	{
		if (!head)
		{
			auto newNode = std::make_unique<Node<T>>(column, data);
			head = std::move(newNode);
			tail = head.get();
		}
		else if (head->get_column() > column)
		{
			auto newNode = std::make_unique<Node<T>>(column, data);
			newNode->set_next(std::move(head));
			head = std::move(newNode);
		}
		else
			head->add(column, data);
	}
	/*T& operator [](size_t idx) 
	{
		
	}

	T operator [](size_t idx) const 
	{
		
	}*/
};
