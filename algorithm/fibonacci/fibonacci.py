# coding=UTF8

def fibonacci(n):
    """树形递归"""
    if n is 0:
        return 0
    if n is 1:
        return 1
    return fibonacci(n-1) + fibonacci(n-2)

def fib_line(n):
    def fib_iter(a,b,count):
        if count is 0:
            return b
        else:
            return fib_iter(b,a+b,count-1)
    return fib_iter(1,0,n)
