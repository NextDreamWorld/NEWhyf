#include "CList.h"

template<class T>
CList<T>::~CList()
{
     if(NULL != m_Head)
     {
         delete[] m_Head;
         m_Head = NULL;
     }
     m_size = 0;
     m_length = MIX_LENGTH;
}

template<class T>
int CList<T>::Add(T& point)
{
    // 为空的队列分配内存
    if(NULL == m_Head)       
    {
       m_Head = new T*[m_length];
       if(NULL == m_Head)
       {
           cout<<"ERROR: not enough memeory for new!"<<endl;
           return -1;
       }
    }
    else if( m_size >= m_length )       //队列空间不足，扩充队列
    {
       int iOldLength = m_length;
       
       m_length = ((m_length >= MAX_LENGTH) ? m_length+MAX_LENGTH : 3*m_length );
       
       T* tmpHead = new T*[m_length];
       if(NULL == tmpHead)
       {
           m_length = iOldLength;
           cout<<"ERROR: not enough memeory for new!"<<endl;
           return -1;
       }

       memcpy(tmpHead, m_Head, sizeof(T)*m_size);
       delete[] m_Head;
       m_Head = tmpHead;
    }
    
    if( NULL != m_head[m_size])
    {
    	 delete m_head[m_size];
    }
    
    m_head[m_size] = new T;
    m_Head[m_size] = point;
    m_size++;

    return 0;
}
