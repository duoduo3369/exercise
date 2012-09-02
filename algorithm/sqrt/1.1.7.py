# coding=UTF8

# sicp 1.1.7

# 牛顿法求平方根

def sqrt(x):
    def sqrt_iter(guess,x):
        if(good_enough(guess,x)):
            return guess
        else:
            return sqrt_iter(improve(guess,x),x)
        
    return sqrt_iter(1.0,x)


def good_enough(guess,x):
    return abs(guess * guess - x) < 0.0001

def improve(guess,x):
    return average(guess,x / guess) 

def average(x,y):
    return (x + y) / 2
