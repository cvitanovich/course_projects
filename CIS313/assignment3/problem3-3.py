# TIMING: Average time for 20 operations is about 0.0035 seconds
# THIS IS THE SLOWEST IMPLEMENTATION
# BECAUSE OF ALL THE OVERHEAD OF TRANSFERING NODES BETWEEN THE TWO TREES



# Import module rbTree for Red Black Tree Class and Helper Functions
# This module is found in rbTree.py
import rbTree as rbt
import time
		
# Initialize Empty Trees (2 Of Them)
lowerT = rbt.rbTree()
upperT = rbt.rbTree()
	
# Read Text File And Process Instructions
import sys
data = (line.rstrip('\n') for line in open(sys.argv[1]))
nActions = int(next(data))

# tree max
def treeMax(T):
	max = T.maximum().getVal()
	if(max == None):
		max = float("inf")
	return max

# tree min
def treeMin(T):
	min = T.minimum().getVal()
	if(min == None):
		min = -1*float("inf")
	return min

# 2 Tree Median (Uses 2 Trees)
def median2Tree(lowT,hiT):
	# print median
	#print "sizes are " + str(lowT.getSize()) + " " + str(hiT.getSize())
	if( lowT.getSize() == hiT.getSize() ):
		x = lowT.maximum().getVal()
		y = hiT.minimum().getVal()
		print '{0:g}'.format( (float(x)+float(y))/float(2) )
	elif( lowT.getSize() > hiT.getSize() ):
		print '{0:g}'.format( float(treeMax(lowT)) )
	else:
		print '{0:g}'.format( float(treeMin(hiT)) )

# tree fixup (maintains properties)
def tree_fixup(lowT,hiT):

	if(treeMax(lowT) != float("inf") and treeMin(hiT) != -1*float("inf")):
		while( treeMax(lowT) > treeMin(hiT) ):
			x = treeMax(lowT)
			rbt.removeNode(lowT,x)
			rbt.insertNode(hiT,x)
	
	
	# make trees approximately equal size
	while( lowT.getSize() > (hiT.getSize() + 1) ):
		x = treeMax(lowT)
		rbt.removeNode(lowT,x)
		rbt.insertNode(hiT,x)
	
	while( (lowT.getSize() + 1) < hiT.getSize() ):
		x = treeMin(hiT)
		rbt.removeNode(hiT,x)
		rbt.insertNode(lowT,x)
	
	# Switch values between hiT and lowT until max of lowT
	# is less than min of hiT (i.e. the trees divide the values properly
	# into lower and upper halves).
	
	if(treeMax(lowT) == float("inf") or treeMin(hiT) == -1*float("inf")):
		return
	

	
# ADD2 (Uses 2 Trees)
def add2(lowT,hiT,k):
	# add new value to lower tree by default
	rbt.insertNode(lowT, k)
	# fix properties
	tree_fixup(lowT,hiT)
	# print median
	median2Tree(lowT,hiT)


# REMOVE2 (Uses 2 Trees)
def remove2(lowT,hiT,k):
	# remove node
	node1 = lowT.search(k)
	node2 = hiT.search(k)
	if node1.getVal() != None:
		rbt.removeNode(lowT,k)
		tree_fixup(lowT,hiT)
		median2Tree(lowT,hiT)
	elif node2.getVal() != None:
		rbt.removeNode(hiT,k)
		tree_fixup(lowT,hiT)
		median2Tree(lowT,hiT)
	else:
		print "TreeError"
	
	
for lineNo in range(0,nActions):
	line = next(data).split(' ') # split line by whitespace
	if(line[0] == "add"):
		add2(lowerT,upperT, line[1])
	elif(line[0] == "remove"):
		remove2(lowerT,upperT, line[1])
	elif(line[0] == "print"):
		print "Lower: "
		printTree(lowerT)
		print "Upper: "
		printTree(upperT)
	elif(line[0] == "start"):
		start = time.time()
	elif(line[0] == "end"):
		end = time.time()
		print("Elapsed Time = " + str(end-start))