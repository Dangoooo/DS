#ifndef DYNAMICLINKLIST_H
#define DYNAMICLINKLIST_H
#include "linklist.h"
namespace DS {
template <typename T, int N>
class DynamicLinkList: public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;
    unsigned char m_space[sizeof (Node)*N];
    int m_used[N];
    Node* create()
    {

    }
    void destroy(Node* p)
    {

    }
};
}
#endif // DYNAMICLINKLIST_H
