#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include"dictionary.h"
#include "Entry.h"
#include"bitmap.h"
//size _t 为无符号数（32/64）
// longlong 64位 8字节
static size_t hashcode(char c) {return (size_t) c;}
static size_t hashcode(int k)  {return (size_t) k;}
static size_t hashcode(long long i) {return (size_t) i;}
static size_t hashcode(char s[])
{
    int h=0;
    for(size_t n=strlen(s),i=0;i<n;i++)
    {
        h=(h<<5)|(h>>27);
        h+=(int) s[i];
    }
    return (size_t) h;
}

template<typename K, typename V>
class hashtable :public dictionary<K,V>
{
    private:
        Entry<K,V> **ht;
        int M;
        int N;

    protected:
        int probe4bit(const K&k);
        int probe4Free(const K& k);
        void rehash();
    
    public:
        hashtable (int c=5);
        ~hashtable();
        int size() const {return N;}
        bool put (K,V);
        V*get(K k);
        bool remove(K k);
};

template<typename K,typename V>
void hashtable<K,V>::rehash()
{
    int old_capacity= M;
    Entry<K,V> **old_ht=ht;

    
    M=primeNLT(2*M);
    ht=new Entry<K,V>* [M];
    memset(ht,0,sizeof(Entry<K,V>*)*M);
    release(lazyRemoval);
    lazyRemoval= new bitmap(M);

    for(int i=0;i<old_capacity;i++)
    {
        if(old_ht[i])
        //    ht[i]=old_ht[i];
        //old_ht[i]=NULL;
            put(old_ht[i]->key,old_ht[i]->value);
    }
    release(old_ht);
}

template<typename K,typename V>
hashtable<K,V>:: hashtable (int c)
{
    M=primeNLT();
    N=0;
    ht=new Entry<K,V>;
}

template<typename K,typename V>
hashtable<K,V>::~hashtable()
{
    for(int i=0;i<M;i++)
    {
        if(ht[i]) release(ht[i]);
        release(ht);
        release(lazeRemoval);
    }
}

template<typename K,typename V>
V* hashtable<K,V>::get(K k)
{
    int r=probe4bit(k);
    return ht[r]? &(ht[r]->value):NULL;
}

template<typename K,typename V>
int hashtable<K,V>::probe4bit(const K&k)
{
    int r=hashcode(k)%M;
    while((ht[r]&&k!=ht[r]->key)||(!ht[r]&&lazyRemoved(r)))
    {
        r=(r+1)%M;
    }
    return r;
}

template<typename K,typename V>
bool hashtable<K,V>::remove(K k)
{
    int r=probe4bit(k);
    if(!ht[r]) return false;
    releas(ht[r]);
    ht[r]=NULL;
    markasRemoved(r);
    N--;
    return true;
}

template<typename K,typename V>
bool hashtable<K,V>::put(K k,V v)
{
    if( ht[probe4bit(k)])
        return false;
    int r=probe4Free(k);
    ht[r]=new Entry<K,V>(k,v);
    
    if(N*2>M)
        rehash();
    return true;
}

template<typename K, typename V>
int hashtable<K,V>::probe4Free(const K&k)
{
    int r=hashcode(k);
    while(ht[r])
        r=(r+1)%M;
    return r;
}// 基于线性链法的试探策略




#endif