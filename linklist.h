#ifndef LINKLIST_H
#define LINKLIST_H
#include "list.h"
#include "object.h"
#include "exception.h"
namespace DS {
template <typename T>
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };
     int m_length;
     mutable Node m_header;
     Node* m_current;
     int m_step;
     virtual Node* create()
     {
         return new Node();
     }
     virtual void destroy(Node* p)
     {
         delete p;
     }
public:
    LinkList()
    {
        m_length = 0;
        m_header.next = nullptr;
        m_current = nullptr;
        m_step = 1;
    }
    bool insert(int i, const T& e)
    {
        bool ret = (i>=0&&i<=m_length);
        if(ret)
        {
            Node* node = create();
            if(node != nullptr)
            {
                Node* current = &m_header;
                if(current != nullptr)
                {
                    for(int p=0;p<i;p++)
                    {
                        current = current->next;
                    }
                    node->value = e;
                    node->next = current->next;
                    current->next = node;
                    m_length++;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create Node...");
            }
        }
        return ret;
    }
    bool insert(const T& e)
    {
        return insert(m_length, e);
    }
    bool remove(int i)
    {
        bool ret = (i>=0&&i<m_length);
        if(ret)
        {
            Node* current = &m_header;
            for(int p=0;p<i;p++)
            {
                current = current->next;
            }
            Node* toDel = current->next;
            if(m_current == toDel)
            {
                m_current = toDel->next;
            }
            current->next = toDel->next;
            destroy(toDel);
            m_length--;
        }
        return ret;
    }
    virtual T get(int i) const
    {
        T ret;

        if(get(i, ret))
        {
            return ret;
        }
        else {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
        }
    }
    bool get(int i, T& e) const
    {
        bool ret = (i>=0&&i<m_length);
        if(ret)
        {
            Node* current = &m_header;
            for(int p=0;p<i;p++)
            {
                current = current->next;
            }
            e = current->next->value;
        }
        return ret;
    }
    bool set(int i, const T& e)
    {
        bool ret = (i>=0&&i<m_length);
        if(ret)
        {
            Node* current = &m_header;
            for(int p=0;p<i;p++)
            {
                current = current->next;
            }
            current->next->value = e;
        }
        return ret;
    }
    int find(const T& e) const
    {
        Node* node = m_header.next;
        int i = 0;
        while (node)
        {
           if(node->value == e)
           {
               return i;
           }
           node = node->next;
           i++;
        }
        return -1;
    }
    int length() const
    {
        return m_length;
    }
    void clear()
    {
        while (m_header.next)
        {
            Node* toDel = m_header.next;
            m_header.next = toDel->next;
            destroy(toDel);
        }
        m_length = 0;
        m_current = nullptr;
    }
    virtual bool move(int i, int step = 1)
    {
        bool ret = (i>=0&&i<m_length&&step>0);
        if(ret)
        {
            Node* current = &m_header;
            for(int p=0;p<i;p++)
            {
                current = current->next;
            }
            m_current = current->next;
            m_step = step;
        }
        return ret;
    }
    virtual bool end()
    {
        return (m_current == nullptr);
    }
    virtual T current()
    {
        if(!end())
        {
           return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position...");
        }
    }
    virtual bool next()
    {
        int i = 0;
        while (i<m_step&&!end())
        {
            m_current = m_current->next;
            i++;
        }
        return (i==m_step);
    }
    ~LinkList()
    {
        clear();
    }
};

}
#endif // LINKLIST_H
