# coding=UTF8

"""
    在一个2**k * 2**k的方格里面有一个与其他的不同（黑色，其他为白色）
    将其他方格填满如下的三角格子
    **     **    *     *
    *       *    **   **
    1号    2号   3号   4号

    思路：
        1、基本情况：如果为2*2，则下一次划分变长为1，直接返回
        2、找到target所在的区域，区域分为4快，从左到右，从上到下，定义为LOCAL
        3、根据区域填三角，例如，target在左上角区域（LEFT_UP）时，RIGHT_UP的左下角
        LEFT_BOTTOM的右上角，RIGHT_BOTTOM的左上角需要填数字。
        4、此时，每一个区域都有一个target，将每一个区域看做一个新棋盘，
        则出现最初的问题描述，递归条件完成，递归填写这四个区域。
"""

from pprint import pprint
TILE = [1,2,3,4]

LOCAL = {'LEFT_UP':0,'RIGHT_UP':1,
         'LEFT_BOTTOM':2,'RIGHT_BOTTOM':3}

def init_chess_board(size):
    board = []
    for i in xrange(size):
        board.append([0 for i in xrange(size)])
    return board

class Point(object):
    def __init__(self,row,col):
        self.row = row
        self.col = col
    def __repr__(self):
        return 'row:%s col:%s' % (self.row, self.col)
        
def fill_chess_board(board,origin_point,target_point,size):
    if size <= 1:
        return None
    next_size = size / 2
    global tile
    tile += 1
    left_up_point = Point(origin_point.row, origin_point.col)
    right_up_point = Point(origin_point.row, origin_point.col+next_size)
    left_bottom_point = Point(origin_point.row+next_size, origin_point.col)
    right_bottom_point = Point(origin_point.row+next_size, origin_point.col+next_size)

    #print left_up_point,right_up_point, left_bottom_point, right_bottom_point

    def find_target_local(target_point):
        #print target_point
        if target_point.row < left_bottom_point.row and \
           target_point.col < right_up_point.col:
            return LOCAL['LEFT_UP']
        if target_point.row < right_bottom_point.row and \
           target_point.col >= right_up_point.col:
            return LOCAL['RIGHT_UP']
        if target_point.row >= left_bottom_point.row and \
           target_point.col < right_bottom_point.col:
            return LOCAL['LEFT_BOTTOM']
        if target_point.row >= right_bottom_point.row and \
           target_point.col >= left_bottom_point.col:
            return LOCAL['RIGHT_BOTTOM']
        
    # test find_target_local     
    # return find_target_local(target_point)
    def fill_tile(target_point_local):
        def fill_one_left_up():
            #print 'lu lu lu'
            row,col = left_up_point.row+next_size-1,left_up_point.col+next_size-1
            board[row][col] = tile
            return Point(row,col)
        def fill_one_right_up():
            #print 'ru ru ru'
            row,col = right_up_point.row+next_size-1,right_up_point.col
            board[row][col] = tile
            return Point(row,col)
        def fill_one_left_bottom():
            #print 'lb lb lb'
            row,col = left_bottom_point.row,left_bottom_point.col+next_size-1
            board[row][col] = tile
            return Point(row,col)
        def fill_one_right_bottom():
            #print 'rb rb rb'
            row,col = right_bottom_point.row,right_bottom_point.col
            board[row][col] = tile
            return Point(row,col)
        target_list = {}    
        if find_target_local(target_point) is LOCAL['LEFT_UP']:
            ru_point = fill_one_right_up()
            lb_point = fill_one_left_bottom()
            rb_point = fill_one_right_bottom()
            target_list.update({'LEFT_UP':target_point,
                                'RIGHT_UP':ru_point,
                                'LEFT_BOTTOM':lb_point,
                                'RIGHT_BOTTOM':rb_point
                                })
            return target_list
        if find_target_local(target_point) is LOCAL['RIGHT_UP']:
            lu_point = fill_one_left_up()
            lb_point = fill_one_left_bottom()
            rb_point = fill_one_right_bottom()
            target_list.update({'LEFT_UP':lu_point,
                                'RIGHT_UP':target_point,
                                'LEFT_BOTTOM':lb_point,
                                'RIGHT_BOTTOM':rb_point
                                })
            return target_list
        if find_target_local(target_point) is LOCAL['LEFT_BOTTOM']:
            lu_point = fill_one_left_up()
            ru_point = fill_one_right_up()
            rb_point = fill_one_right_bottom()
            target_list.update({'LEFT_UP':lu_point,
                                'RIGHT_UP':ru_point,
                                'LEFT_BOTTOM':target_point,
                                'RIGHT_BOTTOM':rb_point
                                })
            return target_list
        if find_target_local(target_point) is LOCAL['RIGHT_BOTTOM']:
            lu_point = fill_one_left_up()
            ru_point = fill_one_right_up()
            lb_point = fill_one_left_bottom()
            target_list.update({'LEFT_UP':lu_point,
                                'RIGHT_UP':ru_point,
                                'LEFT_BOTTOM':lb_point,
                                'RIGHT_BOTTOM':target_point
                                })
            return target_list
    target_list = fill_tile(find_target_local(target_point))
    #print 'target list:'
    #print target_list['LEFT_UP'],target_list['RIGHT_UP'],target_list['LEFT_BOTTOM'],target_list['RIGHT_BOTTOM']
    #print board
    fill_chess_board(board,left_up_point,target_list['LEFT_UP'],next_size)
    fill_chess_board(board,right_up_point,target_list['RIGHT_UP'],next_size)
    fill_chess_board(board,left_bottom_point,target_list['LEFT_BOTTOM'],next_size)
    fill_chess_board(board,right_bottom_point,target_list['RIGHT_BOTTOM'],next_size)
        


        

size = 8
board = init_chess_board(size)
tile = 0
lu,ru,lb,rb = Point(0,1),Point(1,2),Point(3,1),Point(2,2)
origin_point,target_point = Point(0,0),Point(0,1)
board[target_point.row][target_point.col] = '*'
fill_chess_board(board,origin_point,target_point,size)

from pprint import pprint

import unittest

class TestFindTargetLocal(unittest.TestCase):
    def test_lu(self):
         self.assertEqual(LOCAL['LEFT_UP'],
                          fill_chess_board(board,origin_point,lu,size,0))
    def test_ru(self):
         self.assertEqual(LOCAL['RIGHT_UP'],
                          fill_chess_board(board,origin_point,ru,size,0))
    def test_lb(self):
         self.assertEqual(LOCAL['LEFT_BOTTOM'],
                          fill_chess_board(board,origin_point,lb,size,0))
    def test_rb(self):
         self.assertEqual(LOCAL['RIGHT_BOTTOM'],
                          fill_chess_board(board,origin_point,rb,size,0))

def test():
    unittest.main()
