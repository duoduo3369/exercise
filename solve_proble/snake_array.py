# coding=UTF8


import sys
from pprint import pprint
from double_array import double_array

##在n*n方陈里填入1,2,...,n*n,要求填成蛇形。例如n=4时方陈为：
##10 11 12 1
##9 16 13 2
##8 15 14 3
##7 6 5 4

def snake_array(n):    
    array = double_array(n,n)
    def init_row_col(n):
        return 0,n-1
    row,col = init_row_col(n)
    number = 1
    def set_array_pos(array,row,col,number):
        array[row][col] = number
    def plus_number(number):
        return number + 1
    while number <= n ** 2:
        while row < n and not array[row][col]:
            set_array_pos(array,row,col,number)
            row += 1
            number += 1
        row,col= row-1,col-1
        #print row,col,array
        while col >= 0 and not array[row][col]:
            set_array_pos(array,row,col,number)
            col -= 1
            number += 1
        col,row = col+1,row-1
        #print row,col,array
        while row >= 0 and not array[row][col]:
            set_array_pos(array,row,col,number)
            row -= 1
            number += 1
        row,col = row+1,col+1
        #print row,col,array
        while col < n and not array[row][col]:
            set_array_pos(array,row,col,number)
            col += 1
            number += 1
        col,row= col-1,row+1
        #print row,col,array
    return array


if __name__ == '__main__':
    n = input('please input n:')
    snake = snake_array(n)
    pprint(snake)
