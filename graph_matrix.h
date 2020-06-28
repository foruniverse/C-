#ifndef GRAPH_MATRIX_H_
#define GRAPH_MATRIX_H_

#include"graph.h"
#include"vector.h"

template<typename Tv>
struct Vertex
{
    Tv data;
    int indegree,outdegree;
    VStatus status;
    int dtime,ftime;
    int parent,priority;
    Vertex(Tv const& d=(Tv 0)):
        data(d),indegree(0),outdegree(0),status(UNDISCOVERED),
        dtime(-1),ftime(-1),parent(-1),priority(INT_MAX) {}

};

template<typename Te>
struct Edge
{
    Te data;
    int weight;
    EType type;
    Edge (Te const& d,int w): data(d),weight(w), type(UNDISCOVERED) {}

};


template<typename Tv,typename Te>
class graphmatrix:public graph<Tv,Te>
{
    private:
        vector<Vertex <Tv>> V;
        vector<vector<Edge <Te>*>> E;
    
    public:
        graphmatrix() {n=e=0;}
        ~graphmatrix() 
        {
            for(int j=0;j<n;j++)
                for(int i=0;i<n;i++)
                    delete E[j][i];
        }// 是否涉及指针的成员变量都需要单独析构

        virtual Tv&vertex (int i) { return V[i].data}
        virtual int indegree (int i) { return V[i].indegree;}
        virtual int outdegree( int i) { return V[i].outdegree;}
        virtual int firstnbr(int i) {return nextnbr(i,n);}
        virtual int nextnbr(int i,int j) 
        {
            while((-1<j)&&(!exist(i,--j)));
            return j;
        }
        virtual int &dtime(int i) {return V[i].dtime;}
        virtual int &ftime(int i)   {return V[i].ftime;}
        virtual int &parent(int i)   {return V[i].parent;}
        virtual int &priority(int i)   {return V[i].priority;}
        virtual VStatus &status (int i) { return V[i].status;}
        virtual bool exists(int i,int j)
        {
            return (0<=i)&&(i<n)&&(0<=j)&&(j<n)&&(E[i][j]!=NULL);
        }
        virtual EType& type(int i,int j) {return E[i][j]->type;}
        virtual Te& edge(int i,int j) {return E[i][j]->data;}
        virtual int& weight(int i,int j) {return E[i][j]->weight;}

        virtual int insert(Tv const&vertex)
        {
            for(int j=0;j<n;j++)// 
                E[j].insert(NULL);// 调用的是vetor的insert（在末节点插入） 由于边的类型是指针，所以插入NULL
            n++;
            E.insert(vector<Edge<Te>*>(n,n,(Edge<Te>*)NULL));// 插入边
            //这里的情况比较复杂，注意，我们使用了vector 的构造函数
            /*我们插入了一个vector的临时变量，注意我们可以入代码所示来声明临时类
            同时我们使用的是vector的insert函数，另外，这里有一个关于const的小细节，
            当你传入一个变量时，编译器总是认为你可能会修改这个值，这没有什么问题，可问题出现在当你传入一个临时变量时
            编译器也认为你会修改它，可临时变量是不能被修改的，所以就会报错，怎么解决它呢？
            我们应该在传入它时，使用（const T&）,另外这也在其他一些地方发生相同错误，所以我们必须在所有有必要的地方全部加上const
            嗯，对，就这样*/
            return V.insert(Vertex<Tv> (vertex));//插入点集合
        }

        // // 假设我们为一个结构体分配内存空间
        // int main()
        // {
        //     Edge *p= new Edge;
        //     //然后我们删除p分配的空间
        //     delete p;
        //     //事实上我们只是删除了p 指向的堆内存的内容，而并没有删除p指针的值，它现在只是变成了一个空指针而已
        //     // 这是很重要的一点
        // }

        virtual Tv remove(int i)
        {
            Tv vBAK=V[i];
            for(int j=0;i<n;i++)
                if(exists(i,j))
                {
                    delete E[i][j];//删除已分配的堆内存

                  
                    V[j].indegree--;
                }
            E.remove(i);// 删除第i行
            e=e-2*n+1;
            n--;
            for(int j=0;j<n;j++)
            {
                if(Edge<Te>* e=E[j].remove(i))//神来之笔，这局代码的逻辑导致我们少了一行代码，完美了利用了各个接口和if()的特性 
                    {
                        delete e;//删除已分配的堆内存
                        V[j].outdegree--;
                    }
            }
            V.remove(i);
            return vBAK;
        }//删除点，与其对应的所有出边 和 入边，由于这里的类型是指针，所以还涉及到一些对内存的操作，
        //正如指针总是很微妙的，所以对内存的操作也很微妙  -_-  ....

        virtual Te remove(int i,int j)
        {
            if(!exists(i,j))
                return ;
            Te eBAk=edge(i,j);// edge返回边的data
            delete E[i][j];// 删除内存内容
            E[i][j]=NULL;
            e--;
            V[i].outdegree--;
            V[j].indegree--;
            return eBAK;
        }

        virtual void insert(const Te& edge_1,int w,int i,int j)
        {
            if(exists(i,j))
                return ;
            E[i][j]=new Edge(i,j)(edge_1,w);// 指向类的指针的一种可行构造方式
            e++;
            V[i].outdegree++;
            V[j].indegree++;
        }

};

//初始化为NULL的类指针可以安全的调用不涉及类成员变量的类成员函数而不出错，但是如果类成员函数中调用了类成员变量则会出错，
//既然赋值为NULL的情况都可以使用，那么自然不初始化的类指针同样满足这类情况。
#endif