def binary_search(L,key):
    low,high = 0,len(L)
    while low <= high:
        mid = (low + high)/ 2
        if L[mid] is key:
            return mid
        elif L[mid] < key:
            low = mid + 1
        else:
            high = mid - 1
    return None

L = range(500)
print L
for i in xrange(100):
    key = i * 2 + 1
    print "search %s,local %s" % (key,binary_search(L,key))
