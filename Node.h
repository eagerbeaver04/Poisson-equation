#pragma once

#include <iostream>
#include <memory>
#include <functional>

class Node {
private:
    size_t column;
    double value;
    std::unique_ptr<Node> next;
public:
    Node() : column(), value(), next(nullptr) {};

    Node(size_t column_, double value_) :
            column(column_), value(value_), next(nullptr) {};

    void set_next(std::unique_ptr<Node> data) { next = std::move(data); };

    const Node *get_next() const { return next.get(); }

    size_t get_column() const { return column; }

    double get_value() const { return value; }

    void print(size_t size);

    void add(size_t column_, double data);
};

