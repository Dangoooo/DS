#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H
#include "graph.h"
#include "exception.h"
#include "dynamicarray.h"
namespace DS {

template <int N, typename V, typename E>
class MatrixGraph : public Graph<V, E>
{
protected:
    V* m_vertexes[N];
    E* m_edges[N][N];
    int m_eCount;
public:
    MatrixGraph()
    {
        for (int i = 0; i < vCount(); i++)
        {
            m_vertexes[i] = nullptr;
            for (int j = 0; j < vCount(); j++)
            {
                m_edges[i][j] = nullptr;
            }
        }
    }

    V getVertex(int i)
    {
        V ret;
        if(!getVertex(i, ret))
        {
            THROW_EXCEPTION(InvalidOperationException, "Cannot find a value via i...");
        }
        return ret;
    }

    bool getVertex(int i, V& value)
    {
        bool ret = ((i >= 0) && (i < vCount()));
        if(ret)
        {
            if(m_vertexes[i] != nullptr)
            {
                value = *(m_vertexes[i]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "Cannot find a value via i...");
            }
        }
        return ret;
    }

    bool setVertex(int i, const V& value)
    {
        bool ret = ((i >= 0) && (i < vCount()));
        if(ret)
        {
            V* data = m_vertexes[i];
            if(data == nullptr)
            {
                data = new V();
            }

            if(data != nullptr)
            {
                *data = value;
                m_vertexes[i] = data;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "Cannot find a value via i...");
            }
        }
        return ret;
    }

    SharedPointer<Array<int>> getAdjacent(int i)
    {
        DynamicArray<int>* ret = nullptr;
        if((i >= 0) && (i < vCount()))
        {
            int n = 0;
            for (int j = 0; j < vCount(); j++)
            {
                if(m_edges[i][j] != nullptr)
                {
                    n++;
                }
                ret = new DynamicArray<int>(n);
                if(ret)
                {
                    for (int j = 0,k = 0; j < vCount(); j++)
                    {
                        if(m_edges[i][j] != nullptr)
                        {
                            ret->set(k++, j);
                        }
                    }
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create a array...");
                }
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
            THROW_EXCEPTION(InvalidParameterException, "Parameter is invalid...");
        }
        return ret;
    }

    bool getEdge(int i, int j, E& value)
    {
        bool ret =((i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount()));
        if(ret)
        {
            if(m_edges[i][j] != nullptr)
            {
                value = *(m_edges[i][j]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "Cannot find a value via i...");
            }
        }
        return ret;
    }

    bool setEdge(int i, int j, const E& value)
    {
        bool ret =((i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount()));
        if(ret)
        {
            E* ne = m_edges[i][j];
            if(ne == nullptr)
            {
                ne = new E();
                if(ne != nullptr)
                {
                    *ne = value;
                    m_edges[i][j] = ne;
                    m_eCount++;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create E...");
                }
            }
            else
            {
                *ne = value;
                m_edges[i][j] = ne;
            }
        }
        return ret;
    }

    bool removeEdge(int i, int j)
    {
        bool ret =((i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount()));
        if(ret)
        {
            E* toDel = m_edges[i][j];
            m_edges[i][j] = nullptr;
            if(toDel != nullptr)
            {
                delete toDel;
                m_eCount--;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter is in valid...");
        }
        return ret;
    }

    int vCount()
    {
        return N;
    }

    int eCount()
    {
        return m_eCount;
    }

    int OD(int i)
    {
        int ret = 0;
        if((i >= 0) && (i < vCount()))
        {
            for (int j = 0; j < vCount(); j++)
            {
                if(m_edges[i][j] != nullptr)
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid...");
        }
    }

    int ID(int i)
    {
        int ret = 0;
        if((i >= 0) && (i < vCount()))
        {
            for (int j = 0; j < vCount(); j++)
            {
                if(m_edges[j][i] != nullptr)
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid...");
        }
    }

    ~MatrixGraph()
    {
        for (int i = 0; i < vCount(); i++)
        {
            delete m_vertexes[i];
            for (int j = 0; j < vCount(); j++)
            {
                delete m_edges[i][j];
            }
        }
    }
};

}
#endif // MATRIXGRAPH_H
