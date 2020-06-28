#ifndef PQ_LEFTHEAP_H_
#define PQ_LEFTHEAP_H_

#include"PQ.h"
#include"bintree.h"

template<typename T>
class pq_leftheap:public PQ<T>, public bintree<T>
{
    public:
        pq_leftheap(){}
        pq_leftheap( T *E, int n)
        {
            for(int i=0;i<n;i++)
                insert(E[i]);
        }
        void insert(T);
        T getmax();
        T delmax();
}


template<typename T>
static binnodeposi(T) merge(binnodeposi(T) a, binnodeposi(T) b)
{
    if(!a) return b;
    if(!b) return a;

    if(a->data<b->data)   swap(a,b);

    a->rc=merge(a->rc,b)
    a->rc->parent=a;
    if(!a->lc||a->rc->npl>a->lc->npl)
        swap(a,b);
    a->npl=a->rc?a->rc+1:1;
    return a;
}

template<typename T>
void  pq_leftheap<T>::insert(T e)
{
    binnodeposi(T) H=new binnode<T> (e);
    _root=merge(H,_root);
    _root->parent=NULL;
    _size++;
}

template<typename T>
T pq_leftheap<T>::delmax()
{
    binnodeposi(T) H=_root;
    // if(H->rc) H->rc->parent=NULL;
    // if(H->lc) H->lc->parent=NULL;
    // no need
    _root=merge(H->lc,H->rc);
    _root->parent=NULL;
    T e=H->data;
    delete H;
    _size--;
    return e;
}

#endif