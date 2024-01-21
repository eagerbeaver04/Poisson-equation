#include "Node.h"

void Iterator::next()
{
    ptr->get_next(*this);
}

void Iterator::print()
{
    if(ptr)
        ptr->print();
}
