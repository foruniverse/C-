#ifndef STACK_H_
#define STACK_H_

#include"list.h"

template<typename T>
class stack:public list<T>
{
    public:
       
        void push(const T&e)
        {
            this->insertaslast(e);
        }
        T pop()
        {
            return this->remove(this->last());
        }
        T &top()
        {
            return this->last()->data; 
        }
};
#endif
// c++模板类是很特殊的情况 应该进行 two-phase name lookup
// 找不到基类的成员函数，所以 只能加this指针
// 另外模板类 因为并不确定所储存的数据类型，只有在调用时确定了所给类型，才会开始编译
