#ifndef BST_H_
#define BST_H_

#include"bintree.h"

template<typename K,typename V>
struct Entry
{
    K key;
    V value;
    Entry (K k=k(),V v=v()):key(k),value(v){};
    Entry (Entry<K,V> const&e):key(e.key),value(e.value) {};
    
    bool operator <(Entry<K,V> const &e) {return key<e.key;}
    bool operator >(Entry<K,V> const &e) {return key>e.key;}
    bool operator ==(Entry<K,V> const &e) {return key==e.key;}
    bool operator !=(Entry<K,V> const &e) {return key!=e.key;}
};


template<typename T>
class BST:public bintree<T>
{
    protected:
        binnodeposi(T) _hot;
        binnodepoi(T) connect34
        (
            binnodeposi(T), binnodeposi(T), binnodeposi(T),
            binnodeposi(T), binnodeposi(T), binnodeposi(T), binnodeposi(T),
        );
 
        binnodeposi(T) rotateat(binnodeposi (T) x);
    
    public:
        virtual binnodeposi(T) & search(const T&e);
        virtual binnodeposi(T) insert(const T&e);
        virtual bool remove (const T&e);
};

template<typename T>
static binnodeposi(T) &searchin(binnodeposi(T) &v,const T&e,binnodeposi(T) &hot)
{
    if(!v||v->data==e)
        return v;
    hot=v;
    // if(e>v->data)
    //     searchin(v->lc,e,hot);
    // else searchin(v->rc,e,hot)L    
    return  searchin((v->data>e?v->rc:v->lc),e,hot);
}

template<typename T>
binnodeposi(T) & BST::search(const T &e)
{
    return searchin(_root,e,_hot=NULL); 
}

template<typename T>
binnodeposi(T)insert(const T&e)
{
    binnodeposi(T) &x=search(e);  // 使用引用的目的是将x的地址与搜索到的匹配空地址匹配
    if(x) return x;
    _size++;
    x=new binnode<T>(e,_hot);// 引用在这里就可以将（lc，rc）指向分配的新的地址空间
    updateheightabove(x);
    return x;
}

template<typename T>
bool BST<T>::remove(const T &e)
{
    binnodeposi(T) &x=search(e);// 
    if(!x) return false;
    removeat(x,_hot);
    _size--;
    updateheightabove(_hot);
    return true;
}

template<typename T>
static binnnodeposi(T) removeat(binnodeposi(T) &x,binnodeposi(T) &hot)
{
    binnodeposi(T) w=x;// 奇妙妙，奇妙妙。指针真是奇妙
    binnoeposi(T) succ=NULL;    //代替删除节点的节点
    if(!haslchild(*x))
    {
        succ=x=x->rc;// 传递引用是为了修改x的地址
    }else if(!hasrchild(*x))
    {
        succ=x=x->lc;
    }else 
    {
        w=x->succ();// 后继
        swap(x->data,w->data);// 交换data，删除后继
        u=w->parent;
        ((u==x)?u->rc:u->lc)==succ=w->rc;
    }
    hot=w->parent;// 将hot指向  实际   被删除的节点（后继）
    if(succ)    succ->parent=hot;
    release(w->data);
    release(w);
    return succ;    
}


template<typename T>
binnodeposi(T) bst<T>::connect34
(binnodeposi(T) a,binnodeposi(T)b,binnodeposi(T) c,
binnodeposi(T) T0,binnodeposi(T) T1,binnodeposi(T) T2,binnodeposi(T) T3)
{
    a->lc=T0; if(T0) T0->parent =a;
    a->rc=T1; if(T1) T1->parent =a;updateheight(a);
    c->lc=T2; if(T2) T2->parent =c;
    c->rc=T3; if(T3) T3->parent =c;updateheight(c);

    b->lc=a; a->parent =b;
    b->rc=c; c->parent =b; updateheight(b);

    return b;// return root
}// 这是旋转的模板，通过变更接口来灵活的转换旋转的类型

template<typename T>
binnodeposi(T) bst<t>::rotateat(binnodeposiT(T) v)
{
    binnodeposi(T) p=v->parent;
    binnodeposi(T) g=p->parent;
    if(islchild(*p))
        if(islchild(*v))
        {
            p->parent=g->parent;
            return connect34(v,p,g,v->lc,v->rc,p->rc,g->rc);
        }else 
        {
            v->parent =g->parent;
            return connect34(p,v,g,p->lc,v->lc,v->rc,g->rc);
        }
    else    
        if(isrchild(*v))
        {
            p->parent=g->parent;
            return connect34(g,p,v,g->lc,p->lc,l->rc,v->lc);
        }else
        {
            v->parent=g->parent;
            return connect34(g,v,p,g->lc,v->lc,v->rc,p->rc)
        }
}

#endif