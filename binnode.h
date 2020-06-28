#ifndef BINNODE_H_
#define BINNODE_H_

#include"stack.h"

#define stature(p) ((p)?(p)->height:-1)
#define binnodeposi(T) binnode<T>*
typedef enum{ RB_RED,RB_BLACK} RBcolor;

template<typename T>
struct binnode
{
    T data;
    binnodeposi(T) parent;
    binnodeposi(T) lc;
    binnodeposi(T) rc;
    int height;
    RBcolor color;
    int npl;

    binnode():
        parent(NULL),data(),height(0),npl(1),color(RB_RED),lc(NULL),lr(NULL) {}
    binnode(T e,binnodeposi(T) parent=NULL,binnodeposi(T) lc=NULL,binnodeposi(T) rc=NULL,
            int h=0,int l=1,RBcolor c=RB_RED):
            data(e),parent(parent),lc(lc),lr(rc),height(h),npl(l),RBcolor(c) {}
    // gouzaohanshu

    //api:insert
    int size();
    binnodeposi(T) insertaslc(T const&);
    binnodeposi(T) insertasrc(T const &);
    binnodeposi(T) succ();

    // visit
    template<typename VST>  void    travlevel(VST&);
    template<typename VST>  void    travpre(VST&);
    template<typename VST>  void    travin(VST&);
    template<typename VST>  void    travpost(VST&);

    bool operator<(binnode const& bn)
    {
        return data<bn.data;
    }
    bool operator==(binnode const& bn)
    {
        return data==bn.data;
    }// comparison
};

template<typename T>
binnodeposi(T) binnode<T>::insertaslc(T const &e)
{
    return lc=new binnode(e,this);    
}


template<typename T>
binnodeposi(T) binnode<T>::insertasrc(T const &e)
{
    return rc=new binnode(e,this);    
}

template<typename T>
binnodeposi(T) binnode<T>::succ()
{
    return 
}

template<typename T,typename VST>
void travpre_R(binnodeposi(T) x,VST &visit)
{
    if(!x) return ;
    visit(x->data);
    travepre(x->lc,visit);
    travepre(x->rc,visit);
}

template<typename T,typename VST>
void travin_R(binnodeposi(T) x,VST& visit)
{
    if(!x) return ;
    travin_R(x->lc,visit);
    visit(x->data);
    travin_R(x->rc,visit);
}

template<typename T,typename VST>
void travpost_R(binnodeposi(T) x,VST& visit)
{
    if(!x) return ;
    travpost(x->lc,visit);
    travpost(x->rc,visit);
    visit(x->data);
}//wei ti gui

template<typename T, typename VST>
void travpre_i1(binnodeposi(T) x,VST& visit)
{
    stack<binnodeposi(T)> s;
    s.push(x);
    while(!s.empty())
    {
        x=s.pop();
        visit(x->data);
        if(hasrchild(*x)) s.push(x->rc);
        if(haslchile(*x)) s.push(x->lc);
    }
}//迭代方法的先序遍历 由尾递归转换而成

template<typename T,typename VST>
void travpre_i2(binnodeposi(T) x,VST& visit)
{
    stack<binnodeposi(T)> s;
    while(true)
    {
        visitalongleftbranch(x,visit,s);
        if(s.empty()) 
            break;
        x=s.pop();
    }
}// 迭代版的先序遍历 版本二

template<typename T,typename VST>
void visitalongleftbranch(binnodeposi(T) x,VST& visit,stack<binnodeposi(T)> &s)
{
    while(x)
    {
        visit(x->data);
        s.push(x->rc);
        x=x->lc;
    }
}// 先序遍历二

template<typename T,typename VST>
void travin_i1(binnodeposi(T) x,VST& visit)
{
    stack<binnodeposi(T)> s;
    while(true)
    {
        goalongleftbranch(x,s);
        if(s.empty()) 
            break;
        x=x.pop();
        visit(x->data);
        x=x->rc;
    }
}//  中序遍历版本一


template<typename T,typename VST>
void goalongleftbranch(binnodeposi(T) x,stack<binnodeposi(T)> &s)
{
    while(x)
    {
        s.push(x);
        x=x->lc;
    }
}// 版本一 深入函数

template<typename T,typename VST>
void travin_i2(binnodeposi(T) x,stack<binnodeposi(T)> &s)
{
    stack<binnodeposi(T)> s
    while(true)
    {
        if(x)
        {
            s.push(x);
            x=x->lc;
        }
        else if(!s.empty())
        {
            x=s.pop();
            visit(x->data);
            x=x->rc;
        }
        else break;
    }
}

template<typename T,typename VST>
binnodeposi(T) binnode::succ()
{
    binnodeposi(T) x=this;
    if(this->rc)
    {
        x=this->rc;
        while(haslchild(*x))
            x=x->lc;
    }
    else 
    {
        //if(isrchild(*x)) yi ding yao you hua cheng xu
            while(rchild(*x))
                x=x->parent;
        //if(islchild(*x))  ke sheng nue
            x=x->parent;
    }
    return s;
}

template<typename T,typename VST>
void travin_i3(binnodeposi(T) x)
{
    bool backtrack=false;
    while(true)
    {
        if(haslchild(*x)&&!backtrack)
            x=x->lc;
        else 
        {

            visit(x->data);
            if(hasrchild(*x))
            {
                x=x->rc;
                backtrack=false;
            }
            else 
            {
                if(!(x=x->succ)) 
                    break;
                backtrack=true;
            }
        }
    }
}
// finish the visit without using stack,cause only has a O(1) cost of space,
//that's absolutely fantastic

template<typename T,typename VST>
void travpost_i1(binnodeposi(T) x)
{
    stack<binnodeposi(T)> s;
    // bool backtrack=false;
    // while(true)
    // {
    //     if(backtrack)
    //         goalongleft(x,s);
    //     if(s.empty())
    //         break;
    //     x=x.pop();
    //     visit(x->data);
    //     if(!isrchild(*x)&&hasrchild(*(x->parent)))
    //     {
    //         x=x->rc;
    //         backtrack=true;
    //     }
    //     else 
    //     {
    //         x=x->parent;
    //         backtrack=false;
    //     }
    // } one case 
    s.push(x);
    while(!s.empty())
    {
        if(s.top()!=x->parent)
            goalontleft(s);
        x=s.pop();
        visit(x->data);
    }// miao a 
}

template<typename T,typename VST>
void goalongleft(binnodeposi(T) x,stack<binnodeposi(T)> &s) 
{
    while(true)
    {
        if(haslchild(*x))
        {
            if(hasrchild(*x))
                s.push(x->rc);
            s.push(x->lc);
            x=x->lc;
        }else if(hasrchild(*x))
        {  
            s.push(x->rc);
            x=x->rc;
        }
        else break;
    }   //case1

    while(binnodeposi(T) x=s.top())    
        if(haslchild(*x))
        {
            if(hasrchild(*x))
                s.push(x->rc);
            s.push(x->lc);
        }
        else s.push(x->rc);        
    s.pop(); //case 2
}

template<typename T,typename VST>
void binnode<T>::travlevel(binnodeposi(T) x)
{
    queue<binnodoposi(T)> q;
    q.enqueue(this);
    while(!q.empty())
    {
        x=q.dequeue();
        visit(x->data);
        if(haslchild(*x))
            q.enqueue(x->lc);
        if(hasrchild(*x))
            q.enqueue(x->rc);
    }
}
#endif