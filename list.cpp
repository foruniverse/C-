#include<iostream>
#include"list.h"
using namespace std;



template<typename T>
listnodeposi(T) listnode<T>:insertaspred(T const&e);
{
    listnodeposi(T) x= new listnode(e,pred,this);
    pred->succ=x;
    pred=x;
    return x;
}

template<typename T>
listnodeposi(T) listnode<T>::insertassucc(T const&e)
{
    listnodeposi(T) x=new listnode(e,this,succ);
    succ->pred=x;
    succ=x;
    return x;
}



template<typename T> 
int list<T>::clear()
{
    int oldsize=_size;
    while(0<_size)
        remove(header->succ);
    return oldsize;
}//qing chu

template<typename T>
void list<T>::init()
{
    header=new listnode<T>;
    trailer=new listnode<T>;
    header->succ=trailer;
    header->pred=NULL;
    trailer->succ=NULL;
    trailer->pred=header;
    _size=0;
}//chu shi hua

template<typename T>
void list<T>::copynodes(listnodeposi(T) p,int n);
{
    init();
    while(n--)
    {
        insertaslast(p->data);
        p=p->succ;
    }
}// fu zhi



template<typename T>
listnodeposi(T) list<T>::insertaslast(T const&e)
{
    _size++;
    return trailer->insertaspred(e);
}
template<typename T>
listnodeposi(T) list<T>::insertasfirst(T const&e)
{
    _size++;
    return header->insertassucc(e);
}
template<typename T>
listnodeposi(T) list<T>::inserta(listnodeposi(T) p,const&e)
{
    _size++;
    return p->insertassucc(e);
}
template<typename T>
listnodeposi(T) list<T>::insertb(listnodeposi(T) p,const&e)
{
    _size++;
    return p->insertaspred(e);
}

template<typename T>
void list<T>::reverse1()
{
    listnodeposi(T) p=header;
    listnodeposi(T) q=trailer;
    for(int i=1;i<_size;i+=2)//?????
        swap((p->succ)->data,(q->pred)->data);
}//交换首尾两端节点的data；

template<typename T>
void list<T>::reverse2()
{
    if(_size<2) return;
    listnodeposi(T) p;
    listnodeposi(T) q;
    for(p=header,q=p->succ;p!=trailer;p=q,q=p->succ)
        p->pred=q;
    trailer->pred=NULL;
    for(p=header,q=p->pred;p!=trailer;p=q,q=p->pred)
        q->succ=p;
    header->succ=NULL;
    swap(header,trailer);
}// 交换每个节点的前驱后继

template<typename T>
void list<T>::reverse3()
{
    if(_size<2) return;
    for(listnodeposi(T) p=header;p;p=p->pred)
        swap(p->pred,p->succ);
    swap(header,trailer);
}

template<typename T>
T list<T>::remove(listnodeposi(T) p)
{
    T e=p->data;
    p->succ->pred=p->pred;
    p->pred->succ=p->succ;
    delete p;
    _size--;
    return e;
}//删除节点p 并返回节点值

template<typename T>
listnodeposi(T) list<T>::find(T const&e,int n,listnodeposi(T) p)
{//无序列表查找 从后向前遍历 返回最大值或null
    while(0<n--)
        if(e==(p=p->pred)->data)
            return p;
    return NULL;
}

template<typename T>
listnodeposi(T) list<T>::search(T const&e,int n,listnodeposi(T) p)
{//有序列表查找。返回rank最大值 或header（查找失败）在其前驱中查找，不包括p
    do
    {
        p=p->pred;
        n--;
    } while ((-1<n)&&(e<p->data));
    return p;
}

template<typename T>
void list<T>::selectionsort(listnodeposi(T) p,int n)
{//起始于位置p的n个节点的排序
    listnodeposi(T) head=p->pred;
    listnodeposi(T) tail=p;
    for(int i=0;i<n;i++)
        tail=tail->succ;
    while(1<n)
    {
        listnodeposi(T) max=selectmax(head->succ,n);
        insertb(tail,remove(max));
        tail=tail->pred;
        n--;
    }
}//time cost shoule be Om(n*N),but we cut down the times of comparision from n to 1,that would absolutely be effective 
template<typename T>
listnodeposi(T) list<T>::selectmax(listnodeposi(T) p,int n)
{
    listnodeposi(T) max=p;
    for(listnodeposi(T) cur=p;1<n;n--)
        if(!lt((cur=cur->succ)->data,max->data))
            max=cur;
    return max;
}//O(n);

template<typename T>
int list<T>::deduplicate()
{
    int oldsize=_size;
    listnodeposi(T) p=first();
    listnodeposi(T) q=NULL:
    for(rank r=0;p!=trailer;p=p->succ,q=find(p->data,r,p))
        q?remove(q):r++;
    return oldsize-_size;

    // rank r=0;
    // while(p!=trailer)
    // {
    //     q?remove(q):r++;
    //     p=p->succ;
    //     q=find(p->data,r,p);
    // }
}// the worst time cost would be O(N*N);  

template<typename T>
int list<T>::uniquify()
{
    int oldsize=_size;
    listnodeposi(T) p=first();
    listnodeposi(T) q=p->succ;
    while(trailer!=(p->succ))
    {
        if(p->data==q->data)
            remove(q);
        else 
            p=q;
    }
    return oldsize-_size;
}// only need to visit the list  once
    //thus the time cost would be O(n);
template<typename T>
void list<T>::insertionsort(listnodeposi(T) p,int n)
{
    for(int r=0;r<n;r++)
    {
        inserta(search(p->data,r,p),p->data);
        p=p->succ;
        remove(p->pred);
    }
}// we should consider the worst situation which means that
//  every time if we try to find a listnode whose data is more
//  relevent to target, we may assume that every listnode before p could be
//  the result we want ,so we must do a r times-find,
// thus the O(n*n) can be concluded;

template<typename T>
template<typename VST>
void list<T>::traverse(VST &visit)
{
    for(listnodeposi(T) p=header->succ;p!=trailer;p=p->succ)
        visit(p->data);
}

