/**
 *
 * value[i]是i号物品的价值
 * weight[i]是i号物品的重量
 * capacity 是容器的大小
 * maxValue[i][remainder]是当背包放入i号元素后的收益,,
 * remainder是容器剩余的大小
 *
 ***/

#include<iostream>
using namespace std;
int max(int a,int b)
{
    return a > b? a:b;
}
void Knapsack(int *value,int *weight,int capacity,int types,int **maxValue)
{
//    int = min(weight[types]-1,capacity);
    for(int i = 0; i <= types; i++)
    {
        maxValue[i][0] = 0;
    }
    for(int j = 0; j <= capacity;j++)
    {
        maxValue[0][j] = 0;
    }
    for(int i = 0; i < types; i++)
    {
        for(int j = 0; j <= capacity;j++)
        {
            if(j >= weight[i])
            {
                maxValue[i][j] = max(maxValue[i-1][j],
                                     maxValue[i-1][j-weight[i]]+value[i]);
            }
            else
            {
                maxValue[i][j] = maxValue[i-1][j];
            }
        }
    }
}
int main()
{
    int value[] = {6,3,5,4,6};
    int weight[] = {2,2,6,5,4};
    int types = 5;
    int capacity = 10;
    int **maxValue = new int*[types];
    for(int i = 0; i < types; i++)
    {
        maxValue[i] = new int[capacity+1];
    }
    for(int i = 0; i < types; i++)
    {
        for(int j = 0; j <= capacity; j++)
        {
            maxValue[i][j] = 0;
        }
    }
    for(int i = 0; i < types; i++)
    {
        for(int j = 0; j <= capacity; j++)
        {
            cout << maxValue[i][j] << " ";
        }
        cout << endl;
    }
    Knapsack(value,weight,capacity,types,maxValue);
     for(int i = 0; i < types; i++)
    {
        for(int j = 0; j <= capacity; j++)
        {
            cout << maxValue[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
