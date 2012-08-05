import shlex

def string_to_token(input_string,whitespace = ',;[]'):
    lexer = shlex.shlex(input_string)
    lexer.whitespace += whitespace
    token = [int(t) for t in lexer]
    return token

def isListArray(input_array):
    if isinstance(input_array,list) == False:
        print 'Error: When you use insert_sort function, please make sure your argument is a list'
        return False
    return True
