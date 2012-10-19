#define TRUE 1
#define FALSE 0

#include<stdio.h>
#include <stdlib.h>

#include "binary_tree.c"
#include "binary_tree_stack.c"

void test_binary_tree();
void test_binary_tree_print();
void test_binary_tree_stack();
void test_binary_tree_stack_push_pop_many();
void test_binary_tree_stack_push_pop_one();

int main()
{
    test_binary_tree_print();

//    test_binary_tree_stack();
    return 0;
}
void test_binary_tree()
{
    BinaryNode *node_1 = NULL;
    node_1 = newNode();
    BinaryNode *node_2 = newNode();
    setNode(node_1,12,node_2,NULL);
    printf("node_1 pointer:%p\n",node_1);
    printf("node_2 pointer:%p\n",node_2);
    printNode(node_1);
    printNode(node_2);
    freeNode(node_1);
    node_1 = NULL;
    freeNode(node_2);
    node_2 = NULL;
    printf("node_1 pointer:%p\n",node_1);
    printf("node_2 pointer:%p\n",node_2);
}
void test_binary_tree_print()
{
    static Type tree[8] = {1,2,3,4,5,6,7,8};
    print_tree(tree,8,36,' ');

}
void test_binary_tree_stack_push_pop_one()
{
    BinaryTreeStack* stack = initBinaryTreeStack();
    BinaryNode *node_1 = newNode();
    BinaryNode *node_2 = newNode();
    BinaryNode *node_3 = newNode();
    BinaryNode *node_4 = newNode();
    setNode(node_1,11,node_2,NULL);
    setNode(node_2,22,NULL,NULL);
    setNode(node_3,33,NULL,NULL);
    setNode(node_4,44,NULL,NULL);
    printNode(node_1);
    printNode(node_2);
    printNode(node_3);
    printNode(node_4);
    pushBinaryTreeStack(stack,node_1);
    pushBinaryTreeStack(stack,node_2);
    pushBinaryTreeStack(stack,node_3);
    pushBinaryTreeStack(stack,node_4);
    printf("node number:%d\n",binaryTreeStackNodeNumber(stack));
    printNode(popBinaryTreeStack(stack));
    printNode(popBinaryTreeStack(stack));
    printNode(popBinaryTreeStack(stack));
    printNode(popBinaryTreeStack(stack));
    printf("node number:%d\n",binaryTreeStackNodeNumber(stack));

    freeNode(node_1);
    freeNode(node_2);
    freeNode(node_3);
    freeNode(node_4);

}
void test_binary_tree_stack_push_pop_many()
{
    BinaryTreeStack* stack = initBinaryTreeStack();
    printf("sizeof stack:%d \n",sizeof(*stack));
    int i;
    for(i = 0; i < STACKSIZE+10;i++)
    {
        if(pushBinaryTreeStack(stack,newNode()))
        {
            continue;
        }
        break;
    }
    printf("many:%d \n",binaryTreeStackNodeNumber(stack));
    for(i = 0; i < STACKSIZE/2; ++i)
    {
        if(popBinaryTreeStack(stack))
        {
            continue;
        }
        break;
    }
    printf("many:%d \n",binaryTreeStackNodeNumber(stack));
    for(i = 0; i < STACKSIZE; ++i)
    {
        if(popBinaryTreeStack(stack))
        {
            continue;
        }
        break;
    }
    printf("many:%d \n",binaryTreeStackNodeNumber(stack));
    free(stack);
}
void test_binary_tree_stack_push_pop()
{

}
