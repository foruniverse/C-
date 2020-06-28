#ifndef BINTREE_H_
#define BINTREE_H_

#include"binnode.h"
#define isroot(x) (!((x).parent))
#define islchild(x) (!isroot(x)&&(&(x)==(x).parent->lc));
#define isrchild(x) (!isroot(x)&&(&(x)==(x).parent->rc));
#define hasparent(x) (!isroot(x))
#define haslchild(x) ((x).lc)
#define hasrchild(x) ((x).rc)
#define haschild(x) ((x).lc||(x).rc)
#define hasbortherchild(x) (haslchild(x)&&hasrchild(x))
#define isleaf(x) (!haschild(x))
#define uncle(x) (islchild(*((x)->parent))?(x)->parent->parent->rc:(x)->parent->parent->lc)

#define sibling(p)
    (islchild(*(p))?hasrchild(p->parent):haslchild(p->parent))
#define fromparentto(x) 
    (isroot(x)?_root : (lslchild(x)?(x).parent->lc:(x).parent->rc)


template<typename T>
class bintree
{
    protected:
        int _size;
        binnodeposi(T) _root;
        virtual int updateheight (binnodeposi(T) x);
        void updateheightabove(binnodeposi(T) x);

    public:
        bintree():_size(0),_root(NULL) {}
        ~bintree() {}
        int size() const {return _size;}
        bool empty() const {return !_root;}

        binnodeposi(T) root() const {return _root; }
        binnodeposi(T) insertasroot(const T &e) ;
        binnodeposi(T) insertaslc(binnodeposi(T) p,const T&e);
        binnodeposi(T) insertasrc(binnodeposi(T) p,const T&e);
        binnodeposi(T) attachaslc(binnodeposi(T) p,bintree<T> * &s); 
        binnodeposi(T)  attachasrc(binnodeposi(T) p,bintree<T> * &s);

    
        int remove(binnodeposi(T) p);// 删除p和p的所有后代，并非只删除p
        bintree<T> * secde(binnodeposi(T) ); //delete child tree


        template<typename VST>
        void travlevel (VST& visit)
        {
            if(_root) 
                _root->travlevel(visit);
        }

        
        template<typename VST>
        void travpre (VST& visit)
        {
            if(_root) 
                _root->travpre(visit);
        }
        
        template<typename VST>
        void travin (VST& visit)
        {
            if(_root) 
                _root->travin(visit);
        }
        
        template<typename VST>
        void travpost (VST& visit)
        {
            if(_root) 
                _root->travpost(visit);
        }
};

template<typename T>
int bintree<T>::remove(binnodeposi(T) x)
{
    fromparentto(*x)=NULL;
    updateheightabove(x->parent);
    int n=removeat(x);
    _size-=n;
    return n;
}

template<typename T>
static int removeat(binnodeposi(T) x)
{
    if(!x)  return 0;
    int n=1+removeat(x->lc)+removeat(x->rc);
    release(x->data);
    release(x);
    return n;
}


template<typename T>
binnodeposi(T) insertaslc(binnodeposi(T) x,const T & e)
{
    _size++;
    x->insertsaslc(e);
    updateheightabove(x);
    return x->lc;
}


template<typename T>
binnodeposi(T) insertasrc(binnodeposi(T) x,const T & e)
{
    _size++;
    x->insertsasrc(e);
    updateheightabove(x);
    return x->rc;
}

template<typename T>
void bintree<T>::updateheightabove(binnodeposi(T) x)
{
    while(x)
    {
        updateheight(x);
        x=x->parent;
    }
}

template<typename T>
int bintree<T>::updateheight(binnodeposi(T) x)
{
    return x->height=1+max(x->lc->height,x->rc->height);
    // return x->height=1+max(stature(x->lc),stature(x->rc));
}

template<typename T>
binnodeposi(T) bintree<T>::attachaslc(binnodeposi(T) x,bintree<T>* &s)
{
    if(x->lc=s->_root)
        x->lc->parent=x;
    this->_size+=s->_size;
    updataheightabove(x);//attach tree
    //now delete s(tree)
    s->_root=NULL;
    s->_size=0;
sssssss    release(s);// zhanshi bulijie
    s=NULL;//并非删除s，我们可以认为我们只是 消除了通过s 访问s子树的你权限
    return x;
}

template<typename T>
binnodeposi(T) bintree<T>::attachasrc(binnodeposi(T) x,bintree<T> * &s)
{
    if(x->rc=s->_root)
        x->rc->parent=x;
    this->_size+=s->_size;
    updataheightabove(x);//attach tree
    //now delete s(tree)
    s->_root=NULL;
    s->_size=0;
    release(s);// zhanshi bulijie
    s=NULL;//并非删除s，我们可以认为我们只是 消除了通过s 访问s子树的你权限
    return x;
}

template<typename T>
bintree<T> * bintree<T>::secede(binnodeposi(T) x)
{
    fromparentto(*x)=NULL;
    updateheightabove(x->parent);
    bintree<T> *s=new bintree<T>;
    s->root=x;
    x->parent=NULL;
    s->_size=x->size();
    this->_size-=s->_size;
    return s;
}


#endif