#define Type int
#include <math.h>
double log_base(double number,int base)
{
    return log(number)/log(base);
}
typedef struct{
    Type data;
    struct BinaryNode *left_child;
    struct BinaryNode *right_child;
}BinaryNode,*BinaryTree;

void setNode(BinaryNode* node,Type data,BinaryNode *left_child,BinaryNode *right_child)
{
    node->data = data;
    node->left_child = left_child;
    node->right_child = right_child;
}
BinaryNode* newNode()
{
    BinaryNode* node = (BinaryNode*)malloc(sizeof(BinaryNode));
    if(node)
    {
        setNode(node,-1,NULL,NULL);
    }
    return node;
}
void freeNode(BinaryNode* node)
{
    free(node);
}
void printNode(BinaryNode* node)
{
    printf("data:%d self_p:%p l_child_p:%p r_child_p:%p\n",
           node->data,node,node->left_child,node->right_child
           );
}
int printf_middle(Type element,int width,char fill)
{
    int i;
    for(i = 0; i < width/2; ++i)
    {
        printf("%c",fill);
    }
    printf("%d",element);
    for(i = 0; i < width/2; ++i)
    {
        printf("%c",fill);
    }
    return width+1;
}
void print_tree(Type tree[],int size,int total_width,char fill)
{
    int row,columns,col_width,i;
    int last_row = -1;
    for(i = 0; i < size; ++i)
    {
        row = (int)(floor(log_base(i+1, 2)));
        if(row != last_row)
        {
            printf("\n");
        }
        columns = (int)(pow(2,row));
        col_width = (int)(floor(total_width * 1.0 / columns));
        printf_middle(tree[i],col_width,fill);
        last_row = row;
    }

}

