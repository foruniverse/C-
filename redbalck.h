#ifndef REDBLACK_H_
#define REDBLAXK_H_

#include"bst.h"
/*
    黑深度：
        从根节点通往任一节点的沿途，经过黑节点的个数（除去根节点本身）
        根节点深度为0

    黑高度：从任一节点通往任一后代外部节点的黑节点个数（不包括外部节点）

        任一外部节点到根节点的沿途，黑节点个数相等
*/
#define isblack(p) (!(p)||(RB_BLACK==(p)->color))
#define isred(p) (!isblack(p))
#define blackheightupdated(x) 
        (stature((x).lc)==stature((x).rc))&&\
        ((x).height==(isred(&x)?stature((x).lc):stature((x).lc)+1))
// 原节点黑高度等于删除后 重新计算的黑高度，则红黑树平衡，不必进行双黑修正

template<typename T>
class redblack:public BST<T>
{
    protected:
        void solvedoublered(binnodeposi(T) x);
        void solvedoubleblack(binnodeposi(T) x);

        int updateheight(binnodeposi(T) x);
    public:
        binnodeposi(T) insert(const T&e);
        bool remove(const T&e);

};

template<typename T>
void redblack<T>::solvedoublered(binnodeposi(T) x)
{
    if(root(*x))    
    {
        x->RBcolor=RB_BLACK;
        _root->height++;
        return ;
    }// 黑高度加一
    binnodeposi(T) p=x->parent;
    binnodeposi(T) g=p->parent;
    binnodeposi(T) u=uncle(x);
    if(u->RBcolor==RB_BLACK)
    {
        if(islchild(*p)==isrchild(*x))
        {
            p->color=RB_BLACK;
        }else
            x->color=RB_BLACK;
        g->color=RB_RED;

        binnodeposi(T) gg=g->parent;
        binnodeposi(T) r=fromparentto(*g)=rotate(x);
        r->parent=gg;
        // 可以不判断g为左分支还是右分支
    }else
    {
        p->color=RB_BLACK;
        u->color=RB_BLACK;
        if(!isroot(g*))
            g->color=RB_RED;
        solvedoublered(g);
    }
}

template<typename T>
void redblack<T>::solvedoubleblack(binnodeposi(T) r)
{
    binnodeposi(T) p=r?r->parent:_hot;// 用于替换的r 可能为空，那么便不能使用r->parent 为了方便理解，我们便保留了这一句
    if(!p) return ;
    binnodeposi(T) s=(r==p->lc?p->rc:p->lc); 

    if(isblack(s))
    {
        binnodeposi(T) t=NULL;
        if(isred(s->lc))    t=s->lc;
        if(isred(s->rc))    t=s->rc;
        if(t)
        {
            RBcolor oldcolor=p->color;
            binnodeposi(T) b=fromparentto(*p)=rotateat(t);
            //应对对称情况
            if(haslchild(*b)) { b->lc->color=RB_BLACK;updateheight(b->lc);}
            if(hasrchild(*b)) { b->rc->color=RB_BLACK;updateheight(b->rc);}//把b的子树全部置黑，即将t和p染成黑色
            b->color=oldcolor;
            updateheight(b);
        }else
        {
            s->color=RB_RED;
            s->height--;
            if(isred(p))
            {
                //s->color=RB_RED;
                p->color=RB_BLACK;
                //s->height--;
            }else
            {
                //s->color=RB_RED;
                //s->height--;
                p->height--;
                solvedoubleblack(p);
            }
            
        }
    }else
    {
        s->color=RB_BLACK;
        p->color=RB_RED;
        //if(islchild(*s)) binnodeposi(T) r=fromparentto(*p)=rotateat(s->lc);
        //else binnodeposi(T) r=fromparentto(*p)=rotateat(s->rc);
        binnodeposi(T) t=(islchild(*s)?s->lc:s->rc);
        fromparentto(*p)=rotateat(t);
        _hot=p;
        p->height--;
        s->height++;
        solvedoubleblack(r);
    }
    
}

template<typename T>
bool redblack<T>::remove(const T &e)
{// 排除退化情况
    binnodeposi(T) &x=search(e);
    if(!x) return false;

    binnodeposi(T) r=removeat(x,_hot);
    if(!(--_size)) return true;// 只有根节点的情况（空树）

    if(!_hot)
    {
        _root->color=RB_BLACK;
        updateheight(_root);
        return true;
    }// hot 是实际删除节点的父亲，hot为空，则删除的为根节点

    //以下，原（x）现r 不为根节点，

    if(blackheightupdated(*_hot)) return true;// 如果所有祖先的黑高度依然平衡，退出
    // 这条语句是不是只排除了  x为红了情况，因为只有这种情况下，x所在子树黑高度不会发生改变
    if(isred(r))// 第一种 r为红的情况
    {
        r->color=RB_BLACK;
        r->height++;
        return true;
    }
    // x为红的情况直接退化，不需任何修正
    solvedoublebalck(r);
    return true;
}

template<typename T>
int redblack<T>::updateheight(binnodeposi(T) x)
{
    x->height=max(stature(x->lc),stature(x->rc));
    return isblack(x)?x->height++:x->height;
}

template<typename T>
binnodeposi(T) insert(const T&e)
{
    binnodeposi(T) &x=search(e);
    if(x) return x;
    x=new binnode<T>(e,_hot,NULL,NULL,-1);
    _size++;
    solvedoublered(x);
    if(e>_hot->data)
}


#endif






