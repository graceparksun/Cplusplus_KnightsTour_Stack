#include "basestack.h"

baseStack::baseStack()
{
    stack = NULL;
}

baseStack::~baseStack()
{
    deleteStack();
}

bool baseStack::empty()
{
    return tos == -1;
}

bool baseStack::full()
{
    return tos + 1 == total;
}

void baseStack::clear()
{
    tos = -1;
}

int baseStack::size() const
{
    return tos + 1;
}

int baseStack::capacity() const
{
    return total;
}

void baseStack::increment()
{
    ++tos;
}

void baseStack::decrement()
{
    --tos;
}


int baseStack::topOfStack()
{
    return tos;
}

void baseStack::deleteStack()
{
    delete [] stack;
}

void baseStack::makeStack(int s)
{
   stack = new void*[total = s];
   tos = -1;
}
