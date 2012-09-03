# coding=UTF8
def gcd(a,b):
    """欧几里得算法"""
    def remainder(x,y):
        return x % y
    if remainder(a,b) is 0:
        return b
    else:
        return gcd(b,remainder(a,b))
