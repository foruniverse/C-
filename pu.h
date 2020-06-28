#ifndef PU_H_
#define PU_H_


#include "graph.h"
template<typname Tv,typename Te>// 最小支撑树
struct primpu
{
    void operator ()(graph<Tv,Te> * s,int uk,int v)
    {
        if(s->priority(v)==UNDISCOVERED)
            if(g->priority(v)>g->weight(uk,v))
            {
                g->priority(v)=g->weight(uk,v);// 对每一个优先级更新算法而言都是必须的
                //因为可能我们联通的顶点在 之前就已经被赋予了更低的优先级数（即更高的优先级）
                // 如果我们不进行判断。就会降低v的优先级（拨高优先级数）
                parent(v)=uk;
            }
    }
}


template<typename Tv,typename Te>
struct dijkstrapu
{
    virtual operator()(graph<Tv,Te> *g,int uk,int v)
    {
        if(g->status(v)==UNDISCOVERED) 
        {
            if(g->priority(v)>g->priority(uk)+g->weight(uk,v))
                g->priority(v)=g->priority+g->weight(uk,v);
                g->parent(v)=uk;
        }
    }
};

template<typename Tv,typename Te>
struct bfspu
{
    virtual operator()(graph<Tv,Te> *g,int uk,int v)
    {
        if(g->status(v)==UNDISCOVERED)
        {
            if(g->priority(v)>g->priority(uk)+1)
                g->priority(v)=g->priority+1;
                g->parent(v)=uk;
        }
    }
};
// 顶点的初始优先级为 int——max，最低

template<typename Tv,typename Te>
struct dfspu
{
    virtual operator ()(graph<Tv,Te> * g,int uk,int v)
    {
        if(g->status(v)==UNDISCOVERED)
        {
            if(g->priority(v)>g->priority(uk)-1)
            {
                g->priority(v)=g->priority(uk)-1;
                g->parent(v)=uk;
            }   
        }
    }
}



#endif