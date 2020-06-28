#ifndef BTNODE_H_
#define BTNODE_H_

#include"vector.h"

#define btnodeposi(T) BTNODE<T>*
template<typename T>
struct BTNODE
{
    btnodeposi(T) parent;
    Vector <T> key;
    Vector <btnodeposi(T)> child;

    BTNODE()
    {
        parent=NULL;
        child.insert(0,NULL);
    }
    BTNODE(T e,btnodeposi(T) lc=NULL, btnodeposi(T) rc=NULL)
    {
        parent =NULL;
        key.insert(0,e);
        child.insert(0,lc);
        child,insert(1,rc);
        if(lc) lc->parent=this;
        if(rc) rc->parent=this;
    }
};




#endif