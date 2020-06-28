#ifndef GRAPH_H_
#define GRAPH_H_

#include<iostream>
#include"stack_vector.h"
#include"Queue.h"
using namespace std;

typedef enum{UNDISCOVERED,DISCOVERED,VISITED} VStatus;
typedef enum{UNDETERMINED,TREE,CROSS,FORWARD,BACKWARD} EType;


template<typename Tv,typename Te>
class graph
{
    private:
        void reset()
        {
            for(int i=0;i<n;i++)
            {
                status[i]=UNDISCOVERED;
                dtime(i)=ftime (i)=-1;
                parent (i)=-1;
                priority(i) =INT_MAX;
                for(int j=0;j<n;j++)
                    if(exists(i,j))
                        type(i,j)=UNDISCOVERED;
            }
        }
    
        void BFS(int ,int &);// bfs （连通域）广度优先
        void DFS(int ,int &); // dfs
        void DFS_1(int ,int &);// dfs diedai banben
        void BCC(int ,int &,stack<int>&);// 基于dfs的双连通分量分解算法
        bool TSORT(int,stack<Tv>*);// 基于dfs的拓扑排序
        template<typename PU> void PFS(int ,PU);
    public:
        int n;
        int e;
        
        virtual int insert(Tv,const&) =0;
        virtual Tv remove(int )=0;// shandian
        virtual Tv&vertex(int ) =0;
        virtual int indegree(int )=0;
        virtual int outdegree()=0;
        virtual int firstnbr()=0;
        virtual int nextnbr(int ,int)=0; 
        virtual int& dtime(int)=0;  
        virtual int& ftime(int)=0;
        virtual int& parent(int)=0; 
        virtual int& priority(int)=0; 
        virtual VStatus & status(int)=0;
        virtual bool exists(int,int)=0;
        virtual void insert(Te const&e,int,int,int)=0;//chabian
        virtual Te remove(int,int)=0; // shanbian
        virtual EType&type (int,int)=0;
        virtual Te& edge(int,int)=0;
        virtual int & weight(int,int)=0;
        
        void dfs_1(int);
        void bfs(int);
        void dfs(int);
        void bcc(int);
        stack<Tv> *tsort(int);
        bool TSORT_1(Queue<int> &);// 非 dfs 的拓扑排序
        void pfs(int ,PU);    
    
};

template<typename Tv,typename Te>
template<typename PU>
void graph<Tv,Te>::pfs(int s,PU prioupdater)
{
    reset();
    int v=s;
    do if(UNDISCOVERED==status(v))
            PFS(v,prioupdater)
    while(s!=(v=(++v%n)));
}

template<typename Tv,typename Te>
template<typename PU>
void graph<Tv,Te>::PFS(int v,PU prioupdater)
{
    priority(v)=0;
    status(v)=VISITED;
    while(true)
    {
        for(int u=firstnbr(v);-1<u;u=nextnbr(v,u))
            prioupdater(this,v,u);
        
        for(int shortest=INT_MAX,u=0;u<n;u++)
            if(UNDISCOVERED==status(u))
                if(shortest>priority(u))
                {
                    shortest=priority(u);
                    v=u;
                }//只有在存在优先级更低的时候才更新s
        
        if(status(v)=VISITED)// 只有两种状态，undicovered和visited
            break;
        status(v)=VISITED;
        type(parent(v),v)=TREE;
        
    }
}

template<typename Tv,typename Te>
void graph<Tv,Te>::bcc(int S)
{
    reset();
    int clock=0;
    int v=S;
    stack<int> s;
    do if(UNDISCOVERED==status(v))
        {
            BCC(v,clock);
        }while(S!=(++v(v%n)));
    
    
}

