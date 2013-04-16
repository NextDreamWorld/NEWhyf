#ifndef CLIST_H_
#define CLIST_H_

#include<iostream>
using namespace std;

#define MIX_LENGTH 32
#define MAX_LENGTH 1024

template<class T>

class CList
{

private:
    int m_size;
    int m_length;
    T* m_Node;
    T* m_Head;
public:
    CList():m_size(0),m_length(MAX_LENGTH),m_Node(NULL)
    {
    }
    ~CList();
    int Add(T&);
    void Erase();
    int size(){ return m_size; }
};

#endif
