# -*- coding: utf8 -*-
##
##有一颗二叉树，最大深度为D,且所有叶子的深度都相同。
##所有结点从左到右从上到下的编号为1,2,3，·····，2的D次方减1。
##在结点1处放一个小猴子，它会往下跑。
##每个内结点上都有一个开关，初始全部关闭，
##当每次有小猴子跑到一个开关上时，它的状态都会改变，当到达一个内结点时，
##如果开关关闭，小猴子往左走，否则往右走，直到走到叶子结点。
##
##一些小猴子从结点1处开始往下跑，最后一个小猴儿会跑到哪里呢？

def init_binary_tree(level):
    return [False for i in xrange(pow(2,level)-1)]

from math import floor,log
def monkey_tree(level,monkey_number):
    tree = init_binary_tree(level)
    earth = -1
    for monkey in xrange(monkey_number):
        root = 0
        lvl = int(floor(log(root+1,2)))
        # level->lvl from 0 to n-1
        while 1:
            #print 'root',root
            tree[root] = not tree[root]
            # 改变这个开关
            lvl = int(floor(log(2*root+2,2)))
            #print 'level',lvl,level
            # 下一层
            if not lvl < level:
                # 没有下一层退出
                earth = root
                break
            if not tree[root] is False:
                # 改变之前
                root = root * 2 + 1
            else:
                root = root * 2 + 2
    # 树里面的编号是从1开始的，而数组坐标是从0开始的，所以加1
    return earth + 1
                
            
        
    
