# coding=UTF8
import collections


# Counter 是一个字典
c = collections.Counter()
print 'Initial :', c

# 检查字符串的时候挺好用的
c.update('abcdaab')
print 'Sequence:', c

c.update({'a':1, 'd':5})
print 'Dict    :', c

# 准换为list
list(c.elements())

# 输出一样
print collections.Counter(['a', 'b', 'c', 'a', 'b', 'b'])
print collections.Counter({'a':2, 'b':3, 'c':1})
print collections.Counter(a=2, b=3, c=1)
