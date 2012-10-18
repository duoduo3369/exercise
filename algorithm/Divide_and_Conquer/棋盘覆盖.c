/*
    LOCAL:四大区域，从上到下，从左到右依次为0,1,2,3
    tile为每次填的骨牌数字号码，为一个全局变量
*/

#include<stdio.h>
#include <windows.h>

#define SIZE 16
#define LEFT_UP_LOCAL 1
#define RIGHT_UP_LOCAL 2
#define LEFT_BOTTOM_LOCAL 3
#define RIGHT_BOTTOM_LOCAL 4
#define LOCAL_NOT_FOUND 0
#define SPECIAL_POINT -1
typedef int TYPE;
typedef struct Point
{
    int row;
    int col;
} Point;

int tile = 0;


void set_point(Point *point,TYPE row,TYPE col);
void show_point(Point *point);
void init_board(TYPE board[][SIZE],Point *target);
void print_board(TYPE board[][SIZE]);
void fill_board(TYPE board[][SIZE],Point *origin,Point *target,int size);

int main()
{
    static TYPE board[SIZE][SIZE];

    Point *origin = (Point *)malloc(sizeof(Point));
    set_point(origin,0,0);
    Point *target = (Point *)malloc(sizeof(Point));
    set_point(target,0,1);
    printf("***init***\n");
    init_board(board,target);
    print_board(board);
    printf("\n");
    printf("***filled***\n");
    fill_board(board,origin,target,SIZE);
    print_board(board);
    return 0;
}
void set_point(Point *point,TYPE row,TYPE col)
{
    point->row = row;
    point->col = col;
}
void show_point(Point *point)
{
    printf("row:%3d col:%3d\n",point->row,point->col);
}
void init_board(TYPE board[][SIZE],Point *target)
{
    board[target->row][target->col] = SPECIAL_POINT;
}
void print_board(TYPE board[][SIZE])
{
    int i,j;
    for(i = 0; i < SIZE; ++i)
    {
        for(j = 0; j < SIZE; ++j)
        {
            switch(board[i][j] % 4)
            {
            case 0:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
                                        FOREGROUND_RED);
                break;
            case 1:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
                                        FOREGROUND_GREEN);
                break;
            case 2:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
                                        FOREGROUND_RED | FOREGROUND_GREEN);
                break;
            case 3:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
                                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;
            }
            printf("%3d ",board[i][j]);

        }
        printf("\n");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
                            FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
int find_local(Point *left_up_point,Point *right_up_point,
               Point *left_bottom_point,Point *right_bottom_point,
               Point *target)
{
    if(target->col < right_up_point->col && target->row < left_bottom_point->row)
    {
        return LEFT_UP_LOCAL;
    }
    if(target->col >= right_up_point->col && target->row < right_bottom_point->row)
    {
        return RIGHT_UP_LOCAL;
    }
    if(target->row >= left_bottom_point->row && target->col < right_bottom_point->col)
    {
        return LEFT_BOTTOM_LOCAL;
    }
    if(target->row >= right_bottom_point->row && target->col >= right_bottom_point->col)
    {
        return RIGHT_BOTTOM_LOCAL;
    }
    return LOCAL_NOT_FOUND;
}
Point* fill_one_box_left_up(TYPE board[][SIZE],Point *left_up_point,int next_size)
{
    int row,col;
    row = left_up_point->row + next_size -1;
    col = left_up_point->col + next_size -1;
    board[row][col] = tile;
    Point *target = (Point *)malloc(sizeof(Point));
    set_point(target,row,col);
    return target;
}
Point* fill_one_box_right_up(TYPE board[][SIZE],Point *right_up_point,int next_size)
{
    int row,col;
    row = right_up_point->row + next_size -1;
    col = right_up_point->col;
    board[row][col] = tile;
    Point *target = (Point *)malloc(sizeof(Point));
    set_point(target,row,col);
    return target;
}
Point* fill_one_box_left_bottom(TYPE board[][SIZE],Point *left_bottom_point,int next_size)
{
    int row,col;
    row = left_bottom_point->row;
    col = left_bottom_point->col + next_size -1;
    board[row][col] = tile;
    Point *target = (Point *)malloc(sizeof(Point));
    set_point(target,row,col);
    return target;
}
Point* fill_one_box_right_bottom(TYPE board[][SIZE],Point *right_bottom_point,int next_size)
{
    int row,col;
    row = right_bottom_point->row;
    col = right_bottom_point->col;
    board[row][col] = tile;
    Point *target = (Point *)malloc(sizeof(Point));
    set_point(target,row,col);
    return target;
}
void fill_board(TYPE board[][SIZE],Point *origin,Point *target,int size)
{
    if(size == 1)
    {
        return ;
    }
    int next_size = size / 2;
    int t = ++tile;
    Point *left_up_point = (Point *)malloc(sizeof(Point));
    Point *right_up_point = (Point *)malloc(sizeof(Point));
    Point *left_bottom_point = (Point *)malloc(sizeof(Point));
    Point *right_bottom_point = (Point *)malloc(sizeof(Point));
    set_point(left_up_point,origin->row,origin->col);
    set_point(right_up_point,origin->row,origin->col+next_size);
    set_point(left_bottom_point,origin->row+next_size,origin->col);
    set_point(right_bottom_point,origin->row+next_size,origin->col+next_size);

    int local = find_local(left_up_point,right_up_point,left_bottom_point,right_bottom_point,target);

    Point *target_lu,*target_ru,*target_lb,*target_rb;
    if(local == LEFT_UP_LOCAL)
    {
        target_lu = target;
        target_ru = fill_one_box_right_up(board,right_up_point,next_size);
        target_lb = fill_one_box_left_bottom(board,left_bottom_point,next_size);
        target_rb = fill_one_box_right_bottom(board,right_bottom_point,next_size);

    }
    if(local == RIGHT_UP_LOCAL)
    {
        target_lu = fill_one_box_left_up(board,left_up_point,next_size);
        target_ru = target;
        target_lb = fill_one_box_left_bottom(board,left_bottom_point,next_size);
        target_rb = fill_one_box_right_bottom(board,right_bottom_point,next_size);

    }
    if(local == LEFT_BOTTOM_LOCAL)
    {
        target_lu = fill_one_box_left_up(board,left_up_point,next_size);
        target_ru = fill_one_box_right_up(board,right_up_point,next_size);
        target_lb = target;
        target_rb = fill_one_box_right_bottom(board,right_bottom_point,next_size);

    }
    if(local == RIGHT_BOTTOM_LOCAL)
    {
        target_lu = fill_one_box_left_up(board,left_up_point,next_size);
        target_ru = fill_one_box_right_up(board,right_up_point,next_size);
        target_lb = fill_one_box_left_bottom(board,left_bottom_point,next_size);
        target_rb = target;
    }
    fill_board(board,left_up_point,target_lu,next_size);
    fill_board(board,right_up_point,target_ru,next_size);
    fill_board(board,left_bottom_point,target_lb,next_size);
    fill_board(board,right_bottom_point,target_rb,next_size);

}

