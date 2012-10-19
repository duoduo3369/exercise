void preorder(BinaryTree root)
{
    BinaryTreeStack* stack = initBinaryTreeStack();
    pushBinaryTreeStack(stack,root);
    BinaryNode *top = NULL;
    while(!isBinaryTreeStackEmpty(stack))
    {
        top = popBinaryTreeStack(stack);
        printNode(top);
        if(top->right_child)
        {
            pushBinaryTreeStack(stack,(BinaryNode *)top->right_child);
        }
        if(top->left_child)
        {
            pushBinaryTreeStack(stack,(BinaryNode *)top->left_child);
        }
    }
}
void inorder(BinaryTree root)
{
    BinaryTreeStack* stack = initBinaryTreeStack();
    pushBinaryTreeStack(stack,root);
    BinaryNode *top = NULL;
    while(!isBinaryTreeStackEmpty(stack))
    {
        top = getBinaryTreeStackTop(stack);
        while(top->left_child)
        {
            pushBinaryTreeStack(stack,(BinaryNode *)top->left_child);
            top = getBinaryTreeStackTop(stack);
        }
        do
        {
            top = popBinaryTreeStack(stack);
            printNode(top);
            if(isBinaryTreeStackEmpty(stack))
            {
                break;
            }
        }while(!top->right_child);
        if(top->right_child)
        {
            pushBinaryTreeStack(stack,(BinaryNode *)top->right_child);
        }

    }
}
void postorder(BinaryTree root)
{
    BinaryTreeStack* stack = initBinaryTreeStack();
    pushBinaryTreeStack(stack,root);
    BinaryNode *top = NULL;
    BinaryNode * stack_top = NULL;
    while(!isBinaryTreeStackEmpty(stack))
    {
        top = getBinaryTreeStackTop(stack);
        while(top->left_child)
        {
            pushBinaryTreeStack(stack,(BinaryNode *)top->left_child);
            top = getBinaryTreeStackTop(stack);
        }
        if(top->right_child)
        {
            pushBinaryTreeStack(stack,(BinaryNode *)top->right_child);
            continue;
        }
        do
        {
            top = popBinaryTreeStack(stack);
            printNode(top);
            if(isBinaryTreeStackEmpty(stack))
            {
                return;
            }
            stack_top = getBinaryTreeStackTop(stack);
        }while(stack_top->right_child == NULL || stack_top->right_child == top);
        if(stack_top->right_child)
        {
            pushBinaryTreeStack(stack,(BinaryNode *)stack_top->right_child);
            continue;
        }
    }
}

