#define TRUE 1
#define FALSE 0

#include<stdio.h>
#include <stdlib.h>

#include "binary_tree.c"
#include "binary_tree_stack.c"
#include "traversal.c"

void test_binary_tree();
void test_binary_tree_print();
void test_binary_tree_stack();
void test_binary_tree_stack_push_pop_many();
void test_binary_tree_stack_push_pop_one();
BinaryTree init_tree();
BinaryTree init_tree2();

int main()
{

    BinaryTree tree = init_tree();
    printf("************************\n");
    printf("preorder:\n");
    preorder(tree);
    printf("************************\n");
    printf("inorder:\n");
    inorder(tree);
    //BinaryTree tree = init_tree2();
    printf("************************\n");
    printf("postorder:\n");
    postorder(tree);
    return 0;
}
BinaryTree init_tree2()
{
    BinaryNode *root = newNode();
    BinaryNode *node_1 = newNode();
    BinaryNode *node_2 = newNode();
    BinaryNode *node_3 = newNode();
    setNode(root,0,node_1,node_2);
    setNode(node_1,1,NULL,node_3);
    setNode(node_2,2,NULL,NULL);
    setNode(node_3,3,NULL,NULL);


    return root;
}
BinaryTree init_tree()
{
    BinaryNode *root = newNode();
    BinaryNode *node_1 = newNode();
    BinaryNode *node_2 = newNode();
    BinaryNode *node_3 = newNode();
    BinaryNode *node_4 = newNode();
    BinaryNode *node_5 = newNode();
    BinaryNode *node_6 = newNode();
    BinaryNode *node_7 = newNode();
    BinaryNode *node_8 = newNode();
    BinaryNode *node_9 = newNode();

    setNode(root,0,node_1,node_2);
    setNode(node_1,1,node_3,node_4);
    setNode(node_2,2,node_5,NULL);
    setNode(node_3,3,node_6,NULL);
    setNode(node_4,4,node_7,node_8);
    setNode(node_5,5,NULL,NULL);
    setNode(node_6,6,node_9,NULL);
    setNode(node_7,7,NULL,NULL);
    setNode(node_8,8,NULL,NULL);
    setNode(node_9,9,NULL,NULL);
    return root;

}
void test_binary_tree()
{
    BinaryNode *node_1 = newNode();
    BinaryNode *node_2 = newNode();

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
        if(pushBinaryTreeStack(stack,newNode(-1)))
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
