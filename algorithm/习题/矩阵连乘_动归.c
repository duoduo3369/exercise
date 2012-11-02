/**
 * A1A2A3...AN
 * minMulTimes[left][right] 存着Aleft~Aright进行乘法运算的最小个数
 * breakK存着取得这些最小个数时的Ak点，在Aleft~AK加括号
 * minMulTimes、breakK数据下标皆从1开始
 * dimension下标从0开始
 * 例如 A1[30*35] A2[35*15] A3[15*5] A4[5*10]
 * dimension[30,35,15,5,10] 共N+1个元素(N=4)
 * m[i][j] = 0, i = j,A[i:i] = A[i],单一矩阵，无需计算
 * m[i][j] = min{m[i][k] + m[k+1][j] + pi-1*pk*pj} i < j(k为中断点)
 * 计算顺序要保证在计算m[i][j]查找m[i][k]和m[k+1][j]的时候，
 * m[i][k]和m[k+1][j]已经计算出来了
 * http://www.cnblogs.com/liushang0419/archive/2011/04/27/2030970.html
 * 斜对角线为顺序
 * 1、minMulTimes[i][i] = 0, i = 1,2,...n
 * 2、再算minMulTimes[i][i+1], i = 1,2,...n-1(链长为2)(斜对角线)
 * 3、minMulTimes[i][i+2], i = 1,2,...n-2(链长为3)
**/

#include<stdio.h>
#include<stdlib.h>
#define SIZE 7
void MatrixChain(int *dimension,int N,int **minMulTimes,int **breakK)
{
    int i;
    //对角线置0
    for(i = 1; i <= N; ++i)
    {
        minMulTimes[i][i] = 0;
    }
    int chain_length,left,right,k;
    //从链长为2到链长为N填两个矩阵
    for(chain_length = 2; chain_length <= N; ++chain_length)
    {
        for(left = 1; left <= N-chain_length+1; ++left)
        {
            right = left + chain_length - 1;
            //A1~AN
            //A11 + A2~AN + p[left-1]*p[left]*p[right] A11 = 0
            //将A1看做最初的break 得到最初的m1~N
            minMulTimes[left][right] = minMulTimes[left+1][right] +
                                       dimension[left-1]*dimension[left]*dimension[right];
            //dimension[left-1] 是因为dimension 下标从0开始
            // 如A1[1,2]*A2[2,3]，left可以看做A1的列[2],left-1为A1的行
            breakK[left][right] = left;
            for(k = left+1; k < right; ++k)
            {
                //得到最小的m1~N
                int mulTimes = minMulTimes[left][k]+minMulTimes[k+1][right]+
                        dimension[left-1]*dimension[k]*dimension[right];
                if(mulTimes < minMulTimes[left][right])
                {
                    minMulTimes[left][right] = mulTimes;
                    breakK[left][right] = k;
                }
            }
        }
    }
}
void Traceback(int left,int right,int **breakK)
{
    //A[left:right]最佳加括号方式为 (left：k)(k+1,right)
    // k 即为 breakK[left][right]
    if(left == right)
    {
        return ;
    }
    Traceback(left,breakK[left][right],breakK);
    Traceback(breakK[left][right]+1,right,breakK);
    printf("Multiply A%d,%d",left,breakK[left][right]);
    printf(" and A%d,%d\n",breakK[left][right]+1,right);
}
print_array(int **array,int size)
{
    int i,j;
    for(i = 0; i < size; ++i)
    {
        for(j =0; j < size; j++)
        {
            printf("%8d ",array[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    static int dimension[SIZE] = {30,35,15,5,10,20,25};
    int **minMulTimes = (int **)malloc(SIZE*sizeof(int *));
    int i;
    for(i = 0; i < SIZE; ++i)
    {
        minMulTimes[i] = (int *)malloc(SIZE*sizeof(int));
    }
    int **breakK = (int **)malloc(SIZE*sizeof(int *));
    for(i = 0; i < SIZE; ++i)
    {
        breakK[i] = (int *)malloc(SIZE*sizeof(int));
    }
    int j;
    printf("M:\n");
    print_array(minMulTimes,SIZE);
    printf("B:\n");
    print_array(breakK,SIZE);
    printf("\n\n======================\n\n");
    MatrixChain(dimension,SIZE-1,minMulTimes,breakK);
    Traceback(1,SIZE-1,breakK);
    printf("\n\n======================\n\n");
    printf("M:\n");
    print_array(minMulTimes,SIZE);
    printf("B:\n");
    print_array(breakK,SIZE);
    printf("\n\n======================\n\n");
    return 0;
}
