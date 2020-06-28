#include<iostream>
using namespace std;

void mergesort(int,int,int[]);
void selectsort(int ,int,int []);
void quicksort(int,int,int []);
void insertsort(int ,int, int []);
void quicksorta(int,int,int[]);
int model(int,int,int[]);
void print(int,int,int[]);
int n;
int main()
{
    
    cin>>n;
    // int a[n];
    // for(int i=0;i<n;i++)
    //     cin>>a[i];
    
    //sort(0,n,a);


    int a[n];
    for(int i=0;i<n;i++)
    {
        a[i]=rand()%100;
        cout<<a[i]<<" ";
    }
    cout<<endl;
    //quicksort(0,n,a);
    mergesort(0,n-1,a);
    
    for(int x:a)
        cout<<x<<" ";
    cout<<endl;
    return 0;
}
void print(int lo,int hi,int c[])
{
    for(int i=lo;i<hi;i++)
        cout<<c[i]<<" ";
    cout<<endl;
}

int s[10];
void mergesort(int a,int b,int c[])
{

    if(a==b)    return;
    int mid=(a+b)/2;
    mergesort(a,mid,c);
    mergesort(mid+1,b,c);

    int i=a,j=mid+1;
    int k=a;
    while(i<=mid && j<=b)
    {
        if(c[i]<=c[j])
            s[k++]=c[i++];
        else s[k++]=c[j++];
    }
    while(i<=mid)   s[k++]=c[i++];
    while(j<=b) s[k++]=c[j++];

    for(int i=a;i<=b;c[i]=s[i],i++);

}


void insertsort(int a,int b,int c[])
{
    int j;
    for(int i=0;i<b;i++)
    {

        for(j=i-1;j>=0;j--)
        {
            if(c[i]>c[j])   break;
        }
        if(j!=i-1)
        {
            int temp=c[i];
            for(int k=i;k>j+1;k--)
                c[k]=c[k-1];
            c[j+1]=temp;
        }
    }
}
int num=0;
// void quicksort(int a,int b,int c[])
// {

//     int mid=c[(a+b-1)/2];
//     int lo=a;
//     int hi=b-1;
//     while(lo<hi)
//     {
//         while(c[lo]<mid) lo++;
//         while(c[hi]>mid) hi--;

//         if(lo<hi)
//         {
//             int temp=c[lo];
//             c[lo]=c[hi];
//             c[hi]=temp;
//             //cout<<"第"<<++num<<"次交换"<<endl;
//             for(int i=0;i<n;cout<<c[i++]<<" ");
//             cout<<endl;
//             lo++;
//             hi--;
//         }
//     }
//     if(lo-a>1) quicksort(a,lo+1,c);
//     if(b-hi>1) quicksort(lo+1,hi+1,c);

// }

int model(int lo,int hi,int c[])
{
    
    swap(c[lo],c[rand()%(hi-lo+1)+lo]);
    int temp=c[lo];
    while(lo<hi)
    {
        while(lo<hi && c[hi]>temp) hi--;
        c[lo++]=c[hi];
        while(lo<hi && c[lo]<temp) lo++;
        c[hi--]=c[lo];
        print(0,n,c);
    }
    c[lo]=temp;
    return lo;

}

void quicksort(int a,int b,int c[])
{

    if(b-a<2) return;
    
    int p=model(a,b-1,c);

    quicksort(a,p,c);
    quicksort(p+1,b,c);
}

void quicksorta(int a,int b,int c[])
{

    int mid=c[(a+b)/2];
    int lo=a;
    int hi=b;

    do{
        while(c[lo]<mid)    lo++;
        while(c[hi]>mid)    hi--;

        if(lo<=hi)
        {
            int temp=c[lo];
            c[lo]=c[hi];
            c[hi]=temp;
            for(int i=0;i<n;cout<<c[i++]<<" ");
            cout<<endl;
            lo++;
            hi--;
        }
    }while(lo<=hi);
    if(a<hi)    quicksorta(a,hi,c);
    if(lo<b)    quicksorta(lo,b,c);
}

void selectsort(int lo,int hi,int a[])
{

    for(int i=0;i<hi;i++)
    {

        int k=i;
        for(int j=i+1;j<hi;j++)
        {
            if(a[j]<a[k])
                k=j;
        }
        if(k!=i)
        {
            int temp=a[i];
            a[i]=a[k];
            a[k]=temp;
        }
    }
}





