#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>
using namespace std;
typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T> class Vector
{
    protected:
        Rank _size;
        int _capacity;
        T* _elem;
        void expand();
        void shrink();
        void copyfrom(T const *A,Rank lo,Rank hi);
    
    public:
        Vector (int c=DEFAULT_CAPACITY,int s=0,T v=0)
        {
            _elem = new T[_capacity=c];
            for(_size=0;_size<s;_elem[_size++]=v);
        }
        Vector (T const* A,Rank n)
        {
            copyfrom (A,0,n);
        }
        Vector (T const* A,Rank lo,Rank hi)
        {
            copyfrom (A,lo,hi);
        }
        // xigou hanshu

        ~Vector() 
        {
            delete [] _elem;    
        }

        Rank size(){return _size;}
        T& operator[] ( Rank r) const;
        Rank insert ( Rank r, T const& e);
        int remove(Rank lo,Rank hi);
        T remove(Rank r);
        Rank find(T const &e) {return find(e,0,_size);}
        Rank find(T const & e, Rank lo,Rank hi);
        int deduplicate();
        int uniquify();
        void mergesort(Rank lo,Rank hi);
        void merge(Rank lo,Rank mi, Rank hi);
        bool empty();
};

template<typename T>
bool Vector<T>::empty()
{
    return !_size;
}

template<typename T>
void Vector<T>::expand()
{
    if(_size <_capacity) return;
    _capacity =max(_capacity,DEFAULT_CAPACITY);
    T* oldElem=_elem;
    _elem = new T[_capacity <<=1];
    for(int i=0;i< _size;i++)
    _elem[i]=oldElem[i];
    delete [] oldElem;
}

template<typename T>
void Vector<T>::shrink()
{
    if(_capacity<DEFAULT_CAPACITY<<1)
        return;
    if(_size<<2>DEFAULT_CAPACITY)
        return;// jie
    T*oldelem=_elem;
    _elem=new T[_capacity>>=1];
    for(int i=0;i<_size;i++)
        _elem[i]=oldelem[i];
    delete [] oldelem;
}

template<typename T>
T& Vector<T>::operator[](Rank r) 
const { return _elem[r];}

template<typename T>
Rank Vector<T>::insert(Rank r, T const& e)
{
    expand();
    for(int i=_size;i>r;i--)
        _elem[i]=_elem[i-1];
    _elem[r]=e;
    _size++;
    return r;
}

template<typename T>
int Vector<T>::remove(Rank lo,Rank hi)
{
    if(lo==_size)
    return 0;
    while(hi<_size)
        _elem[lo++]=_elem[hi++];
    _size=lo;
    shrink();
    return hi-lo;
}

template<typename T>
T Vector<T>::remove(Rank r)
{
    T e=_elem[r];
    remove(r,r+1);
    return e;
}

template<typename T>
Rank Vector<T>::find(const T&e,int lo,int hi)
{
    while((lo<hi--) && (e!=_elem[hi]));
    return hi;
}

template<typename T>
int Vector<T>::deduplicate()
{
    int oldsize=_size;
    Rank i=1;
    while(i<_size)
        (find(_elem[i],0,i)<0)?i++: remove(i);
    return oldsize-_size;
}

template<typename T>
int Vector<T>::uniquify()
{
    Rank i=0,j=0;
    while(++j<_size)
        if(_elem[i]!=_elem[j])
            _elem[++i]=_elem[j];
    _size=++i;
    shrink();
    return j-i;
}// high effictive algorithm

template<typename T>
void Vector<T>::mergesort(Rank lo,Rank hi)
{
    if(hi-lo<2) return;
    int mi=(lo+hi)>>1;
    mergesort(lo,mi);
    mergesort(mi,hi);
    merge(lo,mi,hi);
    
}

template<typename T>
void Vector<T>::merge(Rank lo,Rank mi,Rank hi)
{
    T* A=_elem+lo;
    T* B=new T[mi-lo];
    T* C=_elem+mi;
    int lb=mi-lo;
    int lc=hi-mi;
    for(int i=0;i<mi;B[i]=A[i++]);
    for(int i=0,j=0,k=0;j<lb;)
    {
        if(lc<=k||B[j]<=C[k]) A[i++]=B[j++];
        if(k<lc&&C[k]<B[j]) A[i++]=C[k++];
    }
    // for(int i=0,j=0,k=0;j<lb||k<lc;)
    // {
    //     if((j<lb)&&((B[j]<=C[k])||(lc<=k))) A[i++]=B[j++];
    //     if((k<lc)&&((c[k]<B[j])||lb<=j) )A[i++]=C[k++];
    // }
    delete [] B; 
}

#endif 