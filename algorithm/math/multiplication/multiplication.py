def multiplication_accumulation(x,n):
    if n is 0:
        return 0
    else:
        return x + multiplication_accumulation(x,n-1)

def is_odd(num):
    return num % 2 is 1

def multiplication_binary(x,n):
    def double(num):
        return num * 2
    def half(num):
        return num / 2    
    def mul_iter(a,b,result):
        if b is 0:
            return 0
        elif is_odd(a):
            return mul_iter(half(a),double(b),result+b)
        elif a is 0:
            return result
        else:
            return mul_iter(half(a),double(b),result)
            
    return mul_iter(x,n,0)
    

