#ifndef BASESTACK_H
#define BASESTACK_H

#include <iostream>
#include <cstdlib>

using namespace std;

class baseStack
{
    public:
        baseStack();
        ~baseStack();

        bool empty();
        bool full();
        void clear();
        virtual void resize(int x) = 0;
        int size() const;
        int capacity() const;

    protected:
        void **stack;

        virtual void nukem() = 0;
        virtual void newStack(int s) = 0;

        void increment();
        void decrement();
        int topOfStack();
        void makeStack(int s);
        void deleteStack();

    private:
        int tos, total;
};

#endif // BASESTACK_H
