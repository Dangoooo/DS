#ifndef LISTGRAPH_H
#define LISTGRAPH_H
#include "graph.h"
#include "linklist.h"
#include "exception.h"
#include "dynamicarray.h"
namespace DS {

template <typename V, typename E>
class ListGraph : public Graph<V, E>
{
protected:
    struct Vertex : public Object
    {
        V* data;
        LinkList<Edge<E>> edge;
        Vertex()
        {
            data = nullptr;
        }
    };

    LinkList<Vertex*> m_list;
public:
    ListGraph(unsigned int n = 0)
    {
        for (unsigned int i = 0; i < n; i++)
        {
           addVertex();
        }
    }

    int addVertex()
    {
        int ret = -1;
        Vertex* v = new Vertex();
        if(v != nullptr)
        {
            m_list.insert(v);
            ret = m_list.length() - 1;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create a vertex...");
        }
        return ret;
    }

    int addVertex(const V& value)
    {
        int ret = addVertex();
        if( ret >= 0)
        {
            setVertex(ret, value);
        }
        return ret;
    }

    bool setVertex(int i, const V* value)
    {
        bool ret = ((i >= 0) && (i < vCount()));
        if(ret)
        {
            Vertex* vertex = m_list.get(i);
            V* data = vertex->data;
            if(data != nullptr)
            {
                data = new V();
            }

            if(data != nullptr)
            {
                *data = value;
                vertex->data = data;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create a vertex...");
            }
        }
        return ret;
    }

    V getVertex(int i)
    {
        V ret;
        if(!getVertex(i, ret))
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid...");
        }
        return ret;
    }

    bool getVertex(int i, const V& value)
    {
        bool ret = ((i >= 0) && (i < vCount()));
        if(ret)
        {
            Vertex* vertex = m_list.get(i);
            if(vertex->data != nullptr)
            {
                value = *(vertex->data);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "Cannot get the vertex via i...");
            }
        }
        return ret;
    }

    void removeVertex()
    {
        if(m_list.length() > 0)
        {
            int index = m_list.length() - 1;
            Vertex* v = m_list.get(index);
            if(m_list.remove(index))
            {
                int i = 0;
                for (m_list.move(0); !m_list.end(); m_list.next())
                {
                    int pos = m_list.current()->edge.find(Edge<E>(i, index));
                    if(pos >= 0)
                    {
                        m_list.current()->edge.remove(pos);
                    }
                    i++;
                }
                delete v->data;
                delete v;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No vertex in current graph...");
        }
    }
    
    SharedPointer<Array<int>> getAdjacent(int i)
    {
        DynamicArray<int>* ret = nullptr;
        if((i >= 0) && (i < vCount()))
        {
            Vertex* v = m_list.get(i);
            if(v != nullptr)
            {
               ret = new DynamicArray<int>(v->edge.length());
               if(ret != nullptr)
               {
                   int k = 0;
                   for(v->edge.move(0); !v->edge.end(); v->edge.next())
                   {
                       ret->set(k++, v->edge.current().e);
                   }
               }
               else 
               {
                   THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create a array...");
               }
            }
            else 
            {
                THROW_EXCEPTION(InvalidOperationException, "Cannot get the adjacentVertex via i...");
            }
        }
        else 
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid...");
        }
        return ret;
    }
    
    E getEdge(int i, int j)
    {
        E ret;
        if(!getEdge(i, j, ret))
        {
            THROW_EXCEPTION(InvalidOperationException, "Cannot get the E via...");
        }
        return ret;
    }
    
    bool getEdge(int i, int j, E& value)
    {
        int ret = ((i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount()));
        if(ret)
        {
            Vertex* v = m_list.get(i);
            int pos = v->edge.find(Edge<E>(i, j));
            if(pos >= 0)
            {
                value = v->edge.get(pos).data;
            }
            else 
            {
                THROW_EXCEPTION(InvalidOperationException, "Cannot get the pos via...");
            }
        }
        return ret;
    }
    
    bool setEdge(int i, int j, const E& value)
    {
        int ret = ((i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount()));
        if(ret)
        {
            Vertex* v = m_list.get(i);
            int pos = v->edge.find(Edge<E>(i, j));
            if(pos >= 0)
            {
                ret = v->edge.set(pos, Edge<E>(i, j, value));
            }
            else 
            {
                ret = v->edge.insert(0, Edge<E>(i, j, value));
            }
        }
        return ret;
    }
    
    bool removeEdge(int i, int j)
    {
        bool ret = ((i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount()));
        if(ret)
        {
            Vertex* v = m_list.get(i);
            int pos = v->edge.find(Edge<E>(i, j));
            if(pos >= 0)
            {
                ret = v->edge.remove(pos);
            }
        }
        return ret;
    }
    
    int vCount()
    {
        return m_list.length();
    }

    int eCount()
    {
        int ret = 0;
        for (m_list.move(0); !m_list.end(); m_list.next())
        {
            ret += m_list.current().edge.length();
        }
        return ret;
    }

    int ID(int i)
    {
        int ret = 0;
        if((i >= 0) && (i < vCount()))
        {
            for (m_list.move(0); !m_list.end(); m_list.next())
            {
                LinkList<Edge<E>>& edge = m_list.current();
                for(edge.move(0); !edge.end(); edge.next())
                {
                    if(edge.current().e == i)
                    {
                        ret++;
                        break;
                    }
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid...");
        }
        return ret;
    }

    int OD(int i)
    {
        int ret = 0;
        if((i >= 0) && (i < vCount()))
        {
            ret = m_list.get(i)->edge.length();

        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid...");
        }
        return ret;
    }

    ~ListGraph()
    {
        while(m_list.length() > 0)
        {
            Vertex* toDel = m_list.get(0);
            m_list.remove(0);
            delete toDel->data;
            delete toDel;
        }
    }
};

}
#endif // LISTGRAPH_H
