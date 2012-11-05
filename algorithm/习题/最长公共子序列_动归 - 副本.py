# coding=UTF8

"""



设序列X={x1,x2,x3,...xm},Y={y1,y2,...yn}
最长公共子序列为Z={z1,z2,...zk}
子问题有3个:
(1)若xm = yn,且 zk = xm = yn,
   则zk-1 是 Xm-1 和 Ym-1的最长公共子序列
(2)若xm != yn,且 zk != xm,则
   Z是 Xm-1 和 Y 的最长公共子序列
(3)若xm != yn,且 zk != ym,则
   Z是 X 和 Ym-1 的最长公共子序列

其中 Xm-1={x1,x2,x3,...xm-1}

用MaxLenghtMetrix[m+1][n+1]这个二维数组来记录来记录Xi和Yj
的最长公共子序列长度(也就是zk)，

MaxLenghtMetrix[i][j]
1、 = 0; i = 0,j = 0
2、 = MaxLenghtMetrix[i-1][j-1] + 1;  i,j > 0,xi = yi
3、 = max(MaxLenghtMetrix[i][j-1],MaxLenghtMetrix[i-1][j])
      i,j > 0, xi!=yi

用SolvedNumberMetrix这个二维数组来记录来记录存入MaxLenghtMetrix时是
由哪一个子问题得到的

注意事项：
因为X,Y从1开始，所以字符串开始时要加一个废字符 'abcd' --> ' abcd'
SolvedNumberMetrix，MaxLenghtMetrix的横纵坐标的长度分别为m+1,n+1

"""
from pprint import pprint
def LCSLength(XLength,YLength,XArray,YArray,
              MaxLenghtMetrix,SolvedNumberMetrix):
    i = 1
    while i <= XLength:
        MaxLenghtMetrix[i][0] = 0
        i += 1
    i = 1
    while  i <= YLength:
        MaxLenghtMetrix[0][i] = 0
        i += 1
    i = 1
    while i <= XLength:
        j = 1
        while j <= YLength:
            try:
                XArray[i] == YArray[j]
            except:
                print 'i',i,'j',j
            if XArray[i] == YArray[j]:
                MaxLenghtMetrix[i][j] = MaxLenghtMetrix[i-1][j-1]+1
                SolvedNumberMetrix[i][j] = 1            
            elif MaxLenghtMetrix[i-1][j] >= MaxLenghtMetrix[i][j-1]:
                MaxLenghtMetrix[i][j] = MaxLenghtMetrix[i-1][j]
                SolvedNumberMetrix[i][j] = 2
            else:
                MaxLenghtMetrix[i][j] = MaxLenghtMetrix[i][j-1]
                SolvedNumberMetrix[i][j] = 3
            j += 1
        i += 1   

def LCS(i,j,XArray,SolvedNumberMetrix):
    if i <= 0 or j <= 0: return
    if SolvedNumberMetrix[i][j] is 1:
        LCS(i-1,j-1,XArray,SolvedNumberMetrix)
        print XArray[i],
    elif SolvedNumberMetrix[i][j] is 2:
        LCS(i-1,j,XArray,SolvedNumberMetrix)
    else:
        LCS(i,j-1,XArray,SolvedNumberMetrix)


XArray = 'abcbdab'
YArray = 'bdcaba'
XArray = ' ' + XArray
YArray = ' ' + YArray 
from copy import copy
MaxLenghtMetrix = [[0 for i in xrange(len(YArray))] for j in xrange(len(XArray))]
SolvedNumberMetrix = [[0 for i in xrange(len(YArray))] for j in xrange(len(XArray))]
LCSLength(len(XArray)-1,len(YArray)-1,XArray,YArray,
              MaxLenghtMetrix,SolvedNumberMetrix)

pprint(MaxLenghtMetrix)
pprint(SolvedNumberMetrix)
LCS(len(XArray)-1,len(YArray)-1,XArray,SolvedNumberMetrix)
