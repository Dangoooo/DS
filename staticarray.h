#ifndef STATICARRAY_H
#define STATICARRAY_H
#include "array.h"
namespace DS {
template <typename T, int N>
class StaticArray : public Array<T>
{
protected:
    T m_space[N];
public:
    StaticArray()
    {
        this->Array = m_space;
    }
    StaticArray(const StaticArray<T, N>& obj)
    {
        this->m_array = m_space;
        for (int i=0;i<N;i++)
        {
          m_space[i] = obj.m_space[i];
        }
    }
    StaticArray<T, N>& operator=(const StaticArray<T, N>& obj)
    {
        if(this != &obj)
        {
            for (int i=0;i<N;i++)
            {
              m_space[i] = obj.m_space[i];
            }
        }
        return *this;
    }
    int length() const
    {
        return N;
    }
    T getMax() const
    {
        T max = m_space[0];
        for(int i=1;i<N;i++)
        {
            if(m_space[i]>max)
            {
                max = m_space[i];
            }
        }
        return  max;
    }
};

}
#endif // STATICARRAY_H
