
#include  <iostream>
#include <vector>
using namespace std;

template<class Type>
void permutation(Type array[],int first,int last)
{
    if(first == last)
    {
        for( int i = 0; i < last ; ++i )
        {
            cout << array[i] << " ";
        }
        cout << endl;

    }
    else
    {
        for( int i = first; i < last ; ++i )
        {
            swap(array[first],array[i]);
            permutation(array,first+1,last);
            swap(array[first],array[i]);
        }

    }
}
template<class Type>
void swap(Type &a,Type &b)
{
    Type temp = a;
    a = b;
    b = temp;
}


int main(int argc, char *argv[])
{
    int a[4] = {1,2,3,4};
    permutation(a,0,4);
    char b[4] = {'a','b','c','d'};
    permutation(b,0,4);
    return 0;
}
