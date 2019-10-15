#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H
#include "pointer.h"
namespace DS {

template <typename T>
class SmartPointer: public Pointer<T>
{

public:
    SmartPointer(T* p = nullptr): Pointer<T>(p)
    {

    }

    SmartPointer(const SmartPointer<T>& obj) : Pointer<T>(nullptr)
    {
        this->m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T>&>(obj).m_pointer = nullptr;
    }

    SmartPointer<T>& operator=(const SmartPointer<T>& obj)
    {
        if(this != &obj)
        {
            T* temp = this->m_pointer;
            this->m_pointer = obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer = nullptr;
            delete this->m_pointer;
        }
        return *this;
    }

    ~SmartPointer()
    {
        delete this->m_pointer;
    }
};

}

#endif // SMARTPOINTER_H
