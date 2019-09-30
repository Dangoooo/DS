#include <iostream>
#include "dstring.h"
#include "sort.h"
using namespace DS;
using namespace std;


int main()
{
    int a[] = {4,9,5,6,3,7,8,10};
    Sort::Bead(a, 8);

    for(int i=0; i<8; i++)
    {
        cout<<a[i]<<endl;
    }

    return 0;
}

