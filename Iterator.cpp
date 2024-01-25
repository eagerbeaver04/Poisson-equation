#include "Node.h"

void Iterator::next() {
    ptr->get_next(*this);
}

void Iterator::print() {
    if (ptr)
        ptr->print();
}

void Iterator::reset_after_this() {
    ptr->reset_after_this();
}