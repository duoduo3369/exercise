# coding=UTF8
import cProfile
from Sum import Sum

def integral(function,a,b,dx):
    def add_dx(x):
        return x + dx
    def Next(num):
        return num + dx / 2.0
    return Sum(function,(a+dx/2.0),add_dx,b)*dx

def cube(x):
    return x * x * x

def simpson_integral(function,a,b,n):
    def get_h():
        return (b - a) * 1.0 / n
    def get_y(k):
        return function(a+k*get_h())
    def simpson_term(k):
        if k is 0 or k is n:
            return get_y(k)
        elif k % 2 is 0:
            return 2 * get_y(k)
        else:
            return 4 * get_y(k)
    def simpson_next(k):
        return k + 1
    return get_h() / 3.0 * Sum(simpson_term,0,simpson_next,n)
