#include<iostream>
 #include<cstdlib>
 using namespace std;

 void LCSLength(int m, int n, char *x, char *y, int c[][10], int b[][10]) //定义函数时，**c，**b不会用
 {
     int i, j;
     for(i = 1; i <= m; ++i){
         c[i][0] = 0;
         b[i][0] = 0;//可以不用初始化
     }
     for(i = 1; i <= m; ++i){
         c[0][i] = 0;
         b[0][i] = 0;//可以不用初始化
     }
     c[0][0] = b[0][0] = 0;

     for(i = 1; i <= m; i ++)//m行n列
         for(j = 1; j <= n; j ++){
             if(x[i] == y[j]){
                 c[i][j] = c[i - 1][j - 1] + 1;//左上方
                 b[i][j] = 1;
             }else if(c[i - 1][j] >= c[i][j - 1]){
                 c[i][j] = c[i - 1][j];//上方
                 //X少去一项不影响，故最长公共子序列最后一项来自Y
                 //X（i）与Y（j）的最长公共子序列为X（i-1）与Y（j）最长公共子序列
                 //max{c[i][j-1], c[i-1][j]}
                 b[i][j] = 2;
             }else{
                 c[i][j] = c[i][j - 1]; //左方
                 //Y少去一项不影响，故最长公共子序列最后一项来自X
                 b[i][j] = 3;
             }
         }
 }

 void LCS(int i, int j, char *x, int b[][10])
 {
     if(i == 0 || j == 0)return;//不会再有左上方，故该元素为公共子列的首元素
     if(b[i][j] == 1){
         LCS(i - 1, j - 1, x, b);//从左上方来的
         cout<<x[i];//先递归再打印
     }else if(b[i][j] == 2)//X少去一项不影响，故X（i）与Y（j）的最长公共子序列为X（i-1）与Y（j）最长公共子序列
         LCS(i - 1, j, x, b);//从上方来的
     else
         LCS(i, j - 1, x, b);//从左方来的
 }

 int main()
 {
     int b[10][10], c[10][10], i, j;
     char X[9] = " ABCBDAB";//" dbcdabd";        注意X[0]为空项
     char Y[8] = " BDCABA";//" bacdbd";
     char Z[7];
     LCSLength(7, 6, X, Y, c, b);//LCSLength(7, 6, X, Y, &c[0], &b[0]);
     cout<<c[7][6]<<endl;
     for(i = 0;  i <= 7; i ++){
         for(j = 0; j <= 6; j ++){
             cout<<c[i][j]<<"   ";
         }
         cout<<endl;
     }
     cout<<endl;
     for(i = 0; i <= 7; i ++){
         for(j = 0; j <= 6; j ++){
             cout<<b[i][j]<<"   ";
         }
         cout<<endl;
     }
     LCS(7, 6, X, b);//LCS(7, 6, X, &b[0]);
     //system("pause");
 }
