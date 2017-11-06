# Dictionaries for A and B Tiers
A_tier = {}
B_tier = {}

# Read Text File And Store Each Address In Correct Dictionary
import sys
data = (line.rstrip('\n') for line in open(sys.argv[1]))
nAddresses = int(next(data))
for lineNo in range(0,nAddresses):
	line = next(data).split(' ') # split line by whitespace
	if(line[1] == "A"):
		A_tier[line[0],lineNo] = int(line[2])
	elif(line[1] == "B"):
		B_tier[line[0],lineNo] = int(line[2])

# Heap Sorting
import heapq as hq

# Push A Tier Addresses Onto heapA
heapA = []
for key,value in A_tier.items():
	hq.heappush(heapA, (value, key[1], key[0]))

# Push B Tier Addresses Onto heapB
heapB = []
for key,value in B_tier.items():
	hq.heappush(heapB, (value, key[1], key[0]))

# Print Heapsorted A Tier Addresses
while heapA:
	top = hq.heappop(heapA)
	print top[2]

# Print Heapsorted B Tier Addresses
while heapB:
	top = hq.heappop(heapB)
	print top[2]