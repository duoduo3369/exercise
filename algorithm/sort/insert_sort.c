#include<stdio.h>
#include "print_array.h"
int insertSort(TYPE *array,int length)
{
    int start = 0,iter = start+1;
    int i,compare_number;
    while(iter < length)
    {
        start = 0;
        compare_number = array[iter];
        while(start<iter)
        {
            if(array[start] > compare_number)
            {
                break;
            }
            start++;
        }
        if(start < iter)
        {
            for(i = iter;i > start;i--)
            {
                array[i] = array[i-1];
            }
            array[start] = compare_number;
        }
        iter++;
    }
}
int main()
{
    static TYPE A[] = {5,6,7,8,9,2,3,4,5,6,1,2,3,4,5,6};
    int length = 16;
    int start = 0,end = length-1;
    insertSort(A,length);
    print_array(A,length);
    return 0;
}
