#include<iostream>
using namespace std;

void buddle_sort(int *a,int n)
{
    for(int j=0;j<n-1;j++)
    {
        for(int i=0;i<n-1;j++)
        {
            if(a[i]>a[i+1])
            swap(a[i],a[i+1]);
            
        }
    }
}

void buddlesort1(int *a,int n)
{
    for(int j=0;j<n-1;j++)
    {
        for(int i=0;i<n-1-j;i++)
        
       {  
            if(a[i]>a[i+1])
            swap(a[i],a[i+1]);

            for(int x=0;x<n;x++ )
                cout<<a[x]<<" ";
                cout<<endl;
       }
    }
}

void buddlesot3(int *a,int n)
{
    bool sorted=false;
    while(!sorted)
    {    
        sorted=true;  
        for(int i=0;i<n-1;i++)
        {
            if(a[i]>a[i+1])
            {
                swap(a[i],a[i+1]);
                sorted=false;
            }
        }
        n--;
    }
}


void buddlesort2(int *a,int n)
{
    for(int i=0;i<n-1;i++)
    {
        bool sorted=true;
        for(int j=0;j<n-1-i;j++)
            if(a[j]>a[j+1])
            {
                swap(a[j],a[j+1]);
                sorted=false;
            }
        if(sorted==true)
        break;
    }
}//youhua banben
int n;

void buddlesort5(int *a,int lo,int hi)
{
    int last=hi;
    int temp;
    bool flag ;
    for(int j=lo;j<hi-1;j++)
    {
        temp=last-1;
        flag = false;
        for(int i=lo;i<temp;i++)
        {
            if(a[i]>a[i+1])
            {
                swap(a[i],a[i+1]);
                last=i+1;
                flag= true;
            }

            for(int k=0;k<n;k++)
                cout<<a[k]<<" ";
            cout<<endl;
        }
        if(!flag)
            break;
    }
}// you hua banben




int main()
{
    
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
        cin>>a[i];
    cout<<"mei you you hua"<<endl;
    buddlesort1(a,n);
    
    cout<<"you hua hou"<<endl;
    buddlesort5(a,0,n);
    for(int x=0;x<n;x++)
        cout<<a[x]<<" ";


    cout<<"hello world"<<endl;
    return 0;

}