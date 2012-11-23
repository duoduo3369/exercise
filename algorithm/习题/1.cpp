#include<iostream>
 #include<cstdlib>
 using namespace std;

 void LCSLength(int m, int n, char *x, char *y, int c[][10], int b[][10]) //���庯��ʱ��**c��**b������
 {
     int i, j;
     for(i = 1; i <= m; ++i){
         c[i][0] = 0;
         b[i][0] = 0;//���Բ��ó�ʼ��
     }
     for(i = 1; i <= m; ++i){
         c[0][i] = 0;
         b[0][i] = 0;//���Բ��ó�ʼ��
     }
     c[0][0] = b[0][0] = 0;

     for(i = 1; i <= m; i ++)//m��n��
         for(j = 1; j <= n; j ++){
             if(x[i] == y[j]){
                 c[i][j] = c[i - 1][j - 1] + 1;//���Ϸ�
                 b[i][j] = 1;
             }else if(c[i - 1][j] >= c[i][j - 1]){
                 c[i][j] = c[i - 1][j];//�Ϸ�
                 //X��ȥһ�Ӱ�죬����������������һ������Y
                 //X��i����Y��j���������������ΪX��i-1����Y��j�������������
                 //max{c[i][j-1], c[i-1][j]}
                 b[i][j] = 2;
             }else{
                 c[i][j] = c[i][j - 1]; //��
                 //Y��ȥһ�Ӱ�죬����������������һ������X
                 b[i][j] = 3;
             }
         }
 }

 void LCS(int i, int j, char *x, int b[][10])
 {
     if(i == 0 || j == 0)return;//�����������Ϸ����ʸ�Ԫ��Ϊ�������е���Ԫ��
     if(b[i][j] == 1){
         LCS(i - 1, j - 1, x, b);//�����Ϸ�����
         cout<<x[i];//�ȵݹ��ٴ�ӡ
     }else if(b[i][j] == 2)//X��ȥһ�Ӱ�죬��X��i����Y��j���������������ΪX��i-1����Y��j�������������
         LCS(i - 1, j, x, b);//���Ϸ�����
     else
         LCS(i, j - 1, x, b);//��������
 }

 int main()
 {
     int b[10][10], c[10][10], i, j;
     char X[9] = " ABCBDAB";//" dbcdabd";        ע��X[0]Ϊ����
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
