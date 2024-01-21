#include "List.h"

List::List(const List &A) {
    auto node = A.head.get();
    tail = node;
    while (node) {
        push_back(node->get_column(), node->get_value());
        node = const_cast<Node *>(node->get_next());
    }
}

List::List(List &&A) noexcept(true) {
    head = std::move(A.head);
    tail = A.tail;
}

void List::push_back(size_t column, double data) {
    auto tmp = std::make_unique<Node>(column, data);
    if (head) {
        tail->set_next(std::move(tmp));
        tail = const_cast<Node *>(tail->get_next());
    } else {
        head = std::move(tmp);
        tail = head.get();
    }
}

void List::print(size_t size) {
    if (head)
        head->print_all(size);
    else
        for (size_t i = 0; i < size; i++)
            std::cout << double() << " ";
    std::cout << std::endl;
}

void List::add(size_t column, double data) {
    if (!head) {
        auto newNode = std::make_unique<Node>(column, data);
        head = std::move(newNode);
        tail = head.get();
    } else if (head->get_column() > column) {
        auto newNode = std::make_unique<Node>(column, data);
        newNode->set_next(std::move(head));
        head = std::move(newNode);
    } else
        head->add(column, data, tail);
}
