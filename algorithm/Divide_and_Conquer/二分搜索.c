#include<stdio.h>
#include<windows.h>
#define N 100
int binary_search(int *array,int key,int len)
{
    int mid,low = 0,high = len;
    while(low <= high)
    {
        mid = (low + high)/2;
        //printf("***low=%d high=%d mid=%d***\n",low,high,mid);
        if(array[mid] == key)
        {
            return mid;
        }
        else if(array[mid] < key)
        {

            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }

    }
    return -1;
}
void init_array(int *array,int len)
{
    int i;
    for(i = 0; i < len; ++i)
    {
        array[i] = i;
    }
}
void print_array(int *array,int len)
{
    int i;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
    FOREGROUND_RED);
    for(i = 0; i < len; ++i)
    {
        printf("%d ",array[i]);
    }
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void print_reslut(int key,int local)
{
    printf("search ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
    FOREGROUND_RED);
    printf("%d",key);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf(":local ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
    FOREGROUND_RED | FOREGROUND_BLUE);
    printf("%d\n",local);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void test_lots()
{
    int a[N],i;
    int local,key;
    init_array(a,N);
    print_array(a,N);
    for(i = 0; i < N/5; ++i)
    {
        key = i * 2 + 1;
        print_reslut(key,binary_search(a,key,N));
    }
}
void test_one()
{
    int a[N];
    init_array(a,N);
    print_array(a,N);
    print_reslut(63,binary_search(a,63,N));
}
int main()
{
//    test_one();
    test_lots();
    return 0;
}
