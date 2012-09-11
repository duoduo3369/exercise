# 
import os
import fnmatch

pattern = '*.*'

def ls(dir='.',file_type = '*',pattern=pattern):
    for file in os.listdir(dir):
        if fnmatch.fnmatch(file, file_type):
            print('Filename: %-25s %s' % (file, fnmatch.fnmatch(file, pattern)))
            