#define hca(x) (ftime(x))
template<typename Tv, typename Te>
void graph<Tv,Te>::BCC(int v,int &clock,stack<int> &s)
{
    status(v)=DISCOVERED;
    s.push(v);
    hca(v)=dtime(v)=++clock;
    for(int u=firstnbr(v);-1<u;u=nextnbr(v,u))
    {
        switch(status(u))
        {
            case UNDISCOVERED:
                type(v,u)=TREE;
                parent(u)=v;
                BCC(u,clock,s);
                if(hca(u)<dtime(v))
                    hca(v)=min(hca(u),hca(v));
                else
                {
                    while(v!=s.pop());
                    s.push(v);
                }                
            case DISCOVERED:
                type(v,u)=BACKWARD;
                if(parent(v)!=u)
                hca(v)=min(dtime(u),hca(v));// 不能省略min（）的原因是，父节点v可能和更上层的祖先建立了通路
            default:
                type(v,u)=(dtime(v)<dtime(u)?FORWARD:CROSS);   
        }

    }
    status(v)=VISITED;
}

#undef hca


template<typename Tv,typename Te>
stack<Tv> * graph<Tv,Te>::tsort(int s)
{
    reset();
    stack<Tv> *S =new stack<Tv>;
    int v=s;
    do  if(UNDISCOVERED==status(v))        
            if(!TSORT(v,s))// 如果失败 则返回false 直接结束整个循环
            {
                while(!S.empty())
                    s.pop();
                break;
            }                  
    while(s!=(v=(++v%n)));
    return S;  // 如果失败（存在通路） s为空 否则 栈顶为拓扑排序的起始顶点；
}

template<typename Tv,typename Te>
bool graph<Tv,Te>::TSORT(int v,stack<Tv> *s)// 基于dfs的拓扑排序，如果存在通路 return false结束整个程序
{
    status(v)=DISCOVERED;
    for(int u=firstnbr(v);-1<u;u=nextnbr(v))
        switch(status(u))
        {
            case UNDISCOVERED:// ke shou suo de dian
                if(!TSORT(u,s))
                    return false;
                break;
            default:// huanlu
                return false;
        }
    status(v)=VISITED;
    s.push(v);
}// 精简后的拓扑排序，源代码参考教材
// 时间复杂度：O(n+e) 应该是reset的原因 暂时不清楚 枚举所有节点（建立在存在有效拓扑排序上） 空间复杂度：O(n)
template<typename Tv,typename Te>
bool TSORT_1(Queue<int> &q)
{
    stack<int> s;
    for(int i=0;i<n;i++)
    {
        if(V[i].indegree=0)
        s.push(i);
    }
    int t;
    while(!s.empty())
    {
        t=s.pop();
        q.enqueue();
        for(int i=0;i<n;i++)
        {
            if(exists(t,i)&&(V[i].indegree<2))
                s.push(i);
        }
        V.remove(t);
    }
    
    return (n?false:true); 
}


