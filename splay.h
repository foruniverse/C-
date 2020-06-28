#ifndef SPLAY_H_
#define SPLAY_H_

#include"bst.h"

template<typename T>
class Splay:public BST<T>
{
    protected:

        binnodeposi(T) splay(binnodeposi(T) v);
    public:
        binnodeposi(T) &search(const T &e);
        binnodeposi(T) insert(const T &e);
        bool remove(const T&e);
};

template<typename nodeposi>inline
void attachaslchild(nodeposi p,nodeposi lc)
{
    p->lc=lc;
    if(lc) lc->parent=p;
}

template<typename nodeposi>
void attachasrchild(nodeposi p,nodeposi rc)
{
    p->rc=rc;
    if(rc) rc->parent=p;
}

template<typename T>
binnodeposi(T) Splay<T>::splay(binnodeposi(T) v)
{
    if(!v) return NULL;// 排除v为空的情况
    binnodeposi(T) p,g;

    while((p=v->parent)&&(g=p->parent)) // 判断p，v是否为空
    {
        binnodeposi(T) gg=g->parent;
        if(islchild(*p))
            if(islchild(*v))
            {
                attachaslchild(p,v->rc);
                attachasrchild(v,p);
                attachaslchild(g,p->rc);
                attachasrchild(p,g);
            }
            else
            {
                attachasrchild(p,v->lc);
                attachaslchild(v,p);
                attachasrchild(v,g);
                attachaslchild(g,v->rc);
            }
        else if(isrchild(*v))
            {
                attachasrchild(g,p->lc);
                attachaslchild(p,g);
                attachasrchild(p,v->lc);
                attachaslchild(v,p);
            }
            else
            {
                attachasrchild(g,v->lc);
                attachaslchild(v,g);
                attachaslchild(p,v->rc);
                attachasrchild(v,p);
            }
            // 连接旋转后的子树
            if(!gg) v->parent =NULL;// v 为根节点的情况
            else(g==gg->lc)?attachaslchild(gg,v):attachasrchild(gg,v);// 连接子树
            updateheight(p);
            updateheight(v);
            updateheight(g);// 更新高度（不要忘记）
    }
    if(p=v->parent) // 由于是每两层进行旋转，那么可分为余数为奇 偶的情况
    {
        if(islchild(*v))
        {
            attachaslchild(p,v->rc);
            attachasrchild(v,p);
        }else
        {
            attachasrchild(p,v->lc);
            attachaslchild(v,p);
        }   
        updateheight(p);
        updateheight(v);
    }
    v->parent=NULL;// v为根节点
    return v
}

template<typename T>
binnodeposi(T) & Splay<T>::search(const T&e)
{
    binnodeposi(T)&x=searchin(_root,e,_hot=NULL);
    _root=splay(p?p:_hot);
    return _root;
}

template<typename T>
binnodeposi(T) Splay<T>::insert(const T&e)
{
    if(!_root) 
    {
        _size++;
        return _root=new binnode<T>(e);
    }
    if(e==search(e)->data) return _root;
    // 排除退化情况
    _size++;

    binnodeposi(T) t=_root;
    if(e>t->data)
    {
        t->parent=_root=new binnode<T>(e,NULL,t,t->rc);// 编译器可能执行不同方向
        if(hasrchild(*t))
        {
            t->rc->parent=_root;
            t->rc=NULL;
        }// 对于指针我们只是更改其指向NULL 事实上原来我们指向的内容依然存在，
        // 只要不使用delete语句，它一直存在于内存区
    }else
    {
        t->parent=_root=new binnode<T>(e,NULL,t->lc,t);
        if(haslchild(*t))
        {
            t->lc->parent=_root;
            t->lc=NULL;
        }
    }
    //updateheight(_root); 不必，我们约定root节点的高度是0，另外，root的parent节点的高度为-1
    // 上文错误，root节点的高度，应该是所有节点的最深深度，而对于root节点的深度为0，parent深度为-1
    updateheightabove(t);// 更新t及其_root 的高度
    return _root;
}

template<typename T>
bool Splay<T>::remove(const T &e)
{
    
    if(!_root||e!=search(e)->data)
        return false;
    // 排除退化情况
    binnodeposi(T) w=_root;
    if(!haslchild(*_root))
    {
        _root=_root->rc;
        if(_root)
            _root->parent=NULL:
    }else if(!hasrchild(*_root))
    {
        _root=_root->lc;
        if(_root)
            _root->parent=NULL;
    }else
    {
        binnodeposi(T) ltree=_root->lc;
        ltree->parent=NULL;
        _root=_root->rc;
        root->parent=NULL;
        search(e);
        _root->lc=ltree;
        _root->lc->parent=_root;
    }
    release(w);
    releasse(w->data);
    _size--;
    if(_root)
    updateheight(_root);
    return true;
    
}

#endif