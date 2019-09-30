#ifndef STATICQUEUE_H
#define STATICQUEUE_H
#include "queue.h"
#include "exception.h"
namespace DS {
template<typename T, int N>
class StaticQueue : public Queue<T>
{
protected:
    T m_space[N];
    int m_front;
    int m_rear;
    int m_length;
public:
    StaticQueue()
    {
        m_length = 0;
        m_front = 0;
        m_rear = 0;
    }
    void add(const T& e)
     {
         if(m_length<N)
         {
             m_space[m_rear] = e;
             m_rear = (m_rear+1)%N;
             m_length++;
         }
         else {
             THROW_EXCEPTION(InvalidOperationException, "No memory in current queue...");
         }
     }
     void remove()
     {
         if(m_length>0)
         {
             m_front = (m_front+1)%N;
             m_length--;
         }
         else {
             THROW_EXCEPTION(InvalidOperationException, "No element in current queue...");
         }
     }
     T front() const
     {
         if(m_length>0)
         {
             return m_space[m_front];
         }
         else {
             THROW_EXCEPTION(InvalidOperationException, "No element in current queue...");
         }
     }
     void clear()
     {
         m_front = 0;
         m_rear = 0;
         m_length = 0;
     }
     int length() const
     {
         return m_length;
     }
     int capacity() const
     {
         return N;
     }
     ~StaticQueue()
     {
         clear();
     }

};
}
#endif // STATICQUEUE_H
