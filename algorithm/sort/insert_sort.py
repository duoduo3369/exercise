# -*- coding: utf8 -*-
def insert_sort(input_array):
    """ asc ord
    
    每次处理就是将无序数列的第一个元素与有序数列的元素从后往前逐个进行比较，找出插入位置，将该元素插入到有序数列的合适位置中。
    """
    if isinstance(input_array,list) == False:
        print 'Error: When you use insert_sort function, please make sure your argument is a list'
        return None
    for j in xrange(1,len(input_array)):
        i = 0
        while input_array[j] > input_array[i]:
            i += 1
        temp = input_array[j]
        for k in xrange(j,i,-1):
            input_array[k] = input_array[k-1]
        input_array[i] = temp
    return input_array
