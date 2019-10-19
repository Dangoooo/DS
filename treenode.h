#ifndef TREENODE_H
#define TREENODE_H
#include"object.h"
namespace DS {
template <typename T>
class TreeNode: public Object
{
protected:
    bool m_flag;
    TreeNode(const TreeNode<T>&);
    TreeNode<T>& operator=(const TreeNode<T>&);
    void* operator new(unsigned long long size)
    {
        return Object::operator new(size);
    }
public:
    T value;
    TreeNode* parent;
    TreeNode()
    {
        m_flag = false;
        parent = nullptr;
    }
    bool flag()
    {
        return m_flag;
    }
    virtual ~TreeNode() = 0;
};

template <typename T>
TreeNode<T>::~TreeNode()
{

}
}



#endif // TREENODE_H
