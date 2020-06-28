#include<cstring>
#include<iostream>
#include"limits.h"
using namespace std;

// #define  UINT_MAX 4294967295 ; 
int match(char *P,char *T)
{
    int n=strlen(T);
    int m=strlen(P);

    int i=0,j=0;
    while(i<n&&j<m)
    {
        if(P[j]==T[i])   
        {
            i++;
            j++;
        }else{
            i=i-j+1;
            j=0;
        }
    }
    if(i>=n) return -1;
    return i-j;
}

// int match_1(char *p, char *t)
// {
//     int * next=buildnext(p);
//     int n=strlen(t);
//     int m=strlen(p);
//     int j=0,i=0;
//     while(j<m&&i<n)
//     {
//         if(0>j|| t[i]==t[j])
//         {
//             i++;
//             j++;
//         }else
//         {
//             j=next[j];
//         }
        
//     }
//     delete []next;
//     return i-j;
// }

// int * buildnext(char *p)
// {
//     size_t m=strlen(p),j=0;
//     int *N =new int[m];
//     int t=N[0]=-1;
//     while(j<m-1)
//     {
//         if(p[t]==p[j])
//         {
//             i++;
            
//         }        
//     }
// }


int *buildss(char * p)
{
    int m=strlen(p);
    int *ss=new int[m];
    ss[m-1]=m;

    for(int j=m-2,lo=m-1,hi=m-1;j>=0;j--)
    {
        if(lo<j && ss[m-hi+j-1]<=j-lo)//fuyong
        {
            ss[j]=ss[m-hi+j-1];
        }else{
            hi=j;
            lo=min(hi,lo);
            while(lo>=0 && p[lo]==p[m-(hi-lo)-1])
                lo--;
            ss[j]=hi-lo;
        }// this codeblock contains two situations: one belongs to j<lo,and the other one is lo<j while ss[m-hi+j-1]>j-lo
    }
    return ss;
}

int * buildgs(char *p)
{
    int * ss=buildss(p);
    size_t m=strlen(p);
    int * gs=new int[m];
    

    for(size_t i=0;i<m;i++) 
    {
        gs[i]=m;
    }

    for(size_t i=0,j=m-1;j<UINT_MAX;j--)
    {
        if(ss[j]==j+1)
            while(i<m-j-1)
                gs[i++]=m-j-1;// 从小到大 赋值的一种解释是为了取得最小的移动值，其实对于更大的i，更小的i也是可以赋成大i的值，但是不够小
        // else{
        //     gs[m-ss[j]-1]=m-j-1; 第二种赋值是我们更想要的理想值，
        // } 不能在这里进行赋值，由于画家算法的原理，在这里赋的理想值极有可能被覆盖掉，导致gs值不准确
    }
    for(size_t i=0;i<m-1;i++)
        gs[m-ss[i]-1]=m-i-1;
    return gs;
}


int *buildbc(char *p)
{
    int *bc= new int[256];
    for(int i=0;i<256;i++)
        bc[i]=-1;
    for(int i=0;i<strlen(p);i++)
        bc[p[i]]=i;
    return bc;
}

int match_2(char *p,char *t)
{
    int *bc=buildbc(p);
    int *gs=buildgs(p);
    size_t m=strlen(p),i=0;
    
    //size_t i=0,j=m-1;
    for(int j=m-1;i<=strlen(t)-m && j>=0;)
    {
        if(t[i+j]==p[j])
        {
            --j;
            if(j<0) break;
        }else{
            i+=max(j-bc[t[i+j]],gs[j]);
            j=m-1;
        }
    }
    delete []gs;
    delete []bc;
    return i;
}

int match_21(char *p,char *t)
{
    int * bc=buildbc(p);
    int * gs=buildgs(p);

    size_t m=strlen(p),i=0;

    while(i<strlen(t)-m)
    {
        int j=m-1;
        while(p[j]==t[i+j])
            if(--j<0) break;
        if(j<0) break;
        else 
        i+=max(j-bc[t[i+j]],gs[j]);
    }
    delete []bc;
    delete []gs;
    return i;

}


void findString(char *p,char *t)
{
    int i=match_2(p,t);
    int m=strlen(p);
    int n=strlen(t);
    
    if(i<n-m)
        cout<<"在目标字符串的第"<<i<<"位找到目标字符串"<<endl;
    else cout<<"no found"<<endl;
}





int main()
{
    char t[11]="helloworld";
    char p[4]="wor";

    //UINT_MAX j=-1;
    // int i=match_2(p,t);
    
    // cout<<i<<endl;
    //system("pause");

    findString(p,t);
    return 0;
  }