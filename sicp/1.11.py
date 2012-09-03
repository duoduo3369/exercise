# coding=UTF8

def function_1_11(n):
	if n < 3:
		return n
	else:
		return  function_1_11(n-1) +\
                        2 * function_1_11(n-2) +\
                        3 * function_1_11(n-3)

def function_line(n):
        """ n < 3时，直接为n，大于3之后，才满足a,b,c = b,c,3*a+2*b+c的公式。    
        """
        def fun_iter(a,b,c,count):
                if count is 0:
                        return c
                else:
                        return fun_iter(b,c,3*a+2*b+c,count-1)
        if n < 3:
                return n
        else:
                return fun_iter(0,1,2,n-2)
