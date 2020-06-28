#ifndef BTREE_H_
#define BTREE_H_

#include"btnode.h"
#include"vector.h"

template<typename T>
class BTREE
{
    protected:
        int _size;
        btnodeposi(T) _root;
        btnodeposi(T) _hot;
        int _order;
        void solveoverflow(btnodeposi(T) );
        void solveunderflow(btnodeposi(T));

    public:
        BTREE(int order=3):_order(order),_size(0)
        {
            _root=new BTNODE<T>();
        }
        ~BTREE()
        {
            if(_root)
                release(_root);
        }

        int const order()
        {
            return _order;
        }
        int const size() {return _size;}

        btnodeposi(T) & root() {return _root;}
        bool empty() {return !_root};
        btnodeposi(T) search(const T&e);
        bool insert(const T&e);
        bool remove (const T&e);
};

template<typename T>
void BTREE<T>::solveoverflow(btnodeposi(T) v)
{
    if(_order>=v.key.size())    return;
    Rank s=_order/2;
    btnodeposi(T) u=new BTNODE<T>();
    for(Rank j=0;j<_order-s-1;j++)
    {
        u->key.insert(j,v->key.remove(s+1));
        u->child.insert(j,v->child.remove(s+1));
        // 对于child 提升了s后，引用数量并不变,同时对于s+1，考虑其逻辑结构的对应关系
    }//将v的s后半部分截去（长度为  order-s-1 ，s为前一部分，1为将要提升的s）
    u->child.insert(order-s-1,v->child.remove(s+1));
    // 会掉下child的最后一位
    if(u->child[0])
        for(Rank j=0;j<_order-s;j++)
            u->child[j]->parent=u;
    btnodeposi(T) p=v->parent;
    if(!p)
    {
        p=_root=new BTNODE<T>();
        p->child[0]=v;
        v->parent=p;
    }
    Rank r=p->key.search(v->key.remove(s))+1;
    p->child.insert(r+1,,u);
    u->parent=p;
    solveoverflow(p);
}


template<typename T>
void BTREE<T>::solveunderflow(btnodeposi(T) v)
{
    if((_order+1)/2-1<=v->key.size()) return ;
    btnodeposi(T) p=v->parent;
    if(!p)
    {
        if(!v->key.size()&&v->child[0])
        {
            _root=v->child[0];
            _root->parent=NULL;
            v->child[0]= NULL;
            release(v);
        }
        return;
    }
    Rank r=0;
    while(p->child[r]!=v)   r++;
    if(r>0)
    {
        btnodeposi(T) ls=p->child[r-1];
        if(ls->child.size()>(_order+1)/2)
        {
            v->key.insert(0,p->key[r-1]);
            p->key[r-1]=ls->key.remove(ls->key.size()-1);
            v->child.insert(0,ls->child.remove(ls->key.size()));
            
            if(v->child[0]) v->child[0]->parent=v;
            return;// 旋转操作不会产生任何下溢蔓延问题，所以处理完后可直接结束递归
        }
    }

    if(r<p->child.size()-1)
    {
        btnodeposi(T) rs=p->child[r+1];
        if(rs->child.size()>(_order+1)/2)
        {
            v->key.insert(v->key.size()-1,p->key[r]);
            p->key[r]=rs->key.remove(0);
            v->child.insert(v->child.size(),rs->child.remove(0));

            if(v->child[v->child.size()]) v->child[v->child.size()]->parent=v;
            return;
        }
    }

    if(0<r)
    {
        btnodeposi(T) ls=p->child[r-1];
        ls->key.insert(ls->key.size(),p->key.remove(r-1));
        //p->child[r]=NULL;
        p->child.remove(r);
        while(!v->key.empty())
        {
            ls->key.insert(ls->key.size(),v->key.remove(0));
            ls->child.insert(ls->child.size(),v->child.remove(0));
            if(ls->child[ls->child.size()])
                ls->child[ls->child.size()]->parent=ls;
        }
        ls->child.insert(ls->child.size(),v->child.remove(0));
        if(ls->child[ls->child.size()-1])
            ls->child[ls->child.size()-1]->parent=ls;
        release(v);
    }else
    {
        btnodeposi(T) rs=p->child[r+1];
        v->key.insert(v->key.size(),p->key.remove(r));
        p->child.remove(r+1);
        v->child.insert(v->child.size(),rs->child.remove(0));
        if(v->child[v->child.size()-1])
            v->child[v->child.size()-1]->parent=v;
        while(!rs->key.empty())
        {
            v->key.insert(v->key.size(),rs->key.remove(0));
            v->child.insert(v->child.size(),rs->child.remove(0));
            if(v->child[v->child->size()-1])
                v->child[v->child->size()-1]->parent=v;
        }
        release(rs);
    }
    solveunderflow(p);
    return ;//有什么必要？
}

template<typename T>
bool BTREE<T>::remove(const T &e)
{
    btnodeposi(T) v=search(e);
    if(!v) return false;
    Rank r=v->key.search(e);
    if(v->child[0])
    {
        btnodeposi(T) u=v->child[r+1];
        while(u->child[0])
            u=u->child[0];
        v->key[r]=u->key[0];
        v=u;r=0;
    }
    v->key.remove(r);
    v->child.remove(r+1);
    _size--;
    solveunderflow(v);
    return true;
}


template<typename T>
btnodeposi(T) BTREE<T>::search(const T&e)
{
    // if(!_root) return NULL;
    _hot=NULL;
    btnodeposi(T) v=_root;
    while(v)
    {
        Rank r=v->key.search(e);
        if((0<=r)&&(e==v->key[r]))
            return v;
        _hot=v;
        v=v->child[r+1];    
    }

    return NULL;
}

template<typename T>
bool BTREE<T>::insert(const T&e)
{
    btnodeposi(T) v=search(e);
    if(v) return false;
    Rank r=_hot->key.search(e);
    _hot->key.insert(r+1,e);
    _hot->child.insert(r+2,NULL);
    // // _hot->child.insert(_hot->child.size()-1,NULL);
    // //实际上需要我们插入的情况必定是 hot 节点位于叶节点，而插入的节点位于外节点，
    // // 而外节点 在这里全为NULL，对每个节点，事实上我们将key 和 child 交错排列
    // //  那么我们插入一个NULL 应该也是等效于直接在向量末尾直接插入一个null指针
    _size++;
    solveoverflow(_hot);
    return true;
}



#endif