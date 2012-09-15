# coding=UTF8
import unittest
from copy import copy

def partition(L,low,high):
    if high - low <= 1:
        return low
    x = L[low]
    partition_index,iter_index = low,low+1
    while iter_index < high:
        if L[iter_index] < x:
            l1 = copy(L)
            #print l1,'->',
            partition_index += 1
            L[partition_index],L[iter_index] = L[iter_index],L[partition_index]
            #print L
        iter_index += 1
    L[partition_index],L[low] = L[low],L[partition_index]
    return partition_index

def quick_sort(L):
    def q_sort(L,low,high):
        if low < high:
            pivot = partition(L,low,high)
            #print low,pivot,high,L
            q_sort(L,low,pivot)
            q_sort(L,pivot+1,high)
            return L

    return q_sort(L,0,len(L))


import random
date1 = random.sample(xrange(50),30)
date2 = [4,2,5,3,6,7,1,9,0,2]



class TestQuickSort(unittest.TestCase):
    def test_quick_sort_1(self):
        self.assertEqual(quick_sort(range(3)),range(3))
    def test_quick_sort_2(self):
        self.assertEqual(quick_sort(range(50)),range(50))
    def test_quick_sort_3(self):
        self.assertEqual(quick_sort(range(1000)),range(1000))
    def test_quick_sort_4(self):
        self.assertEqual(quick_sort([]),[])
    def test_quick_sort_5(self):
        self.assertEqual(quick_sort([2]),[2])
    def test_quick_sort_6(self):
        test_list = random.sample(xrange(30),20)
        test_list_copy = copy(test_list)
        test_list_copy.sort()
        self.assertEqual(quick_sort(test_list),test_list_copy)
    

def test():
    unittest.main()

import cProfile
