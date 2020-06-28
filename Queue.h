#ifndef QUEUE_H_
#define QUEUE_H_
#include"list.h"

template<typename T>
class Queue:public list<T>
{
    public:
        void enqueue(const T&e)
        {
            this->insertasfirst(e);
        }

        T dequeue()
        {
            return this->remove(this->last());
        }

        T &front()
        {
            return this->last()->data;
        }

        // int &size()
        // const
        // {
        //     return this->size()
        // }
};

#endif