/**
 * 平面的最近点对问题
 * 1、将点集合按照x，y轴递增的顺序排列(x为主)
 * 2、找出中线L将S划分为SL和SR
 * 3、将步骤2递归的应用解决SL和SR的最近点对问题，并令d=min(dL,dR)
 * 4、将L-d~L+d内的点以y值排序，对于每一个点(x1,y1)找出y值在y1-d~y1+d内
 * 的所有点，计算距离为d'
 * 如果d'小于d，令d=d'，最后的d值就是答案
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
typedef struct
{
    double x;
    double y;
} Point;

typedef struct
{
    Point *list;
    int count;
} PointList;

typedef struct
{
    Point *a;
    Point *b;
    double space;
} PointClosed;

PointList* newPointList(int count)
{
    PointList* L = (PointList*)malloc(sizeof(PointList));
    L->list = (Point *)malloc(count*sizeof(Point));
    L->count = count;
    return L;
}
void freePointList(PointList* L)
{
    free(L->list);
    L->list = NULL;
    free(L);
    L = NULL;
}
void printPoint(Point *p)
{
    printf("x:%lf y:%lf",p->x,p->y);
}
void swap(Point *a, Point *b)
{
    Point temp = *a;
    *a = *b;
    *b = temp;
}
int partition(PointList *array,int low,int high)
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
    Point base = array->list[low];
    double temp;
    int p=low, iter=p+1;
    while(iter <= high)
    {
        if(array->list[iter].x == base.x && array->list[iter].y < base.y)
        {
            ++p;
            swap(&array->list[p],&array->list[iter]);
        }
        if(array->list[iter].x < base.x)
        {
            ++p;
            swap(&array->list[p],&array->list[iter]);
        }
        ++iter;
    }
    swap(&array->list[low],&array->list[p]);
    return p;
}
int getRandomIndex(low,high)
{
    return rand()%(high-low+1)+low;
}
int randomPartition(PointList *array,int low,int high)
{
    if(high <= low)
    {
        return low;
    }
    int random_index = getRandomIndex(low,high);
    swap(&array->list[low],&array->list[random_index]);
    return partition(array,low,high);
}
void quickSort(PointList *array,int start,int end)
{
    if(start < end)
    {
        int p = randomPartition(array,start,end);
        quickSort(array,start,p);
        quickSort(array,p+1,end);
    }
}
void sortPointListX(PointList* L)
{

}
void printPointList(PointList* L,int N)
{
    int i;
    for(i = 0; i < N; i++)
    {
        printPoint(&L->list[i]);
        printf("\n");
    }
}
double Distinguish(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x))+((a.y-b.y)*(a.y-b.y));
}
void BruteForce(PointList* L,PointClosed* pointClosed,
                int begin,int end)
{
    int i,j,space;
    for(i = begin; i <= end; ++i)
    {
        for(j = i+1; j <= end; ++j)
        {
            space = Distinguish(L->list[i],L->list[j]);
            if(space < pointClosed->space)
            {
                pointClosed->a = &L->list[i];
                pointClosed->b = &L->list[j];
                pointClosed->space = space;
            }
        }

    }
}
void Middle(PointList* L,PointClosed* pointClosed,
            int mid_point,double mid_index_x)
{
    int i,j,count,count_in=0;
    double d = pointClosed->space;
    i = mid_point;
    double left_line = mid_index_x-d,
                       right_line = mid_index_x+d;
    while(i >= 0 && L->list[i].x >= left_line)
    {
        j = mid_point+1;
        count = 0;
        while(L->list[j].x <=right_line && j <= L->count
              && count++ < 6)
        {
            if(L->list[j].y < L->list[i].y-d ||
                    L->list[j].y > L->list[i].y+d)
                // L->list[j] 不在 d*2d这个区间内
            {
                ++j;
                continue;
            }
            double space = Distinguish(L->list[i],L->list[j]);
            if(space < pointClosed->space)
            {
                pointClosed->a = &L->list[i];
                pointClosed->b = &L->list[j];
                pointClosed->space = space;
            }
            ++j;
        }
        --i;
    }
//    printf("多少次？？:%d\n",count);
}
void DivideAndConquer(PointList* L,PointClosed* pointClosed,
                      int begin,int end)
{
    if(end - begin + 1 < 4)
    {
        BruteForce(L,pointClosed,begin,end);
    }
    else
    {
        int mid_point = (begin + end) / 2;
        double mid_index_x =L->list[mid_point].x;
        DivideAndConquer(L,pointClosed,begin,mid_point);
        DivideAndConquer(L,pointClosed,mid_point+1,end);
        Middle(L,pointClosed,mid_point,mid_index_x);
    }
}
int main()
{
    srand((unsigned)time(NULL));
    int N = 40000;
    int low = 0,high = N-1;
    PointList* L = newPointList(N);
    int i;
    for(i = 0; i < N; i++)
    {
        L->list[i].x = getRandomIndex(low,high)*67;
    }
    for(i = 0; i < N; i++)
    {
        L->list[i].x += getRandomIndex(low,high)*31;
    }
    for(i = 0; i < N; i++)
    {
        L->list[i].y = getRandomIndex(low,high)*73;
    }
    for(i = 0; i < N; i++)
    {
        L->list[i].y += getRandomIndex(low,high)*24;
    }
    //printPointList(L,N);
    printf("===============\n");
    quickSort(L,low,high);
    //printPointList(L,N);
    PointClosed pointClosed;
    pointClosed.space = 60000;
    BruteForce(L,&pointClosed,0,N-1);
    printf("最近点为：a:");
    printPoint(pointClosed.a);
    printf(" b:");
    printPoint(pointClosed.b);
    printf(" 距离:%lf\n",pointClosed.space);
    PointClosed pointClosed_2;
    pointClosed_2.space = 60000;
    DivideAndConquer(L,&pointClosed_2,low,high);
    printf("最近点为：a:");
    printPoint(pointClosed_2.a);
    printf(" b:");
    printPoint(pointClosed_2.b);
    printf(" 距离:%lf\n",pointClosed_2.space);
    return 0;
}
