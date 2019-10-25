#include <iostream>
#include "dstring.h"
#include "sort.h"
#include "btree.h"
#include <ctime>
#include <cstdlib>
#include "dynamicarray.h"
using namespace DS;
using namespace std;


int main()
{

    /*int array[10000];
    int a[10000];
    srand((unsigned)time(nullptr));
    clock_t start1,end1;
    clock_t start2,end2;
    for (int i = 0; i < 10000; i++)
    {
        array[i] = (rand()%20)+1;
    }
    for (int i =0; i < 10000; i++)
    {
        a[i] = array[i];
    }
    start1 = clock();
    Sort::Bead(array, 10000);
    end1 = clock();

    start2 = clock();
    Sort::Quick(a, 10000);
    end2 = clock();

    for(int i=0; i<10000; i++)
    {
        cout<<array[i]<<" ";
    }
    cout<<endl;
    cout<<"Bead Sort:"<<double(end1-start1)/CLOCKS_PER_SEC<<endl;
    system("pause");

    for(int i=0; i<10000; i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    cout<<"Quick Sort:"<<double(end2-start2)/CLOCKS_PER_SEC<<endl;*/

   BTreeNode<char>* tn = nullptr;
   BTree<char> t;
   t.insert('A', nullptr);
   tn = t.find('A');
   cout<<tn->value<<endl;
   t.insert('B', tn);

   tn = t.find('B');
   cout<<tn<<endl;

   cout<<tn->value<<endl;
   cout<<t.count()<<endl;
   cout<<t.height()<<endl;
   cout<<t.degree()<<endl;

   for(t.begin(); !t.end(); t.next())
   {
       cout<<t.current()<<" ";
   }
   cout<<endl;
   SharedPointer<BTree<char>> s = t.clone();
   for(s->begin(); !s->end(); s->next())
   {
       cout<<s->current()<<" ";
   }
   cout<<endl;
   SharedPointer<Array<char>> sp = nullptr;
   cout<< (t == (*s))<<endl;
   sp = t.Travelsal(InOrder);
   for(int i = 0; i < sp->length(); i++)
   {
       cout<<(*sp)[i]<<endl;
   }












    return 0;
}

