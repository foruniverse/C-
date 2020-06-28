#ifndef PQ_COMPLHEAP_H_
#define PQ_COMPLHEAP_H_


#include"vector"
#include"PQ.h"

#define lastInernal(n) ( parent(n-1))
#define parent(x) (((x)-1)>>1)
#define parentValid(x) (0<(x))
#define bigger(a,i,j) ((a[i]>a[j])?(i):(j))
#define biggest(a,n,i) (
    rChildValid(n,i)?bigger(a,rChild(i),bigger(a,i,lChild(i))):
    (lChildValid(n,i)?bigger(a,i,lChild(i)):i)
)



#define lChild(i)   ((i)<<1+1)
#define rChild(i)   ((1+(i))<<1)
#define lChildValid(n,i) (inHeap(n,lChild(i)))
#define rChildValid(n,i) (inHeap(n,rChild(i))) //基于堆的特殊特性 只要有右孩子，那么必定存在左孩子，即同时存在两个孩子
#define inHeap(n,i) ((-1<(i))&&((i)<n))



template<typename T>
class pq_complheap:public PQ<T>,public Vector<T>
{
    protected:
        Rank pecolatedown(Rank n,Rank i);
        Rank percolateUp(Rank i);
        void heapify(Rank n);
    public:
        pq_complheap() {}
        pq_complheap(T *A,Rank n) {
            copyform(A,0,n);
            heapify(n);
        }
        void insert(T);
        T getmax();
        T delmax();
};

template<typename T>
void pq_complheap<T>::insert(T e)
{
    this.insert(e);
    percolateUp(_size-1);
}


template<typename T>
Rank pq_complheap<T>::percolateUp(Rank i)
{
    // while(!parent(i))
    // {
    //     if(_elem[i]>_elem[parent(i)])
    //     {    swap(_elem[i],_elem[parent(i)]);
    //         i=parent(i);
    //     }else break;
    // }

    Rank j;
    T num=_elem[i];
    while(!j=parent(i))
    {
        if(_elem[i]>_elem[j])
        {
            _elem[i]=_elem[j];
            i=j;
        }else break;
    }
    return i;
}

template<typename T>
T pq_complheap<T>::getmax()
{
    return _elem;
}

template<typename T>
T pq_complheap<T>::delmax()
{
    T maxelem=_elem[0];
    _elem[0]=_elem[--_size];

    percolatedown(_size,0);
    return maxelem;
}


template<typename T>
Rank pq_complheap<T>::percolatedown(_size,i)
{
    Rank j;
    while(i!=(j=biggest(_elem,n,i)))
    {
        swap(_elem[i],_elem[j]);
        i=j;
    }

    return i;
}


template<typename T>
void pq_complheap<T>::heapify(Rank n)
{
    for(int i=lastinternal(n);inheap(n,i);i--)
    {
        percolateDown(n,i);
    }
}

template<typename T>
void Vector<T>::heapsort(Rank lo,Rank hi)
{
    pq_complheap<T> H (_elem+lo,hi-lo);
    while(!H.empty())
    {
        _elem[--hi]=H.dealmax();
    }
}

// 堆是一种数据结构，但它并没有多余的构造，从根本来说，它就是向量，只不过其逻辑结构按照 某种形式的二叉树来组织

#endif 