#ifndef GTREENODE_H
#define GTREENODE_H
#include "treenode.h"
#include "linklist.h"
namespace DS {
template<typename T>
class  GTreeNode: public TreeNode<T>
{
protected:

public:
    LinkList<GTreeNode<T>*> child;
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
