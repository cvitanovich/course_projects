import time

# Array for integer values
valArray = []

# Heap Sorting
import heapq as hq
lowerHeap = []
upperHeap = [] 

import sys
data = (line.rstrip('\n') for line in open(sys.argv[1]))
nAddresses = int(next(data))
nLines = 0
for lineNo in range(0,nAddresses):
	line = next(data).split(' ') # split line by whitespace
	valArray.append(float(line[0]))
	nLines += 1

def heapPeek(h):
	try:
		return h[0]
	except IndexError:
		return float('inf')

def printMedian(m):
	print ("%.1f" % m).replace(".0", "")

# lowerHeap is a maxheap for lower half of data
# upperHeap is a minheap for upper half of data
for i in range(0,nLines):
	
	# push new value onto lowerHeap by default
	# negate so that lowerHeap is max-heap
	hq.heappush(lowerHeap, -1 * valArray[i])
	
	# Switch values between upperHeap and lowerHeap until top of lowerHeap
	# is less than top of upperHeap (i.e. the heaps divide the values properly
	# into lower and upper halves).
	while( (-1 * heapPeek(lowerHeap)) > heapPeek(upperHeap) ):
		temp = -1 * hq.heappop(lowerHeap)
		hq.heappush(upperHeap, temp)

	# Check that heap sizes are approx equal (+/- 1)
	while( len(upperHeap) > (len(lowerHeap) + 1) ):
		temp = hq.heappop(upperHeap)
		hq.heappush(lowerHeap, -1 * temp)

	while( (len(upperHeap) + 1) < len(lowerHeap) ):
		temp = -1 * hq.heappop(lowerHeap)
		hq.heappush(upperHeap, temp)

	# Determine the median
	# Use printMedian function to produce output
	if len(upperHeap) == len(lowerHeap):
		# average the top values of each heap
		# to get the median
		lower = -1 * heapPeek(lowerHeap)
		upper = heapPeek(upperHeap)
		median = (lower + upper) * 0.5
		printMedian(median)	
	elif len(upperHeap) > len(lowerHeap):
		median = heapPeek(upperHeap)
		printMedian(median)
	else:
		median = -1 * heapPeek(lowerHeap)
		printMedian(median)

