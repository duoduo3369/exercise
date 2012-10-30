#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define TYPE int
#define N 20

int partition(TYPE *array,int low,int high);
int getRandomIndex(low,high);
srand((unsigned)time(NULL));
int main()
{
    int i;
    for(i = 0;i < 8; i++)
    {
        printf("%d \n",getRandomIndex(5,9));
    }
    return 0;
}
int getRandomIndex(low,high)
{

    return rand()%(high-low+1)+low;
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
int partition(TYPE *array,int low,int high)
{
    if(high - low <= 1)
    {
        return low;
    }
    TYPE base = 0;
    return 1;
}
void quickSort(TYPE *array,int start,int end)
{
    if(start < end)
    {
        int p = partition(array,start,end);
        quickSort(array,start,p);
        quickSort(array,p+1,end);
    }
}
