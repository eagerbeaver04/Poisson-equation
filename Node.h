#pragma once

#include <iostream>
#include <memory>
#include <functional>

class Iterator;

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

    double& get_value() { return value; }

    void print_all(size_t size);

    void print() const;

    void add(size_t column_, double data, Node*& tail);

    void get_next(Iterator& it);

    Iterator create_begin_iterator();

    Iterator create_end_iterator();

    Iterator create_rend_iterator();
};

class Iterator
{
private:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Node;
    using pointer = Node*;
    using reference = Node&;

    pointer ptr;
    // There are raw pointers because instance of Iterator class does not manage objects.
    //These pointers are needed only for enumaration.
    //Also these fields are private and this fact prohibit extern access.

    void next();
public:
    explicit Iterator(pointer ptr_) : ptr(ptr_) {};
    void setValue(Node* node) { ptr = node; };
    reference operator*() { return *ptr; };
    pointer operator ->() { return ptr; };
    Iterator& operator++ () { next(); return *this; };
    Iterator operator++(int i) { Iterator tmp = *this; ++(*this); return tmp; };
    friend bool operator == (const Iterator& a, const Iterator& b) { return (a.ptr == b.ptr); };
    friend bool operator != (const Iterator& a, const Iterator& b) { return (a.ptr != b.ptr); };
    bool is_null() {return ptr == nullptr;}
    void print();
};
