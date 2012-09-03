def sine(angle):
    def cube(n):
        return n * n * n
    def p(x):
        """ p -> sin(angle/3) """
        return 3 * x - 4 * cube(x)
    if abs(angle) < 0.1:
        return angle
    else:
        return p(sine(angle/3.0))
