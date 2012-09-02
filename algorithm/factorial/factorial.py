def factorial(n):
    if n is 1:
        return 1
    return n * factorial(n-1)

def factorial_line(n):
    def factorial_iter(product,counter,max_count):
        if counter > max_count:
            return product
        else:
            return factorial_iter(product*counter, counter + 1,max_count)
    return factorial_iter(1,1,n)
    

