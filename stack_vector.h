#ifndef STACK_VECTOR_H_
#define STACK_VECTOR_H_

#include"vector.h"

template<typename T>
class stack:public Vector<T>
{
    public:
        void push(const T&e)
        {
            this->insert(this->size(),e);
        }
        T pop()
        {
            return this->remove(this->size()-1);
        };
        T& top()
        {
            return this->_elem[this->size()-1];
        }
};

#endif