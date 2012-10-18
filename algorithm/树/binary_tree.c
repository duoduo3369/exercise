#define Type int

typedef struct{
    Type data;
    struct BinaryNode *left_child;
    struct BinaryNode *right_child;
}BinaryNode,*BinaryTree;
BinaryNode* newNode()
{
    BinaryNode* node = (BinaryNode*)malloc(sizeof(BinaryNode));
    if(node)
    {
        node->left_child = NULL;
        node->right_child = NULL;
    }
    return node;
}
void freeNode(BinaryNode* node)
{
    free(node);
}
void setNode(BinaryNode* node,Type data,BinaryNode *left_child,BinaryNode *right_child)
{
    node->data = data;
    node->left_child = left_child;
    node->right_child = right_child;
}
void printNode(BinaryNode* node)
{
    printf("data:%d left_child_pointer:%p right_child_pointer:%p\n",
           node->data,node->left_child,node->right_child
           );
}
