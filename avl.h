#ifndef AVL_H_
#define AVL_H_

#include"bst.h"

#define Balanced(x) (stature((x).lc)==stature((x).rc))
#define Balfac(x) (stature((x).lc))-stature((x).rc)
#define Avlbalanced(x) ((-2<Balfac(x))&&(Balfac(x)<2))

template<typename T>
class AVL:public bst<T>
{
    public:
        binnodeposi(T) insert(const T&e);
        bool remove(const T&e);
};

#define tallerchild(x)(
        stature((x)->lc)>stature((x)->rc)?(x)->lc:(
            stature((x)->lc)<stature((x)->rc)?(x)->rc:(
                islchild(*(x))?(x)->lc:(x)->rc
            )
        )
)

template<typename T>
binnodeposi(T) AVL<T>::insert(const T&e)
{
    binnodeposi(T) &x=search(e);
    if(x) return x;
    binnodeposi(T) xx=x=new binnode<T>(e,_hot);
    _size++;
    // same as bst
    // balance avl tree
    for(binnodeposi(T) g=_hot;g;g=g->parent)
    {
        if(!Avlbalaced(*g))
        {
            //fromparentto(*g)=rotateat(tallerchild(tallerchild(g)));// ???
            auto &p(fromparentto(*g));
            p=rotateat(tallerchild(tallerchild(g)));
            break;
        }else
            updateheight(g);
    }
    return xx;
}

template<typename T>
bool AVL<T>::remove(const T &e)
{
    binnoodeposi(T) &x=search(e);
    if(!x) return false ;
    removeat(x,_hot);
    _size--;
    for(binnodeposi(T) g=_hot;g;g=g->parent)
    {
        if(!Avlbalanced(*g))
        {   
            int height_1=g->height;
            g=fromparentto(*g)=rotateat(tallerchild(tallerchild(g)));
            if(height_1==g->height;)
                break;
        }// 失衡的根本原因是插入或删除操作导致  子树高度改变
        updateheight(g);
    }

    return true;
}

#endif