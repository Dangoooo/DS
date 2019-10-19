#ifndef BTREE_H
#define BTREE_H
#include "Tree.h"
#include "btreenode.h"
#include "exception.h"
#include "linkqueue.h"
namespace DS {
enum BTreePos
{
    ANY,
    LEFT,
    RIGHT
};

template<typename T>
class BTree: public Tree<T>
{
protected:
    virtual BTreeNode<T>* find(BTreeNode<T>* node, T value) const
    {
        BTreeNode<T>* ret = nullptr;
        if(node != nullptr)
        {
          if(node->value == value)
          {
              ret = node;
          }
          else
          {
              if(ret == nullptr)
              {
                  ret = find(node->left, value);
              }
              if(ret == nullptr)
              {
                  ret = find(node->right, value);
              }
          }
        }
        return ret;
    }
    virtual BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj) const
    {
        BTreeNode<T>* ret = nullptr;
        if(node != nullptr)
        {
            if(node == obj)
            {
                ret = node;
            }
            else
            {
                if(ret == nullptr)
                {
                    ret = find(node->left, obj);
                }
                if(ret == nullptr)
                {
                    ret = find(node->right, obj);
                }
            }
        }
        return ret;
    }
    virtual bool insert(BTreeNode<T>* node, BTreeNode<T>* parent, BTreePos pos)
    {
        bool ret = true;
        if(pos == ANY)
        {
            if(parent->left == nullptr)
            {
                parent->left = node;
            }
            else if(parent->right == nullptr)
            {
                parent->right = node;
            }
            else
            {
                ret = false;
            }
        }
        else if(pos == LEFT)
        {
            if(parent->left == nullptr)
            {
                parent->left = node;
            }
            else
            {
                ret = false;
            }
        }
        else if(pos == RIGHT)
        {
            if(parent->right == nullptr)
            {
                parent->right = node;
            }
            else
            {
                ret = false;
            }
        }
        else
        {
           ret = false;
        }
        return ret;
    }
public:
    virtual bool insert(TreeNode<T>* node, BTreePos pos)
    {
        bool ret = true;
        if(node != nullptr)
        {
            if(this->m_root == nullptr)
            {
                this->m_root = node;
                node->parent = nullptr;
            }
            else
            {
                BTreeNode<T>* np = find(node->parent);
                if(np != nullptr)
                {
                    ret = insert(dynamic_cast<BTreeNode<T>*>(node), np, pos);
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Parameter node is incorrect...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node cannot be null...");
        }
        return ret;
    }
    bool insert(TreeNode<T>* node)
    {
        return insert(node, ANY);
    }
    virtual bool insert(const T& value, TreeNode<T>* parent, BTreePos pos)
    {
        bool ret = true;
        BTreeNode<T>* node = BTreeNode<T>::NewNode();
        if(node != nullptr)
        {
            node->value = value;
            node->parent = parent;
            ret = insert(node, pos);
            if(!ret)
            {
                delete node;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create node...");
        }
        return ret;
    }
    bool insert(const T& value, TreeNode<T>* parent)
    {
       insert(value, parent, ANY);
    }
    SmartPointer<Tree<T>> remove(const T& value)
    {
        return nullptr;
    }
    SmartPointer<Tree<T>> remove(TreeNode<T>* node)
    {
        return nullptr;
    }
    BTreeNode<T>* find(const T& value)
    {
        return find(root(), value);
    }
    BTreeNode<T>* find(TreeNode<T>* node)
    {
        return find(root(), dynamic_cast<BTreeNode<T>*>(node));
    }
    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
    }
    int degree() const
    {
        return 0;
    }
    int count() const
    {
        return 0;
    }
    int height() const
    {
        return 0;
    }
    void clear()
    {

    }
};
}
#endif // BTREE_H
