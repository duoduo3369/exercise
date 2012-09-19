# coding=UTF8
try:
    from cStringIO import StringIO
except:
    from StringIO import StringIO
from copy import copy
def permutation(List,first,last,result):
    ## 递归解法，怎么返回生成list而不是打印???因为最后还有一个交换
    ## 面向对象
    """产生从first到last的全排列
        R = {r1,r2,r3,...,rn}
        Ri = R - {ri}
        1、n=1 Perm(R) = r
        ## 如果只有一个元素，则list就是全排列 
        2、n>1 Perm(R) = (ri)(Perm(Ri))        
        ## 否则排列就是([取出一个元素][list剩下的元素])
    """
    def swap(L,from_index,to_index):
        L[from_index],L[to_index] = L[to_index],L[from_index]
        return L

    if first is last:
        #return List        
        #print List
        result.append(copy(List))
    else:
        for i in xrange(first,last):
            swap(List,first,i)
            # 交换第一个和第i个，然后使用k+1~last-->Ri
            permutation(List,first+1,last,result)
            swap(List,first,i)
            # 换回来，保持数组不变性，
            #保证每次交换的第一个函数按照 Ri = R - {ri}的顺序生成Ri

class FullPermutation(object):
    def __init__(self):
        self.result = [] 
    def append(self,List):
        self.result.append(List)
    def permutation(self,List,first,last):
        ## 递归解法，怎么返回生成list而不是打印???因为最后还有一个交换
        ## 面向对象
        """产生从first到last的全排列
            R = {r1,r2,r3,...,rn}
            Ri = R - {ri}
            1、n=1 Perm(R) = r
            ## 如果只有一个元素，则list就是全排列 
            2、n>1 Perm(R) = (ri)(Perm(Ri))        
            ## 否则排列就是([取出一个元素][list剩下的元素])
        """
        def __swap(L,from_index,to_index):
            L[from_index],L[to_index] = L[to_index],L[from_index]
            return L

        if first is last:
            #return List        
            #print List
            self.result.append(copy(List))
        else:
            for i in xrange(first,last):
                __swap(List,first,i)
                # 交换第一个和第i个，然后使用k+1~last-->Ri
                self.permutation(List,first+1,last)
                __swap(List,first,i)
                # 换回来，保持数组不变性，
                #保证每次交换的第一个函数按照 Ri = R - {ri}的顺序生成Ri
    def print_result(self):
        result = self.result
        for r in result:
            print r
def usage(l):       
    #l = range(4)
    full_permutation = FullPermutation()
    full_permutation.permutation(l,0,len(l))
    many = len(full_permutation.result)
    cut_star_line = '*' * len(l) * 3
    print 'has %s results' % (many)
    print cut_star_line
    full_permutation.print_result()


