#include <iostream>
#include "dstring.h"
#include "sort.h"
#include "sharedpointer.h"
#include "smartpointer.h"
using namespace DS;
using namespace std;

class Test
{
public:
    int value;
    Test(int i = 0): value(i)
    {
        cout<<"test"<<endl;
    }
    ~Test()
    {
        cout<<"~test"<<endl;
    }
};

int main()
{
   /*int a[] = {4,9,5,6,3,7,8,10};
    Sort::Bead(a, 8);

    for(int i=0; i<8; i++)
    {
        cout<<a[i]<<endl;
    }*/
    SharedPointer<Test> sp1 = new Test();
    cout<<sp1.isNull()<<endl;
    sp1->value = 5;
    SharedPointer<Test> sp2(sp1);
    cout<<sp2->value<<endl;
    cout<<(sp1==sp2)<<endl;


    return 0;
}

