#include<iostream>
#include"list.h"
using namespace std;

template<typename T>
void randomlist(list<T> & list,T const&n)
{
    listnodeposi(T) p=
    (rand()%2)?
    list.insertaslast(rand()%(T)n*2):
    list.insertasfirst(rand()%(T)n*2);

    for(int i=1;i<n;i++)
        p=rand()%2?
            list.insertb(p,rand()%(T) n*2):
            list.inserta(p,rand()%(T) n*2);
}

template<typename T>
void testlist( int testsize)
{
    list<T> la;
    randomlist<T>(la,testsize);
    cout<<"the list would be: \n";
    la.find(14);
    la.show();
    la.selectionsort(la.first(),testsize);
    cout<<"the final list after sort\n";
    la.show();
    la.reverse2();
    la.show();
    la.insertionsort(la.first(),testsize);
    la.show();
    listnodeposi(T) p=la.first();
    Rank r=5;
    while(r--)
    p=p->succ;
    cout<<p->data<<endl;
    la.inserta(p,11);
    testsize+=1;
    la.show();
    p=la.find(10,testsize,la.last()->succ);
    cout<<p->data<<endl;
    p=la.selectmax(la.first(),testsize);
    cout<<p->data<<endl;
    la.uniquify();
    la.show();
    la.insertasfirst(666);
    la.show();
}

int main()
{
//     list<int> la;
//     int n;
//     cin>>n;
//     // int temp;
//     randomlist<int>(la,n);
//     // listnodeposi(int) p=la.insertaslast(rand()%2);
//     // la.traverse1(print);
//     cout<<la.size()<<endl;
//     la.selectionsort()
//     la.show();
    testlist<int>(10);
    return 0;
    
}   




