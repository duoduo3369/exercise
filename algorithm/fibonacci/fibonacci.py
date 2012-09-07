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

def fib_fast(n):    
    def isEven(num):
        return num % 2 is 0
    def fib_iter(a,b,p,q,count):
        """ p = 0, q = 1 T变换： a<-bq+aq+ap b<-bp+aq
        详情请见：sicp 练习1.19
        """
        if count is 0:
            return b
        if isEven(count):
            return fib_iter(a,
                            b,
                            q*q + p*p,
                            2*p*q + q*q,
                            count/2)
        else:
            return fib_iter(b*q + a*q + a*p,
                            b*p + a*q,
                            p,
                            q,
                            count-1)
    return fib_iter(1,0,0,1,n)
                            
