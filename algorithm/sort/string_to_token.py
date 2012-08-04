import shlex

def string_to_token(input_string,whitespace = ',;[]'):
    lexer = shlex.shlex(input_string)
    lexer.whitespace += whitespace
    token = [int(t) for t in lexer]
    return token
