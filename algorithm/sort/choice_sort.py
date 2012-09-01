def choice_sort(input_array):
    len_array = len(input_array)
    for i in xrange(len_array-1):
        min_index = i
        for j in xrange(i+1,len_array):
            if input_array[min_index] > input_array[j]:
                min_index = j
        if min_index != i:
            input_array[i],input_array[min_index] = input_array[min_index],input_array[i]
    return input_array
