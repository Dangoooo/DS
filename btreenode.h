#ifndef BTREENODE_H
#define BTREENODE_H
#include "treenode.h"
namespace DS {
template<typename T>
class BTreeNode: public TreeNode<T>
{
public:
    BTreeNode<T>* left;
    BTreeNode<T>* right;
    static BTreeNode<T>* NewNode()
    {
        BTreeNode<T>* ret = new BTreeNode<T>();
        if(ret != nullptr)
        {
            ret->m_flag = true;
        }
        return ret;
    }
};


}
#endif // BTREENODE_H
