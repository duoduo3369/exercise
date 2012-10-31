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
      * partion�ĵ��ð���low~high��������array[low,high]
      * 1����ʼpartition_indexΪlow��iterΪ��ʼpartition_index+1
      * 2����(0,partition_index]Ϊ��baseС����
      * 3����L[iter_index] < base��ʱ����partition_index+1��
      * ʹ(0,partition_index]����1
      * 4������L[iter_index] �� L[partition_index]ʹ������Ȼ���㲽��2������
      * 5������,ֱ��iter��С��high
      * 6�����L[0]��L[partition_index]������
      * ʹL[0,partition_index]��<=L[partition_index]
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
