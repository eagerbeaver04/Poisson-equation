#pragma once

#include "Node.h"

class List {
private:
    std::unique_ptr<Node> head;
    Node *tail;
public:
    List() : head(nullptr), tail(nullptr) {};

    List(const List &A);

    List(List &&A) noexcept(true);

    void push_back(size_t column, double data);

    void print(size_t size);

    void add(size_t column, double data);

    Iterator begin() { return Iterator(head.get()); }

    Iterator rend() { return Iterator(nullptr); }

    Iterator end() { return Iterator(tail); }
};
