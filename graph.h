#ifndef GRAPH_H
#define GRAPH_H
#include "object.h"
#include "sharedpointer.h"
#include "array.h"
#include "dynamicarray.h"
#include "linkqueue.h"
#include "linkstack.h"
namespace DS {

template <typename E>
struct Edge : public Object
{
   int b;
   int e;
   E data;

   Edge(int i = -1, int j = -1)
   {
       b = i;
       e = j;
   }

   Edge(int i = -1, int j = -1, const E& value)
   {
       b = i;
       e = j;
       data = value;
   }

   bool operator == (const Edge<E>& obj)
   {
       return ((b = obj.b) && (e = obj.e));
   }
   bool operator != (const Edge<E>& obj)
   {
       return !(*this == obj);
   }
};
template <typename V, typename E>
class Graph : public Object
{
protected:
    template<typename T>
    SharedPointer<Array<T>>* toArray(LinkQueue<T> queue)
    {
        DynamicArray<T>* ret = new DynamicArray<T>(queue.length());
        if(ret != nullptr)
        {
            for (int i = 0; i < ret->length(); i++, queue.remove())
            {
                ret->set(i, queue.front());
            }
        }
        else
        {

        }
        return ret;
    }
public:
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i, V& value) = 0;
    virtual bool setVertex(int i, const V& value) = 0;
    virtual SharedPointer<Array<int>> getAdjacent(int i) = 0;
    virtual E getEdge(int i, int j) = 0;
    virtual bool getEdge(int i, int j, E& value) = 0;
    virtual bool setEdge(int i, int j, const E& value) = 0;
    virtual bool removeEdge(int i, int j) = 0;
    virtual int vCount() = 0;
    virtual int eCount() = 0;
    virtual int OD(int i) = 0;
    virtual int ID(int i) = 0;
    virtual int TD()
    {
        return (OD() + ID());
    }
    SharedPointer<Array<int>> BFS(int i)
    {
        DynamicArray<int>* ret = nullptr;
        if((i >= 0)&&(i < vCount()))
        {
            LinkQueue<int> q;
            LinkQueue<int> r;
            DynamicArray<bool> visited(vCount());
            for (int j = 0; j < visited.length(); j++)
            {
                visited[j] = false;
            }
            q.add(i);
            while (q.length() > 0)
            {
               int v = q.front();
               q.remove();
               if(!visited[v])
               {
                   SharedPointer<Array<int>> aj = getAdjacent(i);
                   for (int j = 0;j < aj->length(); j++)
                   {
                       q.add((*aj)[j]);
                   }
                   r.add(v);
                   visited[v] = true;
               }
            }
            ret = toArray(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid...");
        }
        return ret;
    }
    SharedPointer<Array<int>> DFS(int i)
    {
        DynamicArray<int>* ret = nullptr;
        if((i >= 0)&&(i < vCount()))
        {
            LinkStack<int> s;
            LinkQueue<int> r;
            DynamicArray<bool> visited(vCount());
            for (int j = 0; j < visited.length(); j++)
            {
                visited[j] = false;
            }
            s.push(i);
            while (s.size() > 0)
            {
               int v = s.top();
               s.pop();
               if(!visited[v])
               {
                   SharedPointer<Array<int>> aj = getAdjacent(i);
                   for (int j = 0;j < aj->length(); j++)
                   {
                       s.push((*aj)[j]);
                   }
                   r.add(v);
                   visited[v] = true;
               }
            }
            ret = toArray(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid...");
        }
        return ret;
    }
};

}
#endif // GRAPH_H
