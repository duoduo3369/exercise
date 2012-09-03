# coding=UTF8
def smallest_divisor(n):
    """最小因子 O(sqrt(n))"""
    def dividable(divisor,n):
        return n % divisor is 0
    
    def find_divisor(n,test_divisor):
        if test_divisor ** 2 > n:
            return n
        elif dividable(test_divisor,n):
            return test_divisor
        else:
            return find_divisor(n,test_divisor+1)
            
    return find_divisor(n,2)
    

def is_prime_sd(n):
    """最小因子为他本身"""
    return smallest_divisor(n) is n

from random import randint
def is_prime_fm(n,times=None):
    def is_prime(n):
        """如果n为素数，任意a<n,那么pow(a,n) % n == a"""
        def fermat_test(a,n):
            """费马检查的结果并不是一定正确，结果只有概率上的准确性"""
            print  "n:",n,"a:", a,"remainder",pow(a,n) % n 
            return pow(a,n) % n == a
        print '****'
        if n < 2:
            return False
        elif n is 2:
            return True
        return fermat_test(randint(2,n-1),n)
    if not times:
        times = n / 2 + 1
    for i in xrange(times):
        print 'i:',i,'times:',times
        if not is_prime(n):
            return False
    return True
