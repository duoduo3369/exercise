#define TYPE int
void print_array(TYPE *array,int length)
{
    int i;
    for(i = 0; i < length; ++i)
    {
        printf("%d ",array[i]);
    }
    printf("\n");
}
