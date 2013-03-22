#coding=utf8
import os, fnmatch
def all_files(root,patterns='*',single_level=False,yield_folders=False):
    patterns = patterns.split(';')
    for path, subdirs, files in os.walk(root):
        if yield_folders:
            files.extend(subdirs)
        files.sort()
        for name in files:
            for pattern in patterns:
                if fnmatch.fnmatch(name,pattern):
                    yield os.path.join(path,name)
                    break
        if single_level:
            break

def count_file_lines(path):
    count = -1
    for count,line in enumerate(open(path,'rU')):
        pass
    count += 1
    return count

TYPES = ['*.cpp','*.h','*.py','*.java']

if __name__ == '__main__':
    """
    将此文件放到GitHub根目录下即可查看代码行数，蛋疼的是在learn_python里面
    还收录了其他《python cookbook》这本书的源代码，删除这些源代码。
    btw，我觉得稳妥起见算出的行数除以2差不多就是我写的代码了，因为像django之类的项目
    会自动生成一些项目需要的文件，以及空行的问题，除以2应该是个不错的阀值。
    """
    count = 0
    for path in all_files('.',';'.join(TYPES)):
        print path
        count += count_file_lines(path)
    print count
