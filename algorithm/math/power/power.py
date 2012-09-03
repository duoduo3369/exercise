# coding=UTF8
#
# power 和 power_line的调用次数是相同的
# fast power次数大大降低
# fast_power_2 和fast power 调用次数相同

def power(x,n):
    if n is 0:
        return 1
    else:
        return x * power(x,n-1)

def power_line(b,n):
    def power_iter(b,counter,product):
        if counter is 0:
            return product
        else:
            return power_iter(b,counter-1,product * b)
    return power_iter(b,n,1)

def square(num):
    return num * num
def is_even(num):
    return num % 2 is 0
    
def fast_power(x,n):    
    if n is 0:
        return 1
    elif is_even(n):
        return square(fast_power(x,n/2))
    else:
        return x * fast_power(x,n-1)

def fast_power_2(x,n):
    if n is 0:
        return 1
    elif is_even(n):
        return fast_power_2(square(x),n/2)
    else:
        return x * fast_power_2(x,n-1)
