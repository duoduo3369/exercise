# coding=UTF8

"""
    在一个2**k * 2**k的方格里面有一个与其他的不同（黑色，其他为白色）
    将其他方格填满如下的三角格子
    **     **    *     *
    *       *    **   **
    1号    2号   3号   4号
"""


def init_chess_board(size):
    board = []
    for i in xrange(size):
        board.append([0 for i in xrange(size)])
    return board


def fill_chess_board(board,origin_row,origin_col,
                     target_row,target_col,size,tile):
    if size <= 1:
        return None
    tile += 1
    divided_size = size / 2

    left_up_box_row,left_up_box_col = origin_row,origin_col
    right_up_box_row,right_up_box_col = left_up_box_row,left_up_box_col + divided_size
    left_bottom_box_row,left_bottom_box_col = left_up_box_row + divided_size,left_up_box_col
    right_bottom_box_row,right_bottom_box_col = left_bottom_box_row,left_bottom_box_col  + divided_size

    if target_row < left_up_box_row + divided_size and \
       target_col < left_up_box_col + divided_size:
        fill_chess_board(board,left_up_box_row,left_up_box_col,
                     target_row,target_col,divided_size,tile)
    else:
        tg_row,tg_col = left_up_box_row + divided_size-1,left_up_box_col + divided_size-1
        board[tg_row][tg_col]=tile
        fill_chess_board(board,left_up_box_row,left_up_box_col,tg_row,tg_col,divided_size,tile)

    if target_row < right_up_box_row + divided_size and \
       target_col >= right_up_box_col:
        fill_chess_board(board,right_up_box_row,right_up_box_col,
                     target_row,target_col,divided_size,tile)
    else:
        tg_row,tg_col = right_up_box_row + divided_size-1,left_up_box_col
        board[tg_row][tg_col]=tile
        fill_chess_board(board,right_up_box_row,right_up_box_col,tg_row,tg_col,divided_size,tile)

    if target_row >= left_bottom_box_row and target_col < left_bottom_box_col + divided_size:
        fill_chess_board(board,left_bottom_box_row,left_bottom_box_col,
                     target_row,target_col,divided_size,tile)
    else:
        tg_row,tg_col = left_bottom_box_row, left_bottom_box_col + divided_size-1
        board[tg_row][tg_col]=tile
        fill_chess_board(board,left_bottom_box_row,left_bottom_box_col,
                     tg_row,tg_col,divided_size,tile)

    if target_row >= right_bottom_box_row and\
       target_col >= right_bottom_box_col:
        fill_chess_board(board,right_bottom_box_row,right_bottom_box_col,
                     target_row,target_col,divided_size,tile)
    else:
        tg_row,tg_col = right_bottom_box_row,right_bottom_box_col
        board[tg_row][tg_col]=tile
        fill_chess_board(board,right_bottom_box_row,right_bottom_box_col,
                     tg_row,tg_col,divided_size,tile)
        

def book(tr,tc,dr,dc,size):
    if size is 1:
        return None
    global tile
    t,tile = tile+1,tile+1
    s = size/2
    global board

    if dr < tr + s and dc < tc + s:
        book(tr,tc,dr,dc,s)
    else:
        board[tr+s-1][tc+s-1]=t
        book(tr,tc,tr+s-1,tc+s-1,s)

    if dr < tr+s and dc >=tc+s:
        book(tr,tc+s,dr,dc,s)
    else:
        board[tr+s-1][tc+s]=t
        book(tr,tc+s,tr+s-1,tc+s,s)

    if dr>=tr+s and dc < tc+s:
        book(tr+s,tc,dr,dc,s)
    else:
        board[tr+s][tc+s-1]=t
        book(tr+s,tc,tr+s,tc+s-1,s)

    if dr >= tr+s and dc>=tc+s:
        book(tr+s,tc+s,dr,dc,s)
    else:
        board[tr+s][tr+s]=t
        book(tr+s,tc+s,tr+s,tc+s,s)

        
        

size = 4
board = init_chess_board(size)
tile=0
#fill_chess_board(board,0,0,0,1,size,0)
book(0,0,0,1,size)
