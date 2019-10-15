#ifndef GTREE_H
#define GTREE_H
#include "Tree.h"
#include "gtreenode.h"
#include "exception.h"
namespace DS {
template<typename T>
class GTree: public Tree<T>
{
protected:
    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const
    {
        GTreeNode<T>* ret = nullptr;
        if(node != nullptr)
        {
            if(node->value == value)
            {
                return node;
            }
            else
            {
                for(node->child.move(0); !(node->child.end()) && (ret == nullptr); node->child.next())
                {
                   ret = find(node->child.current(), value);
                }
            }
        }
        return  ret;
    }

    GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj) const
    {
        GTreeNode<T>* ret = nullptr;
        if(node == obj)
        {
            return node;
        }
        else
        {
            if(node != nullptr)
            {
                for(node->child.move(0); !node->child.end() && (ret == nullptr); node->child.next())
                {
                    ret = find(node->child.current(), obj);
                }
            }
        }
        return ret;
    }

    void free(GTreeNode<T>* node)
    {
        if(node != nullptr)
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                free(node->child.current());
            }
            if(node->flag() != false)
            {
                delete node;
            }
        }

    }
public:
    bool insert(TreeNode<T>* node)
    {
        bool ret = true;
        if(node != nullptr)
        {
            if(this->m_root == nullptr)
            {
                node->parent = nullptr;
                this->m_root = node;

            }
            else
            {
                GTreeNode<T>* np = find(node->parent);
                if(np != nullptr)
                {
                    GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);
                    if(np->child.find(n) < 0)
                    {
                        np->child.insert(n);
                    }
                }
                else
                {
                     THROW_EXCEPTION(InvalidOperationException, "Invalid parent tree node...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is null...");
        }

        return  ret;
    }
    bool insert(const T& value, TreeNode<T>* parent)
    {
        bool ret = true;
        GTreeNode<T>* node = GTreeNode<T>::NewNode();
        if(node != nullptr)
        {
            node->value = value;
            node->parent = parent;
            insert(node);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create a tree node...");
        }
        return  ret;
    }
    SmartPointer<Tree<T>> remove(const T& value)
    {
        return  nullptr;
    }
    SmartPointer<Tree<T>> remove(TreeNode<T>* parent)
    {
        return  nullptr;
    }
    GTreeNode<T>* find(const T& value)
    {
        return find(root(), value);
    }
    GTreeNode<T>* find(TreeNode<T>* node)
    {
        return  find(root(), dynamic_cast<GTreeNode<T>*>(node));
    }
    GTreeNode<T>* root()
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }
    int degree() const
    {
        return 0;
    }
    int count() const
    {
        return  0;
    }
    int height() const
    {
        return 0;
    }
    void clear()
    {
        free(root());
        this->m_root = nullptr;
    }
    ~GTree()
    {
       clear();
    }
};
}
#endif // GTREE_H
