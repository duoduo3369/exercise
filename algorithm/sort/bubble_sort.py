def bubble_sort(input_array):
    len_array = len(input_array)
    for times in xrange(len_array-1):
        flag = True
        for i in xrange(len_array-times-1):
            if input_array[i] > input_array[i+1]:
                input_array[i],input_array[i+1] = input_array[i+1],input_array[i]
                flag = False
        if flag == True:
            break
    return input_array
