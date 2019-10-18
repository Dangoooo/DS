#ifndef GTREENODE_H
#define GTREENODE_H
#include "treenode.h"
#include "linklist.h"
namespace DS {
template<typename T>
class  GTreeNode: public TreeNode<T>
{
protected:
    bool m_flag;
    GTreeNode(const GTreeNode<T>&);
    GTreeNode<T>& operator=(const GTreeNode<T>&);
    void* operator new(unsigned long long size)
    {
        return Object::operator new(size);
    }
public:
    LinkList<GTreeNode<T>*> child;
    GTreeNode()
    {
        m_flag = false;
    }

    bool flag()
    {
        return m_flag;
    }

    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret = new GTreeNode<T>();
        if(ret != nullptr)
        {
            ret->m_flag = true;
        }
        return ret;
    }
};
}
#endif // GTREENODE_H
