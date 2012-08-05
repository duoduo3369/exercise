#!/usr/bin/python
# -*- coding: utf8 -*-

from tools import string_to_token
from tools import isListArray

from insert_sort import insert_sort
def test_insert_sort(input_array):
    return insert_sort(input_array)

from bubble_sort import bubble_sort
def test_bubble_sort(input_array):
    return bubble_sort(input_array)

if __name__ == '__main__':
    input_array = raw_input('please input an array:')
    input_array = string_to_token(input_array)
    while not isListArray(input_array):
        input_array = raw_input('please input an array:')
        input_array = string_to_token(input_array)    
    output_array = test_bubble_sort(input_array)
    print output_array

