#ifndef TREENODE_H
#define TREENODE_H
#include"object.h"
namespace DS {
template <typename T>
class TreeNode: public Object
{
public:
    T value;
    TreeNode* parent;
    TreeNode()
    {
        parent = nullptr;
    }
    virtual ~TreeNode() = 0;
};
}



#endif // TREENODE_H
