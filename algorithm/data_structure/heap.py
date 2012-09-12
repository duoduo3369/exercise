# -*- coding: utf8 -*-
import math
from cStringIO import StringIO
def show_tree(tree, total_width=64, fill=' '):
    """Pretty-print a tree."""
    output = StringIO()
    last_row = -1
    for i, n in enumerate(tree):
        if i:
            row = int(math.floor(math.log(i+1, 2)))
        else:
            row = 0
        if row != last_row:
            output.write('\n')
        columns = 2**row
        col_width = int(math.floor((total_width * 1.0) / columns))
        output.write(str(n).center(col_width, fill))
        last_row = row
    print output.getvalue()
    print '-' * total_width
    print
    return

import random
n = 80
heap = random.sample(xrange(n),n)
# heap_adjust(heap,len(heap)/2-1,len(heap))
def heap_adjust(heap,pos,length):
    # _shifup
    """ length 数组长度 最终调节范围是 pos~length-1

    """
    start_item = heap[pos]
    left_child_pos = pos * 2 + 1
    right_child_pos = left_child_pos + 1
    while left_child_pos < length:
        if left_child_pos < length - 1 and heap[left_child_pos] < heap[right_child_pos]:
            max_child_pos = right_child_pos
        else:
            max_child_pos = left_child_pos       
        if start_item > heap[max_child_pos]:                
            break
        heap[pos] = heap[max_child_pos]
        pos = max_child_pos
        left_child_pos = pos * 2 + 1
        right_child_pos = left_child_pos + 1
    heap[pos] = start_item
    return heap

def heap_built(heap,length):
    # heapify
    for i in reversed(xrange(length/2)):
        heap_adjust(heap,i,length)
    return heap
def heap_sort(heap):
    if len(heap) <= 1:
        return heap
    def swap(L,from_pos,to_pos):
        L[from_pos],L[to_pos] = L[to_pos],L[from_pos]
        return L
    heap_length = len(heap)
    heap_built(heap,heap_length)
    for i in xrange(heap_length-1,0,-1):
        swap(heap,0,i)
        heap_adjust(heap,0,i)
    return heap
    
import unittest

class HeapSortTest(unittest.TestCase):
    def test_heap_sort_1(self):
        self.assertEqual(heap_sort(range(3)),range(3))
    def test_heap_sort_2(self):
        self.assertEqual(heap_sort(range(50)),range(50))
    def test_heap_sort_3(self):
        self.assertEqual(heap_sort(range(1000)),range(1000))
    

if __name__ == '__main__':
    unittest.main()
