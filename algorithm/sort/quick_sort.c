#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "print_array.h"
#define N 20

int partition(TYPE *array,int low,int high);
int getRandomIndex(low,high);
void quickSort(TYPE *array,int start,int end);
int main()
{

    TYPE array[] = {5,2,34,5,-1,0,-5,9,123,6,4,3,9,0};
    quickSort(array,0,13);
    print_array(array,14);

    return 0;
}
int getRandomIndex(low,high)
{
    return rand()%(high-low+1)+low;
}
void swap(TYPE *a, TYPE *b)
{
    TYPE temp = *a;
    *a = *b;
    *b = temp;
}
int partition(TYPE *array,int low,int high)
{
    /**
      * partion的调用包括low~high，闭区间array[low,high]
      * 1、初始partition_index为low，iter为初始partition_index+1
      * 2、从(0,partition_index]为比base小的数
      * 3、当L[iter_index] < base的时候，则partition_index+1，
      * 使(0,partition_index]增长1
      * 4、交换L[iter_index] 和 L[partition_index]使数组依然满足步骤2的性质
      * 5、遍历,直到iter再小于high
      * 6、最后将L[0]与L[partition_index]交换，
      * 使L[0,partition_index]都<=L[partition_index]
      *
      **/

    if(high <= low)
    {
        return low;
    }
    TYPE base = array[low];
    TYPE temp;
    int p=low, iter=p+1;
    while(iter <= high)
    {
        if(array[iter]<base)
        {
            ++p;
            swap(&array[p],&array[iter]);
        }
        ++iter;
    }
    swap(&array[low],&array[p]);
    return p;
}
int randomPartition(TYPE *array,int low,int high)
{
    if(high <= low)
    {
        return low;
    }
    int random_index = getRandomIndex(low,high);
    swap(&array[low],&array[random_index]);
    return partition(array,low,high);
}
void quickSort(TYPE *array,int start,int end)
{
    if(start < end)
    {
        int p = randomPartition(array,start,end);
        quickSort(array,start,p);
        quickSort(array,p+1,end);
    }
}
