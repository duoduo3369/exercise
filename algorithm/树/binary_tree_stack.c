
#define STACKSIZE 100

typedef struct{
    BinaryNode* list[STACKSIZE];
    int top_index;
}BinaryTreeStack;
BinaryTreeStack* initBinaryTreeStack()
{
    BinaryTreeStack* stack = (BinaryTreeStack*)malloc(sizeof(BinaryTreeStack));
    if(stack)
    {
        stack->top_index = -1;
        int i;
        for(i = 0; i < STACKSIZE; ++i)
        {
            stack->list[i] = NULL;
        }

    }
    return stack;
}
int binaryTreeStackNodeNumber(BinaryTreeStack* stack)
{
    return stack->top_index+1;
}
int isBinaryTreeStackEmpty(BinaryTreeStack* stack)
{
    if(stack->top_index == -1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int isBinaryTreeStackFull(BinaryTreeStack* stack)
{
    if(stack->top_index == STACKSIZE-1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int pushBinaryTreeStack(BinaryTreeStack* stack,BinaryNode* node)
{
    if(isBinaryTreeStackFull(stack))
    {
        return FALSE;
    }
    stack->top_index++;
    stack->list[stack->top_index] = node;
    return TRUE;

}
BinaryNode* popBinaryTreeStack(BinaryTreeStack* stack)
{
    if(isBinaryTreeStackEmpty(stack))
    {
        return NULL;
    }
    BinaryNode* top = stack->list[stack->top_index];
    stack->top_index--;
    return top;
}
BinaryNode* getBinaryTreeStackTop(BinaryTreeStack* stack)
{
    return stack->list[stack->top_index];
}
