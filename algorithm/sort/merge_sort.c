#include<stdio.h>
#include <string.h>
#define TYPE int
#define N 20
void merge_sort(TYPE *array,int start,int end);
void merge(TYPE *array,TYPE *tempArray,int start,int middle,int end);
void print_array(TYPE *array,int length);
int main()
{
    static TYPE A[N] = {5,6,7,8,9,2,3,4,5,6,1,2,3,4,5,6};
    static temp[N];
    int length = 16;
    int start = 0,end = length-1;
    int middle = (start + end) / 2;
    merge_sort(A,0,end);
    print_array(A,length);
    return 0;
}
void print_array(TYPE *array,int length)
{
    int i;
    for(i = 0; i < length; ++i)
    {
        printf("%d ",array[i]);
    }
    printf("\n");
}
void merge(TYPE *array,TYPE *tempArray,int start,int middle,int end)
{
    int a_index = start;
    int t_index = middle + 1;
    int i = 0;
//    printf("%d %d %d\n",a_index,middle,t_index);
    while(a_index <= middle && t_index <= end)
    {
//        printf("inner left %d right %d == ",array[a_index],array[t_index]);
        if(array[a_index] >= array[t_index])
        {
            tempArray[i++] = array[t_index++];
        }
        else
        {
            tempArray[i++] = array[a_index++];
        }
//        printf("temparray %d\n",tempArray[i-1]);
    }
    while(a_index <= middle)
    {
        tempArray[i++] = array[a_index++];
    }
    while(t_index <= end)
    {
        tempArray[i++] = array[t_index++];
    }
//    printf("============\n");
//    print_array(tempArray,N);
//    print_array(array,N);
//    printf("============\n");
    memcpy(array+start,tempArray,sizeof(TYPE)*(end-start+1));
//    print_array(array,N);
}
void merge_sort(TYPE *array,int start,int end)
{
    if(start >= end)
    {
        return ;
    }
    static temp[N];
    int middle = (start+ end) / 2;
    merge_sort(array,start,middle);
    merge_sort(array,middle+1,end);
    merge(array,temp,start,middle,end);
}
