# TIMING: Average time for 20 operations is about 0.0015 seconds
# THIS IS 2X FASTER THAN THE CODE FOR PROBLEM 3
# BUT 2X SLOWER THAN PROBLEM 1
# PROBABLY BECAUSE IT HAS TO CALCULATE THE MEDIAN

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
	if(line[0] == "add"):
		rbt.add(myTree, line[1])
	elif(line[0] == "remove"):
		rbt.remove(myTree, line[1])
	elif(line[0] == "print"):
		rbt.printTree(myTree)
	elif(line[0] == "start"):
		start = time.time()
	elif(line[0] == "end"):
		end = time.time()
		print("Elapsed Time = " + str(end-start))