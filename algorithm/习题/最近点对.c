/**
 * ƽ�������������
 * 1�����㼯�ϰ���x��y�������˳������(xΪ��)
 * 2���ҳ�����L��S����ΪSL��SR
 * 3��������2�ݹ��Ӧ�ý��SL��SR�����������⣬����d=min(dL,dR)
 * 4����L-d~L+d�ڵĵ���yֵ���򣬶���ÿһ����(x1,y1)�ҳ�yֵ��y1-d~y1+d��
 * �����е㣬�������Ϊd'
 * ���d'С��d����d=d'������dֵ���Ǵ�
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
                // L->list[j] ���� d*2d���������
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
//    printf("���ٴΣ���:%d\n",count);
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
    printf("�����Ϊ��a:");
    printPoint(pointClosed.a);
    printf(" b:");
    printPoint(pointClosed.b);
    printf(" ����:%lf\n",pointClosed.space);
    PointClosed pointClosed_2;
    pointClosed_2.space = 60000;
    DivideAndConquer(L,&pointClosed_2,low,high);
    printf("�����Ϊ��a:");
    printPoint(pointClosed_2.a);
    printf(" b:");
    printPoint(pointClosed_2.b);
    printf(" ����:%lf\n",pointClosed_2.space);
    return 0;
}
