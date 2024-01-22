#include "Node.h"

void Node::print_all(size_t size) {
    Node *tmp = this;
    size_t prev_column = -1;
    size_t current_column;
    while (tmp != nullptr) {
        current_column = tmp->column;
        for (int i = 0; i < static_cast<int>(current_column - prev_column - 1); i++)
            std::cout << double() << " ";
        std::cout << tmp->value << " ";
        tmp = tmp->next.get();
        prev_column = current_column;
    }
    for (size_t i = current_column; i < size - 1; i++)
        std::cout << double() << " ";
}

void Node::print() const
{
    std::cout << value << " ";
}

void Node::add(size_t column_, double data, Node*& tail) {
    Node *tmp = this;
    Node *tmp_next = next.get();
    if (column == 0 && column_ == 0)
        std::cout << "";
    while (tmp_next != nullptr) {
        if (tmp->column <= column_ && tmp_next->column >= column_) {
            if (tmp->column == column_) {
                tmp->value += data;
                return;
            }
            if (tmp_next->column == column_) {
                tmp_next->value += data;
                return;
            }
            auto newNode = std::make_unique<Node>(column_, data);
            tmp->next = std::move(newNode);
            return;
        }
        tmp = tmp->next.get();
        tmp_next = tmp->next.get();
    }
    if (column_ == column)
    {
        tmp->value += data;
        return;
    }
    auto newNode = std::make_unique<Node>(column_, data);
    tmp->next = std::move(newNode);
    tail = tmp->next.get();
}

void Node::get_next(Iterator &it)
{
    Node* tmp = nullptr;
    if(next)
        tmp = next.get();
    it.setValue(tmp);
}

Iterator Node::create_begin_iterator()
{
    return Iterator(this);
}

Iterator Node::create_rend_iterator()
{
    return Iterator(nullptr);
}

Iterator Node::create_end_iterator()
{
    auto node = this;
    while(node->next)
        node = node->next.get();
    return Iterator(node);
}

Node* Node::reset_after_this()
{
    next.reset();
    next = nullptr;
    return this;
}

Node* Iterator::reset_after_this()
{
    return ptr->reset_after_this();
}