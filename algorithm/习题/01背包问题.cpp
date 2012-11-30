/**
    Material����Ʒ��
    Knapsack��������
    mArray ʢ�����е���Ʒ��Ϣ
    TempValue����ά���飬�����;ʹ�õ�valueֵ
    BestStrategy[N+1]���������õ�01�������飬��Ϊ�±�
    �Ǵ�1~N����N+1

    �㷨��
    [1]knapsack
    TempValue[i][col] iΪi����Ʒ��colΪ��������(����������������)
    1~N-1����Ʒ��ʱ��(i����Ʒ��colΪ��������)��
    1����� col >= wi�������������i����Ʒ������(˵����������)
    ��ô��ֵ���ǲ�װ�����Ʒ(TempValue[i+1][col])��װ���
    ��Ʒʱ�ϴ��һ��
    TempValue[i][col] = max(TempValue[i+1][col],
                                       TempValue[i+1][col-mArray[i].weight]
                                       +mArray[i].value);
    2������   0 =< col < wi����������i��С(��������)
    ��ֵ���ǲ�װ�����Ʒ�ļ�ֵ
    TempValue[i][col] = TempValue[i+1][col];
    3�����һ����ƷTempValue[n][col](��ΪǰN-1����Ʒ����ʱ�õ�i+1,����
    ���һ����Ʒ��Ҫ��������)
    �������ɣ�������С�ȵ�n����Ʒ������(col >= wn)
    TempValue[n][col] = vn,
    ����TempValue[n][col] = 0

    [2]traceback
    1������ǰn-1����Ʒ��
        ��TempValue�У������i����Ʒ���i+1����Ʒ��value��ͬ��
    ˵��û���õ�i����Ʒ��BestStrategy[i] = 0
        �������˵�i����Ʒ��BestStrategy[i] = 1��
        capicity��ȥ�����Ʒ������
    2����n����Ʒ��� TempValue[n][capicity]��Ϊ0�Ļ�����˵��
    ���˵�n����Ʒ��
*/

#include <iostream>
#include <cmath>
using namespace std;
class Material
{
public:
    Material():weight(0),value(0){}
    Material(int c,double v):weight(c),value(v){}
    int weight;
    double value;
    void print() const
    {cout << "value:"<< this->value << " weight:" << this->weight << endl;}
};
class Knapsack
{
public:
    Knapsack():value(0),capicity(0){}
    Knapsack(double v,int c):value(v),capicity(c){}
    double value;
    int capicity;
};

void KnapsackProblem(const Material *mArray,const Knapsack& knpk,
                     const int n,double **TempValue)
{
    //ǰ����for��ȷ�����һ��Ԫ�صĴ�����
    int colMax = min(mArray[n].weight-1,knpk.capicity);
    for(int col = 0; col <= colMax; col++)
    {
        TempValue[n][col] = 0;
    }
    for(int col = mArray[n].weight; col <= knpk.capicity; col++)
    {
        TempValue[n][col] = knpk.value;
    }
    for(int i = n-1; i > 1; i--)
    {
        colMax = min(mArray[i].weight-1,knpk.capicity);
        for(int col = 0; col <= colMax; col++)
        {
            TempValue[i][col] = TempValue[i+1][col];
        }
        for(int col = mArray[i].weight; col <= knpk.capicity; col++)
        {
            TempValue[i][col] = max(TempValue[i+1][col],
                                       TempValue[i+1][col-mArray[i].weight]
                                       +mArray[i].value);
        }
    }
    TempValue[1][knpk.capicity] = TempValue[2][knpk.capicity];
    if(knpk.capicity > mArray[1].weight)
    {
        TempValue[1][knpk.capicity] = max(TempValue[1][knpk.capicity],
                                       TempValue[2][knpk.capicity-mArray[1].weight]
                                       +mArray[1].value);
    }
}
void Taceback(const Material *mArray,double **TempValue,const Knapsack& knpk,
              const int n,int *BestStrategy)
{
    int capicity = knpk.capicity;
    for(int i = 1; i < n; i++)
    {
        if(TempValue[i][capicity]
           == TempValue[i+1][capicity])
        {
            BestStrategy[i] = 0;
        }
        else
        {
            BestStrategy[i] = 1;
            capicity -= mArray[i].weight;
        }
    }
    BestStrategy[n] = (TempValue[n][knpk.capicity]) ? 1 : 0;
}
template<typename T>
void print_array(T* array,const int length)
{
    for(int i = 0; i < length; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}
template<typename T>
void set_2dim_array( T** array, const int row,const int col)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col;j++)
        {
            array[i][j] = 0;
        }

    }
}
template<typename T>
void print_2dim_array( T** array, const int row,const int col)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col;j++)
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}
int main()
{
    const int N = 5;
    const int C = 10;
    int BestStrategy[N+1];
    for(int i = 0; i < N+1;i++)
    {
        BestStrategy[i] = 0;
    }
    double **TempValue = new double*[N+1];
    for(int i = 0; i < N+1; i++)
    {
        TempValue[i] = new double[C+1];
    }
    set_2dim_array(TempValue,N+1,C+1);
    print_2dim_array(TempValue,N+1,C+1);
    cout << "================" << endl;
    Knapsack knpk(N,C);
    Material mArray[] = {
                    Material(),
                    Material(2,6),
                    Material(2,3),
                    Material(6,5),
                    Material(5,4),
                    Material(4,6)
                    };
    KnapsackProblem(mArray,knpk,N,TempValue);
    Taceback(mArray,TempValue,knpk,N,BestStrategy);
    print_2dim_array(TempValue,N+1,C+1);
    cout << "==================" << endl;
    print_array(BestStrategy,N+1);
    return 0;
}