template<typename Tv,typename Te>
void graph<Tv,Te>::bfs(int s)
{
    reset();
    int clock=0;
    int v=s;
    // for(int i=0;i<n;i++)
    // {
    //     if(status(i)=UNDISCOVERED)
    //         BFS(i,clock);
    // }// cannot do that 
    do if(status(v)=UNDISCOVERED)
            BFS(v,clock);
    while(s!=(v=(++v%n));// we need to jump vertex s; 

}

template<typename Tv,typename Te>
void graph<Tv,Te>::BFS(int v,int & clock)
{
    Queue<int> Q;
    status(v)=DISCOVERED;
    Q.enqueue(v);
    while(!Q.empty())
    {
        int v=Q.dequeue();
        dtime(v)=++clock;
        for(int u=firstnbr(v);-1<u;u=nextnbr(v,u))
        {
            if(status(u)==UNDISCOVERED)
            {
                Q.enqueue(u);
                status(u)=DISCOVERED;
                type(v,u)=TREE;
                parent(u)=v;
            }else   type(v,u)=CROSS;    
        }
        status(v)=VISITED;
    }
}

template<typename Tv,typename Te>
void graph<Tv,Te>::dfs(int s)
{
    reset();
    int clock=0;
    int v=s;
    do if(status==UNDISCOVERED)
            DFS(v,clock);
    while(s!=(v=(++v%n)));
}

template<typename Tv,typename Te>
void graph<Tv,Te>::DFS(int v,int &clock)
{
    // here is where it should to be
    dtime(v)=++clock;
    status(v)=DISCOVERED;
    for(int u=firstnbr(v);-1<u;u=nextnbr(v))
        switch(status(u))
        {
            case UNDISCOVERED:// ke shou suo de dian
                type(v,u)=TREE;
                parent(u)=v;
                //status(u)=DISCOVERED;
                // cannot turn vertex u in here;
                DFS(u,clock);
                break;
            case DISCOVERED:// huanlu
                type(v,u)=BACKWARD;
                break;
            default:
                type(v,u)=(dtime(v)<dtime(u)?FORWARD:CROSS);
        }
    status(v)=VISITED;
    ftime(v)=++clock;
}// 空间复杂度 ：O(e+n) (忽略了操作系统为了维护递归所调用的栈）时间复杂度：O(n+e)



/*迭代版我写了三个小时，也不知为什么。写完后才始觉似乎并不复杂，可为什么我写了这么久呢，
尤其是在我写完了递归版之后，应该对整个流程有了很大了解，为什么我模仿它，模拟它的过程还觉得如此的艰难呢
对于图的dfs遍历算法，对于我一直纠结于的问题是回溯时怎么避免改变已访问的边，
我的想法是：
        1.单独区分回溯的顶点，为此我引入了回溯状态位，可是接着我发现，无法在合适的时候消除回溯位
        2.跳过回溯顶点，为此我尝试引入临时变量保存上个回溯顶点的 邻接矩阵的位置，但这种方式只能保存同一层的
            t值，在迭代到更深层时，无法保存上一层的t值，当然我们也可以继续做一些小修改，可是程序会变得不简洁
        3.其实，根本原因是对整个过程对顶点和边的操作过程没有清晰的了解，边的初始状态是空，而回溯时必定不为空
            那么只需选择空边进行操作，就这么简单，
        4.但难道上文所提到的思路真的需要这么长的思考和实现时间吗， 我认为不是这样的，我的思考过程存在问题
            思考应是连续且充满突破性的，一旦碰壁，那么立刻思考解决办法，永远不要思维跳空，思考就是发现规律，
            找到关键，然后用已有的经验和思路结合问题实际来解决问题
            总而言之，思考的过程应该是极其专注的，这才是你变强的最重要的一点

*/
template<typename Tv,typename Te>
void graph<Tv,Te>::dfs_1(int v)
{
    reset();
    int clock=0;
    // BFS_1(v,clock);
    // for(int i=0;i<n;i++)
    // {
    //     if(status(i)==UNDISCOVERED)
    //         DFS_1(i,clock);
    // }
    int s=v;
    do if(status==UNDISCOVERED)
            DFS_1(v,clock);
    while(s!=(v=(++v%n)));// no repeat
}

template<typename Tv,typename Te>
void graph<Tv,Te>::DFS_1(int v,int &clock)
{
    bool nontr=false;
    stack<int> s;
    s.push(v);// 我们用栈来模拟回溯的过程
    status(v)=DISCOVERED;
    ditme(v)=++clock;// 既然我们每次访问一个点的方式是将它入栈，那么其对应的接触时间应该与入栈操作一起进行。

    while(!s.empty())
    {
        int v=s.top();
        nontr=false;
        for(int u=firstnbr(v);-1<u;u=nextnbr(v,u))
        {    
            if(UNDISCOVERED==status(u))// 只有在下一个顶点为 undicovered时我们才访问它
            {
                s.push(u);
                ditme(v)=++clock;
                nontr=true;
                type(v,u)=TREE;
                parent(u)=v;
                break;
            }
            else if(status(u)==DISCOVERED)// 如果在从 根节点s到现节点v的访问过程中，发现了这种类型的顶点，那么u必为v的父节点
            {
                type(v,u)=BACKWARD;
            }
            else if(type(v,u)==UNDETERMINED)// 回溯过程中 ，一visit的节点必定是 visited的状态，这时(v,u) 应为树边，为了排除这种情况
                type(v,u)=(dtime(v)<ditme(u)?FORWARD:CROSS);
        } 
        if(nontr==false)// 当v节点没有任何处于undicovered节点时，必然到了该部分dfs的最低点，出栈
        {
            int t=s.pop();
            status(t)=VISITED;
            ftime(t)=++clock;// 完成时间，结束该节点的活跃期
        }
    }
}


template<typename Tv,typename Te>
void 


#endif