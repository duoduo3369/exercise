# coding=UTF8
import cProfile
def Sum(Term,a,Next,b):
    """ 这是一个高阶的求和抽象，Σf(n)= f(a)+...+f(b),a,b是范围，term是求和的方程式，next是a的变换函数
        scheme 定义如下
        (define (<name> a b)
            (if (> a b)
                0
                (+ (<term> a)
                    (<name> (<next> a) b)
                )
            )
        )
    """
    if a > b:
        return 0
    else:
        return Term(a) + Sum(Term,Next(a),Next,b)

def pi(a,b):
    def Term(num):
        return 1.0 / ( num * (num + 2))
    def Next(num):
        return num + 4
    return Sum(Term,a,Next,b) * 8

def cube_sum(a,b):
    def cube(num):
        return num * num * num
    def Next(num):
        return num + 1
    return Sum(cube,a,Next,b) 
