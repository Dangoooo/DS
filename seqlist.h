#ifndef SEQLIST_H
#define SEQLIST_H

#include "exception.h"
#include "list.h"
namespace DS {
template <typename T>
class SeqList : public List<T>
{
protected:
    T* m_array;
    int m_length;
public:
    bool insert(int i, const T& e)
    {
       bool ret = ((i >= 0)&&(i <= m_length));
       ret = ret && (m_length<capacity());
       if(ret)
       {
           for(int j=m_length-1; j>=i; j--)
           {
               m_array[j+1] = m_array[j];
           }
           m_array[i]= e;
           m_length++;
       }
       return ret;
    }
    bool insert(const T& e)
    {
        return insert(m_length, e);
    }
    bool remove(int i)
    {
        bool ret = ((i>=0)&&(i<m_length));
        if(ret)
        {
            for (int j=i; j<m_length-1; j++)
            {
               m_array[j] = m_array[j+1];
            }
            m_length--;
        }
        return ret;
    }
    bool get(int i, T& e) const
    {
       bool ret = ((i>=0)&&(i<m_length));
       if(ret)
       {
           e = m_array[i];
       }
       return  ret;
    }
    bool set(int i, const T& e)
    {
        bool ret = ((i>=0)&&(i<m_length));
        if(ret)
        {
           m_array[i] = e;
        }
        return ret;
    }
    int find(const T& e) const
    {
        for (int i=0;i<m_length;i++)
        {
            if(e == m_array[i])
            {
                return i;
            }
            else {
                return -1;
            }
        }
    }
    int length() const
    {
        return m_length;
    }
    void clear()
    {
        m_length = 0;
    }

    T& operator[](int i)
    {
        if(i>=0&&i<m_length)
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
        }
    }
    T operator[](int i) const
    {
        return const_cast<SeqList<T>&>(*this)[i];
    }

    virtual int capacity() const = 0;
};

}

#endif // SEQLIST_H
