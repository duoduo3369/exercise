/**
    Material：物品类
    Knapsack：背包类
    mArray 盛放所有的物品信息
    TempValue：二维数组，存放中途使用的value值
    BestStrategy[N+1]：最终有用的01策略数组，因为下标
    是从1~N所以N+1

    算法：
    [1]knapsack
    TempValue[i][col] i为i号物品，col为背包容量(用容量来做纵坐标)
    1~N-1个物品的时候(i号物品，col为背包容量)：
    1、如果 col >= wi如果背包容量比i号物品重量大(说明可以容纳)
    那么价值就是不装这个物品(TempValue[i+1][col])和装这个
    物品时较大的一个
    TempValue[i][col] = max(TempValue[i+1][col],
                                       TempValue[i+1][col-mArray[i].weight]
                                       +mArray[i].value);
    2、否则   0 =< col < wi背包容量比i号小(不能容纳)
    价值就是不装这个物品的价值
    TempValue[i][col] = TempValue[i+1][col];
    3、最后一个物品TempValue[n][col](因为前N-1个物品运算时用到i+1,所以
    最后一个物品需要单独考虑)
    若能容纳，容器大小比第n个物品重量大(col >= wn)
    TempValue[n][col] = vn,
    否则，TempValue[n][col] = 0

    [2]traceback
    1、对于前n-1个物品：
        在TempValue中，如果第i个物品与第i+1个物品的value相同，
    说明没有拿第i个物品，BestStrategy[i] = 0
        否则拿了第i个物品，BestStrategy[i] = 1，
        capicity减去这个物品的重量
    2、第n个物品如果 TempValue[n][capicity]不为0的话，则说明
    拿了第n个物品。
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
    //前俩个for是确定最后一个元素的存放情况
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
