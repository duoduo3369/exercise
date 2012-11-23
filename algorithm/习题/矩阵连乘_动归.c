/**
 * A1A2A3...AN
 * minMulTimes[left][right] ����Aleft~Aright���г˷��������С����
 * breakK����ȡ����Щ��С����ʱ��Ak�㣬��Aleft~AK������
 * minMulTimes��breakK�����±�Դ�1��ʼ
 * dimension�±��0��ʼ
 * ���� A1[30*35] A2[35*15] A3[15*5] A4[5*10]
 * dimension[30,35,15,5,10] ��N+1��Ԫ��(N=4)
 * m[i][j] = 0, i = j,A[i:i] = A[i],��һ�����������
 * m[i][j] = min{m[i][k] + m[k+1][j] + pi-1*pk*pj} i < j(kΪ�жϵ�)
 * ����˳��Ҫ��֤�ڼ���m[i][j]����m[i][k]��m[k+1][j]��ʱ��
 * m[i][k]��m[k+1][j]�Ѿ����������
 * http://www.cnblogs.com/liushang0419/archive/2011/04/27/2030970.html
 * б�Խ���Ϊ˳��
 * 1��minMulTimes[i][i] = 0, i = 1,2,...n
 * 2������minMulTimes[i][i+1], i = 1,2,...n-1(����Ϊ2)(б�Խ���)
 * 3��minMulTimes[i][i+2], i = 1,2,...n-2(����Ϊ3)
**/

#include<stdio.h>
#include<stdlib.h>
#define SIZE 7
void MatrixChain(int *dimension,int N,int **minMulTimes,int **breakK)
{
    int i;
    //�Խ�����0
    for(i = 1; i <= N; ++i)
    {
        minMulTimes[i][i] = 0;
    }
    int chain_length,left,right,k;
    //������Ϊ2������ΪN����������
    for(chain_length = 2; chain_length <= N; ++chain_length)
    {
        for(left = 1; left <= N-chain_length+1; ++left)
        {
            right = left + chain_length - 1;
            //A1~AN
            //A11 + A2~AN + p[left-1]*p[left]*p[right] A11 = 0
            //��A1���������break �õ������m1~N
            minMulTimes[left][right] = minMulTimes[left+1][right] +
                                       dimension[left-1]*dimension[left]*dimension[right];
            //dimension[left-1] ����Ϊdimension �±��0��ʼ
            // ��A1[1,2]*A2[2,3]��left���Կ���A1����[2],left-1ΪA1����
            breakK[left][right] = left;
            for(k = left+1; k < right; ++k)
            {
                //�õ���С��m1~N
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
    //A[left:right]��Ѽ����ŷ�ʽΪ (left��k)(k+1,right)
    // k ��Ϊ breakK[left][right]
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
