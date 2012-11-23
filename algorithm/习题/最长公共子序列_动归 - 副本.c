/**
 """

������X={x1,x2,x3,...xm},Y={y1,y2,...yn}
�����������ΪZ={z1,z2,...zk}
��������3��:
(1)��xm = yn,�� zk = xm = yn,
   ��zk-1 �� Xm-1 �� Ym-1�������������
(2)��xm != yn,�� zk != xm,��
   Z�� Xm-1 �� Y �������������
(3)��xm != yn,�� zk != ym,��
   Z�� X �� Ym-1 �������������

���� Xm-1={x1,x2,x3,...xm-1}

��MaxLenghtMetrix[m+1][n+1]�����ά��������¼����¼Xi��Yj
������������г���(Ҳ����zk)��

MaxLenghtMetrix[i][j]
1�� = 0; i = 0,j = 0
2�� = MaxLenghtMetrix[i-1][j-1] + 1;  i,j > 0,xi = yi
3�� = max(MaxLenghtMetrix[i][j-1],MaxLenghtMetrix[i-1][j])
      i,j > 0, xi!=yi

��SolvedNumberMetrix�����ά��������¼����¼����MaxLenghtMetrixʱ��
����һ��������õ���

ע�����
��ΪX,Y��1��ʼ�������ַ�����ʼʱҪ��һ�����ַ� 'abcd' --> ' abcd'
SolvedNumberMetrix��MaxLenghtMetrix�ĺ�������ĳ��ȷֱ�Ϊm+1,n+1
���ǵ��õ�ʱ��ȴҪ��m,n
"""
 **/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void LCSLength(int XLength,int YLength,char* XArray,char* YArray,
              int **MaxLenghtMetrix,int **SolvedNumberMetrix)
{
    /**
     * XLengthΪʵ����Ч��Ԫ�ظ���
     *
     ***/
    int i,j;
    MaxLenghtMetrix[0][0] = SolvedNumberMetrix[0][0] = 0;
    for(i = 1; i <= XLength; i++)
    {
        MaxLenghtMetrix[i][0] = 0;
        SolvedNumberMetrix[i][0] = 0;
    }
    for(i = 1; i <= YLength; i++)
    {
        MaxLenghtMetrix[0][i] = 0;
        SolvedNumberMetrix[0][i] = 0;
    }
    for(i = 1; i <= XLength; i++)
    {
        for(j = 1; j <= YLength; j++)
        {
            if(XArray[i-1] == YArray[j-1])
            //�ַ����±��0��ʼ
            {
                MaxLenghtMetrix[i][j] = MaxLenghtMetrix[i-1][j-1]+1;
                SolvedNumberMetrix[i][j] = 1;
            }
            else if(MaxLenghtMetrix[i-1][j] >= MaxLenghtMetrix[i][j-1])
            {
                MaxLenghtMetrix[i][j] = MaxLenghtMetrix[i-1][j];
                SolvedNumberMetrix[i][j] = 2;
            }
            else
            {
                MaxLenghtMetrix[i][j] = MaxLenghtMetrix[i][j-1];
                SolvedNumberMetrix[i][j] = 3;
            }
        }
    }
}
void LCS(int i,int j,char *XArray,int **SolvedNumberMetrix)
{
    if(i == 0|| j == 0)
    {
        return ;
    }
    if(SolvedNumberMetrix[i][j] == 1)
    {
        LCS(i-1,j-1,XArray,SolvedNumberMetrix);
        printf("%c",XArray[i]);
    }
    else if(SolvedNumberMetrix[i][j] == 2)
    {
        LCS(i-1,j,XArray,SolvedNumberMetrix);
    }
    else
    {
        LCS(i,j-1,XArray,SolvedNumberMetrix);
    }
}
print_array(int **array,int XLength,int YLength)
{
    int i,j;
    for(i = 0; i < XLength; ++i)
    {
        for(j =0; j < YLength; j++)
        {
            printf("%3d ",array[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    char* XArray = "ABCBDAB";
    char* YArray = "BDCABA";
    int XLength = strlen(XArray);
    int YLength = strlen(YArray);
    int **MaxLenghtMetrix = (int **)malloc((XLength+1)*sizeof(int *));
    int i;
    for(i = 0; i <= XLength; ++i)
    {
        MaxLenghtMetrix[i] = (int *)malloc((YLength+1)*sizeof(int));
    }
    int **SolvedNumberMetrix = (int **)malloc((XLength+1)*sizeof(int *));
    for(i = 0; i <= XLength; ++i)
    {
        SolvedNumberMetrix[i] = (int *)malloc((YLength+1)*sizeof(int));
    }
    LCSLength(XLength,YLength, XArray, YArray,
               MaxLenghtMetrix, SolvedNumberMetrix);
    printf("================\n");
    printf("MaxLenghtMetrix:\n");
    print_array(MaxLenghtMetrix,XLength,YLength);
    printf("================\n");
    printf("SolvedNumberMetrix:\n");
    print_array(SolvedNumberMetrix,XLength,YLength);
    LCS(XLength,YLength,XArray,SolvedNumberMetrix);
    return 0;
}
