#ifndef BTREE_H
#define BTREE_H
#include "Tree.h"
#include "btreenode.h"
#include "exception.h"
#include "linkqueue.h"
#include "sharedpointer.h"
#include "dynamicarray.h"
namespace DS {
enum BTreePos
{
    ANY,
    LEFT,
    RIGHT
};

enum BTTravelsal
{
    PreOrder,
    InOrder,
    PostOrder,
    LevelOrder
};

template<typename T>
class BTree: public Tree<T>
{
protected:
    LinkQueue<BTreeNode<T>*> m_queue;
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
    virtual bool remove(BTreeNode<T>* node, BTree<T>* ret)
    {
        ret = new BTree<T>();
        if(ret != nullptr)
        {
            if(node == root())
            {
                this->m_root = nullptr;
            }
            else
            {
                BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);
                if(parent->left == node)
                {
                    parent->left = nullptr;
                }
                else if(parent->right)
                {
                    parent->right = nullptr;
                }
                node->parent = nullptr;
            }
            ret->m_root = node;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create a tree...");
        }
        return ret;
    }
    virtual void free(BTreeNode<T>* node)
    {
        if(node != nullptr)
        {
           free(node->left);
           free(node->right);
           if(node->flag())
           {
               delete node;
           }
        }
    }
    int degree(BTreeNode<T>* node) const
    {
        int ret = 0;
        if(node != nullptr)
        {
            ret = !!node->left + !!node->right;
            if(ret < 2)
            {
                int d1 = degree(node->left);
                if(ret < d1)
                {
                    ret = d1;
                }
            }
            if(ret < 2)
            {
                int d2 = degree(node->right);
                if(ret < d2)
                {
                    ret = d2;
                }
            }
        }
        return ret;
    }
    int count(BTreeNode<T>* node) const
    {
        return (node != nullptr) ? (count(node->left)+count(node->right)+1) : 0;
    }
    virtual int height(BTreeNode<T>* node) const
    {
        int ret = 0;
        if(node != nullptr)
        {
            if(height(node->left)>height(node->right))
            {
                ret = height(node->left)+1;
            }
            else
            {
                ret = height(node->right)+1;
            }
        }
        return ret;
    }
    void preOrderTravelsal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != nullptr)
        {
            queue.add(node);
            preOrderTravelsal(node->left, queue);
            preOrderTravelsal(node->right, queue);
        }
    }
    void inOrderTravelsal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != nullptr)
        {
            preOrderTravelsal(node->left, queue);
            queue.add(node);
            preOrderTravelsal(node->right, queue);
        }
    }
    void postOrderTravelsal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != nullptr)
        {
            preOrderTravelsal(node->left, queue);
            preOrderTravelsal(node->right, queue);
            queue.add(node);
        }
    }
    void levelOrderTravelsal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != nullptr)
        {
            LinkQueue<BTreeNode<T>*> temp;
            temp.add(node);
            if(temp.length() > 0)
            {
                BTreeNode<T>* n = temp.front();
                if(n->left)
                {
                    temp.add(n->left);
                }
                if(n->right)
                {
                    temp.add(n->right);
                }
                temp.remove();
                queue.add(n);
            }
        }
    }
    BTreeNode<T>* clone(BTreeNode<T>* node) const
    {
        BTreeNode<T>* ret = nullptr;
        if(node != nullptr)
        {
            ret = BTreeNode<T>::NewNode();
            if(ret != nullptr)
            {
                ret->value = node->value;
                ret->left = clone(node->left);
                ret->right = clone(node->right);
                if(ret->left)
                {
                    ret->left->parent = ret;
                }
                if(ret->right)
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create node...");
            }
        }
        return ret;
    }
    bool equal(BTreeNode<T>* lt, BTreeNode<T>* rt)
    {
        if(lt == rt)
        {
            return true;
        }
        else if(lt != nullptr && rt != nullptr)
        {
            return (lt->value == rt->value) && equal(lt->left, rt->left) && equal(lt->right, rt->right);
        }
        else
        {
            return false;
        }
    }
    BTreeNode<T>* add(BTreeNode<T>* l, BTreeNode<T>* r)
    {
        BTreeNode<T>* ret = nullptr;
        if((l == nullptr) && (r != nullptr))
        {
            ret = clone(r);
        }
        else if((l != nullptr) && (r == nullptr))
        {
            ret = clone(l);
        }
        else if((l != nullptr) && (r != nullptr))
        {
            ret = BTreeNode<T>::NewNode();
            if(ret != nullptr)
            {
                ret->value = l->value + r->value;
                ret->left = add(l->left, r->left);
                ret->right = add(l->right, r->right);
                if(ret->left)
                {
                    ret->left->parent = ret;
                }
                if(ret->right)
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
               THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create node...");
            }

        }
        return ret;
    }
    void travelsal(BTTravelsal order, LinkQueue<BTreeNode<T>*>& queue)
    {
        switch (order)
        {
        case PreOrder:
            preOrderTravelsal(root(), queue);
            break;
        case InOrder:
            inOrderTravelsal(root(), queue);
            break;
        case PostOrder:
            postOrderTravelsal(root(), queue);
            break;
        case LevelOrder:
            levelOrderTravelsal(root(), queue);
            break;
        default:
            THROW_EXCEPTION(InvalidParameterException, "Parameter order is invalid...");
            break;
        }
    }
    BTreeNode<T>* connect(LinkQueue<BTreeNode<T>*>& queue)
    {
        BTreeNode<T>* ret = nullptr;
        if(queue.length() > 0)
        {
            ret = queue.front();
            BTreeNode<T>* slider = queue.front();
            slider->left = nullptr;
            queue.remove();
            while(queue.length() > 0)
            {
                slider->right = queue.front();
                queue.front()->left = slider;
                slider = queue.front();
                queue.remove();
            }
            slider->right = nullptr;
        }
        return nullptr;
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
       return insert(value, parent, ANY);
    }
    SmartPointer<Tree<T>> remove(const T& value)
    {
        BTree<T>* ret = nullptr;
        BTreeNode<T>* node = find(value);
        if(node != nullptr)
        {
            remove(node, ret);
            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "cannot find a node via value...");
        }
        return ret;
    }
    SmartPointer<Tree<T>> remove(TreeNode<T>* node)
    {
        BTree<T>* ret = nullptr;
        node = find(node);
        if(node != nullptr)
        {
            remove(dynamic_cast<BTreeNode<T>*>(node), ret);
            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid...");
        }
        return ret;
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
        return degree(root());
    }
    int count() const
    {
        return count(root());
    }
    int height() const
    {
        return count(root());
    }
    bool begin()
    {
        bool ret = (root() != nullptr);
        if(ret)
        {
            m_queue.clear();
            m_queue.add(root());
        }
        return ret;
    }
    bool end()
    {
        bool ret = (m_queue.length() == 0);
        return ret;
    }
    bool next()
    {
        bool ret = (m_queue.length() > 0);
        if(ret)
        {
            BTreeNode<T>* node = m_queue.front();
            m_queue.remove();
            if(node->left != nullptr)
            {
                m_queue.add(node->left);
            }
            if(node->right != nullptr)
            {
                m_queue.add(node->right);
            }
        }
        return ret;
    }
    T current()
    {
        if(!end())
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "cannot get the curren value...");
        }

    }
    SharedPointer<Array<T>> Travelsal(BTTravelsal order)
    {
        DynamicArray<T>* ret = nullptr;
        LinkQueue<BTreeNode<T>*> queue;
        travelsal(order, queue);
        ret = new DynamicArray<T>(queue.length());
        if(ret != nullptr)
        {
            for (int i = 0; i < ret->length(); i++, queue.remove())
            {
                ret->set(i, queue.front()->value);
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create array...");
        }
        return ret;
    }
    SharedPointer<BTree<T>> clone() const
    {
        BTree<T>* ret = new BTree<T>();
        if(ret != nullptr)
        {
            ret->m_root = clone(root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create btree...");
        }
        return ret;
    }
    bool operator == (BTree<T>& btree)
    {
        return equal(root(), btree.root());
    }
    bool operator != (BTree<T>& btree)
    {
        return !(*this == btree);
    }
    SharedPointer<BTree<T>> add(BTree<T>& btree)
    {
        BTree<T>* ret = new BTree<T>();
        if(ret != nullptr)
        {
            ret->m_root = add(root(), btree.root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create btree...");
        }
        return ret;
    }
    BTreeNode<T>* thread(BTTravelsal order)
    {
        BTreeNode<T>* ret = nullptr;
        LinkQueue<BTreeNode<T>*> queue;
        travelsal(order, queue);
        ret = connect(queue);
        this->m_root = nullptr;
        m_queue.clear();
        return ret;
    }
    void clear()
    {
        free(root());
        m_queue.clear();
        this->m_root = nullptr;
    }
};
}
#endif // BTREE_H
