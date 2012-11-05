# coding=utf8
def maxSubSum(array,left,right):
    #分治
    sum = 0
    # 只有一个元素时，如果为负数，则为0(题目要求，全为负数时，和为0)
    if(left == right):
        if array[left] > 0:
            sum = array[left]
        else:
            sum = 0
    else:
        center = (left + right) / 2
        left_max_sum = maxSubSum(array,left,center)
        right_max_sum = maxSubSum(array,center+1,right)


        #求左半段中包含最后一个元素的最大值

        sum_left,temp_sum_left = 0,0

        for i in xrange(center,left-1,-1):
            temp_sum_left += array[i]
            if temp_sum_left > sum_left:
                sum_left = temp_sum_left

        #求右半段中包含最后一个元素的最大值

        sum_right,temp_sum_right = 0,0

        for i in range(center+1,right):
            temp_sum_right += array[i]
            if temp_sum_right > sum_right:
                sum_right = temp_sum_right

        sum = sum_left + sum_right
        if sum < left_max_sum:
            sum = left_max_sum
        if sum < right_max_sum:
            sum = right_max_sum
        return sum

# 从第一个元素开始遍历
# sum是最大字段和，temp_sum[j]为某子段的和
# temp_sum[j] = max(1<=i<=j){∑(i~j)a[k]},1<=j<=n
# 最大字段和即为max(temp_sum[j])
# 由temp_sum[j]的定义知
# 当temp_sum[j-1]>0时,temp_sum[j] = temp_sum[j-1]+a[j]
# 当temp_sum[j-1]<=0时(负数的话越加越小),temp_sum[j] = a[j]
# 即，如果前面的字段>0的话，再加这一段可以继续积累
# 如果前面的已经<0则加前面的不会是最大，(负数越加越小),放弃前面所有的元素字段
# so -> temp_sum[j] = max{temp_sum[j-1]+a[j],a[j]}
def maxSubSum_dp(array):
    sum ,temp_sum = 0,0
    for i in xrange(0,len(array)):
        if temp_sum > 0:
            temp_sum += array[i]
        else:
            temp_sum = array[i]
        if temp_sum > sum:
            sum = temp_sum
    return sum
        

array = [-2,11,-4,13,-5,-2]
maxsum = maxSubSum(array,0,len(array)-1)
print maxsum

maxsum_dp = maxSubSum_dp(array)
print maxsum_dp
