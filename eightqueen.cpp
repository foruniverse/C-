#include"stack_vector.h" // 使用的是vector定义的栈 
#include<iostream>
using namespace std;

int nsolu=0;
int ncheck=0;

struct queen
{
    int x,y;
    queen( int xx=0,int yy=0)
        :x(xx),y(yy){};
    bool operator==(const queen& q)
    const{
        return ( x==q.x
                ||y==q.y
                ||(x+y)==q.x+q.y
                ||(x-y==q.x-q.y));
    }
    
    bool operator !=(queen const&q )
    const{
        return !(*this==q);
    }// 重载操作符方便 对冲突的八皇后 进行查找 
    void show()
    {
        cout<<y<<endl;   
    }
};

void placequeens(int n) //n queen
{
    stack<queen> solu;// 回溯的工具
    queen q(0,0);   //从头开始试探合适至
    do{
        // if(solu.size()==n)
        // {
        //     Vector<queen> num;
        //     for(int i=0;i<n;i++)
        //     {
        //         num[i]=solu.pop();
        //         cout<<(num[i].y)<<" ";
        //     }
        //     cout<<endl;
        //     for(int i=n-1;i>=0;i--)
        //     {
        //         solu.push(num[i]);
        //     }
        // }  
        if(solu.size()==n)
        {
            for(int i=0;i<n;i++)
                cout<<"("<<solu[i].x<<","<<solu[i].y<<") ";
            cout<<endl;
        } 
        if(n<=q.y||n<=solu.size())
        {
            q=solu.pop();
            q.y++;
        }// 越界时回溯（列越界或行越界）
        else{
            while(q.y<n&&(0<=solu.find(q)))// 判断是否与自前放置的 皇后冲突
            {
                q.y++;
                ncheck++;
            }// quit while q.y==n or successfully find
            if(q.y<n)// 入栈 放置合适的皇后
            {
                solu.push(q);
                if(solu.size()==n)
                    nsolu++;
                q.x++;// 进入下一行 同时将列数置于第一列
                q.y=0;
            }
        }

    }while(0<q.x||q.y<n); // 在找到所有解后退出，这时候的皇后遍历位置在第一行的最末尾，我们只在这种时候退出
}
int main()
{
    placequeens(4);
    cout<<"jiejuecishu: "<<nsolu<<"\ncheck time: "<<ncheck<<endl;
    return 0;
}