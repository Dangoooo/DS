#include <iostream>
#include "dstring.h"
#include "sort.h"
#include "gtree.h"
using namespace DS;
using namespace std;


int main()
{
    /*int a[] = {4,9,5,6,3,7,8,10};
    Sort::Bead(a, 8);

    for(int i=0; i<8; i++)
    {
        cout<<a[i]<<endl;
    }*/

   GTreeNode<char>* tn = nullptr;
   GTree<char> t;
   t.insert('A', nullptr);
   tn = t.find('A');

   t.insert('B', tn);

   tn = t.find('B');

   cout<<tn->value<<endl;
   cout<<t.count()<<endl;
   cout<<t.height()<<endl;
   cout<<t.degree()<<endl;










    return 0;
}

