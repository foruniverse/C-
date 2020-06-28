#ifndef ENTRY_H
#define ENTRY_H_ 

template<typename K,typename V>
struct Entry
{
    K key;
    V value;
    Entry(K k=K(), V v=V()):key(k),value(v) {};
    Entry(Entry<K,V> const &e):key(e.key),value(e.value) {};
       bool operator< ( Entry<K, V> const& e ) { return key <  e.key; }  //比较器：小于
    bool operator> ( Entry<K, V> const& e ) { return key >  e.key; }  //比较器：大于
    bool operator== ( Entry<K, V> const& e ) { return key == e.key; } //判等器：等于
    bool operator!= ( Entry<K, V> const& e ) { return key != e.key; } 
};


#endif