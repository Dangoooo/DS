#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include "array.h"
#include "exception.h"
namespace DS {
template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;
public:
    DynamicArray(int length)
    {
       this->m_array = new T[length];
        if(this->m_array != nullptr)
        {
            m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object...");
        }
    }
    DynamicArray(const DynamicArray<T>& obj)
    {
        this->m_array = new T[obj.m_length];
         if(this->m_array != nullptr)
         {
             m_length = obj.m_length;
             for(int i=0; i<m_length; i++)
             {
                 this->m_array[i] = obj.m_array[i];
             }
         }
         else
         {
             THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object...");
         }
    }
    DynamicArray<T>& operator=(const DynamicArray<T>& obj)
    {
        if(this != &obj)
        {
           T* array = new T[obj.m_length];
           if(array != nullptr)
           {
               for (int i=0;i<obj.m_length;i++)
               {
                   array[i] = obj.m_array[i];
               }
               T* temp = this->m_array;
               this->m_array = array;
               this->m_length = obj.m_length;
               delete [] temp;
           }
           else
           {
               THROW_EXCEPTION(NoEnoughMemoryException,"NO memory to create to copy object...");
           }

        }
        return *this;
    }
    int length() const
    {
        return m_length;
    }
    void resize(int length)
    {
        if(length != this->m_length)
        {
            T* array = new T[length];
            if(array != nullptr)
            {
                int size = length<m_length?length:m_length;
                for (int i=0;i<size;i++)
                {
                    array[i] = this->m_array[i];
                }
                T* temp = this->m_array;
                this->m_array = array;
                this->m_length = length;
                delete [] temp;
            }
            else {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to resize object...")
            }


        }
    }
    ~DynamicArray()
    {
        delete [] this->m_array;
    }
};

}

#endif // DYNAMICARRAY_H
