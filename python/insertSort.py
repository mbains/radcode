def insertSort(aray):
    for i in xrange(len(aray)):
        for j in xrange(i):
            if aray[j] > aray[i]:
                num = aray[i]
                k = i - 1
                while k>=j:
                    aray[k+1] = aray[k]
                    k -= 1
                aray[j] = num




