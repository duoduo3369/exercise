# coding=UTF8

def merge_sort(L):
    """ 排序结束后，原数组元素依然无序。
    """
    if len(L) <= 1:
        return L
    left = merge_sort(L[:len(L)/2])
    right = merge_sort(L[len(L)/2:])    
    L = merge(left,right)
    return L

def merge(left,right):
    if not left:
        return right
    if not right:
        return left
    left_index,right_index = 0,0
    left_length,right_length = len(left),len(right)
    sorted_list = []
    while left_index < left_length and right_index < right_length:
        if left[left_index] < right[right_index]:
            sorted_list.append(left[left_index])
            left_index += 1
        else:
            sorted_list.append(right[right_index])
            right_index += 1
    while left_index < left_length:
        sorted_list.append(left[left_index])
        left_index += 1
    while right_index < right_length:
        sorted_list.append(right[right_index])
        right_index += 1
    return sorted_list
        
left,right = range(5),range(3)
left_null,right_null = [],[]
import random
L = random.sample(xrange(40),30)

import unittest

class MergeTest(unittest.TestCase):
    def test_merge_1(self):
        self.assertEqual(merge(range(5),range(3)),
                         [0, 0, 1, 1, 2, 2, 3, 4])
    def test_merge_2(self):
        self.assertEqual(merge(range(20),[]),range(20))
    def test_merge_3(self):
        self.assertEqual(merge([],range(6)),range(6))
    def test_merge_4(self):
        self.assertEqual(merge([],[]),[])

from copy import copy       
class Merge_sort(unittest.TestCase):
    def test_merge_sort_1(self):
        test_list = random.sample(xrange(20),20)        
        self.assertEqual(merge_sort(test_list),range(20))
    def test_merge_sort_2(self):
        test_list = random.sample(xrange(30),20)
        test_list_copy = copy(test_list)
        test_list_copy.sort()
        self.assertEqual(merge_sort(test_list),test_list_copy)
    def test_merge_sort_3(self):
        self.assertEqual(merge_sort([]),[])
    def test_merge_sort_4(self):
        self.assertEqual(merge_sort([1]),[1])
        
        
def main():
    unittest.main()
