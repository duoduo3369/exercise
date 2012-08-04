#!/usr/bin/python
# -*- coding: utf8 -*-

from string_to_token import string_to_token

from insert_sort import insert_sort


if __name__ == '__main__':
    input_array = raw_input('please input an array:')
    input_array = string_to_token(input_array)
    output_array = insert_sort(input_array)
    print output_array

