#ifndef ARRAY_H
#define ARRAY_H
#include "object.h"
#include "exception.h"
namespace DS {

template <typename T>
class Array : public Object
{
protected:
    T* m_array;
public:
    virtual bool set(int i, T& e)
    {
        bool ret = (i>=0&&i<length());
        if(ret)
        {
            m_array[i] = e;
        }
        return ret;
    }
    virtual bool get(int i, T& e) const
    {
        bool ret = (i>=0&&i<length());
        if(ret)
        {
           e = m_array[i];
        }
        return ret;
    }
    virtual int length() const = 0;

    T& operator[](int i)
    {
        if(i>=0&&i<length())
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");

        }
    }
    T operator[](int i) const
    {
        const_cast<Array<T>&>(m_array)[i];
    }
    T* array() const
    {
        return m_array;
    }

    virtual T getMax() const = 0;

};

}
#endif // ARRAY_H
