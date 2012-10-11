#include<stdio.h>
#define N 16
// N = 2**n
#define NOT_ARRANGE 0
void copy_array(int form_array[][N],int fa_origin_point_x,int fa_origin_point_y,
                int to_array[][N],int to_origin_point_x,int to_origin_point_y,
                int length)
{
    int i = 0,j = 0;
    while(i < length)
    {
        j = 0;
        while(j < length)
        {
            to_array[to_origin_point_x+i][to_origin_point_y+j] = form_array[fa_origin_point_x+i][fa_origin_point_y+j];
            ++j;
        }
        ++i;
    }
}

void print_double_array(int array[][N],int origin_point_x,int origin_point_y,int length)
{
    int i = 0,j = 0;
    while(i < length)
    {
        j = 0;
        while(j < length)
        {
            printf("%2d ",array[origin_point_x+i][origin_point_y+j]);
            ++j;
        }
        putchar('\n');
        ++i;
    }
}

void inital_array(int array[][N])
{
    int j;
    for(j = 0; j < N; ++j)
    {
        array[0][j] = j+1;
    }
}

void arrange(int array[][N],int origin_point_x,int origin_point_y,int length)
{
    print_double_array(array,0,0,N);
    putchar('\n');
    if(length >= N)
    {
        return ;
    }
    printf("==%d==\n",array[origin_point_x+length-1][origin_point_y+length-1]);
    if(array[origin_point_x+length-1][origin_point_y+length-1]!=NOT_ARRANGE)
    {
        int step = length*2,i;
        int y = origin_point_y;
        for(i = 0; i < N/step; i++)
        {
            y = origin_point_y + step*i;
            printf("***%d %d %d\n",y,i,step*i);
            copy_array(array,origin_point_x,y,
                       array,origin_point_x+length,y+length,length);
            copy_array(array,origin_point_x,y+length,
                       array,origin_point_x+length,y,length);

        }

    }
    arrange(array,origin_point_x,origin_point_y,length*2);
    //arrange(array,origin_point_x,origin_point_y+length,length*2);
}

int main()
{
    int Array[N][N] = {0};
    inital_array(Array);
    //print_double_array(Array,0,0,N);
    arrange(Array,0,0,1);
    //print_double_array(Array,0,0,N);
    return 0;
}
