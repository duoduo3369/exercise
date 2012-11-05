#include<stdio.h>
int maxSubSum(int *array,int left,int right)
{
    int sum = 0;
    if(left == right)
    {
        sum = array[left] > 0 ? array[left]:0;
    }
    else
    {
        int center = (left + right) / 2;
        int left_sum = maxSubSum(array,left,center);
        int right_sum = maxSubSum(array,center+1,right);
        int sleft = 0,temp_sleft =0;
        int i;
        for(i = center; i >= left; i--)
        {
            temp_sleft += array[i];
            if(temp_sleft > sleft)
            {
                sleft = temp_sleft;
            }
        }
        int sright = 0,temp_sright = 0;
        for(i = center+1; i <= right; i++)
        {
            temp_sright += array[i];
            if(temp_sright > sright)
            {
                sright = temp_sright;
            }
        }
        sum = sleft + sright;
        if(sum < left_sum)
        {
            sum = left_sum;
        }
        if(sum < right_sum)
        {
            sum = right_sum;
        }
    }
    return sum;
}
int main()
{
    int array[] = {-2,11,-4,13,-5,-2};
    int length = 6;

    int sum = maxSubSum(array,0,5);
    printf("%d ",sum);
//    printf
    return 0;
}
