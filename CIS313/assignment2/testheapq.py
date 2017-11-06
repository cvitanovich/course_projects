import heapq as hq
import numpy as np
import time

tm = []
def heapsort(iterable):
	h = []
	for value in iterable:
		hq.heappush(h,value)
	return [hq.heappop(h) for i in range(len(h))]

def selectionSort(alist):
   for fillslot in range(len(alist)-1,0,-1):
       positionOfMax=0
       for location in range(1,fillslot+1):
           if alist[location]>alist[positionOfMax]:
               positionOfMax = location

       temp = alist[fillslot]
       alist[fillslot] = alist[positionOfMax]
       alist[positionOfMax] = temp


sz = range(2,10**4,500)
for i in sz:
	a = np.random.rand(i)
	t0 = time.time()
	#selectionSort(a)
	heapsort(a)
	t1 = time.time()
	tm.append(t1-t0)
	print tm[-1]
	print i

import matplotlib.pyplot as plt

plt.plot(sz,tm,'r')
plt.show()