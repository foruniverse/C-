#ifndef DICTIONARY_H_
#define DICTIONARY_H_

template<typename K,typename V>
struct dictionary
{
    virtual int size() const =0;
    virtual bool put(K,V) =0;
    virtual V*get(K k) =0;
    virtual bool remove(K k)=0;
};

#endif