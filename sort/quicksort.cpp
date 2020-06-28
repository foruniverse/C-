#include<iostream>
using namespace std;

int findMi(int,int,int []);

void quicksort(int lo,int hi,int a[])
{
    if(hi-lo<2) return ;
    int mi=findMi(lo,hi-1,a);
    quicksort(lo,mi-1,a);
    quicksort(mi,hi,a);
}


int findMi(int lo,int hi,int a[])
{
    swap(a[lo],a[lo+rand()%(hi-lo+1)]);
    int p=a[lo];
    while(hi!=lo)
    {
        while(hi>lo && a[hi]>=p)
            hi--;
        if(lo<hi) 
            a[lo++]=a[hi];
        while(lo<hi && a[lo]<=p)
            lo++;
        if(lo<hi)
            a[hi--]=a[lo];
    }
    a[lo]=p;
    return lo;
}




#define N 10

int main()
{
    int a[N];
    for(int i=0;i<N ; i++)
    {
        a[i]=rand()%10;
    }
    quicksort(0,N,a);
    for(int x:a)
        cout<<x<<" ";
    
    cout<<endl;
    return 0;
}