from cProfile import run
from time import time

def time_counter(fun):
    def fac(n):
        start = time()
        returnv = fun(n)
        end = time()
        print "fib(%s)'s time is %s" % (n,end-start)
        del start,end
        return returnv
    return fac
    

#@time_counter
from fibonacci import fibonacci as fib
fib.fibonacci = time_counter(fib.fibonacci)
def test_fibonacci(n):    
    fibonacci = fib.fibonacci
    return fibonacci(n)

from fibonacci import fibonacci as fib
fib.fib_line = time_counter(fib.fib_line)    
def test_fib_line(n):
    fibonacci = fib.fib_line
    return fibonacci(n)

if __name__ == "__main__":
    pass
