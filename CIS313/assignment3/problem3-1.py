# TIMING: Average time for 20 operations is about 0.0007 seconds
# THIS IS THE FASTEST IMPLEMENTATION
# ABOUT 2X FASTER THAN PROBLEM 2
# ABOUT 4X FASTER THAN PROBLEM 3
# THERE IS NO NEED TO CALCULATE THE MEDIAN FOR THIS PROBLEM
# SO IT IS FASTER

# Import module rbTree for Red Black Tree Class and Helper Functions
# This module is found in rbTree.py
import rbTree as rbt
import time
		
# Initialize Empty Tree
myTree = rbt.rbTree()
	
# Read Text File And Process Instructions
import sys
data = (line.rstrip('\n') for line in open(sys.argv[1]))
nActions = int(next(data))
for lineNo in range(0,nActions):
	line = next(data).split(' ') # split line by whitespace
	if(line[0] == "insert"):
		rbt.insertNode(myTree, line[1])
	elif(line[0] == "remove"):
		rbt.removeNode(myTree, line[1])
	elif(line[0] == "search"):
		rbt.searchTree(myTree, line[1])
	elif(line[0] == "print"):
		rbt.printTree(myTree)
	elif(line[0] == "max"):
		rbt.printMax(myTree)
	elif(line[0] == "min"):
		rbt.printMin(myTree)
	elif(line[0] == "start"):
		start = time.time()
	elif(line[0] == "end"):
		end = time.time()
		print("Elapsed Time = " + str(end-start))


	
					
					
					
					