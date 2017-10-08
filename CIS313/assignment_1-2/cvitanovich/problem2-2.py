# Problem 2.2 - Brackets

# Node Class
class node(object):
	# constructor
	def __init__(self, value=None, next=None):
		self.value = value # Node value (data)
		self.next = next # Points to the next node
	# get node value
	def getVal(self):
		return self.value
	# get next node
	def getNext(self):
		return self.next
	# set next node
	def setNext(self, next):
		self.next = next

# Linked List Class
class linkedList:
	# constructor
	def __init__(self):
		self.head = None # Points to current node
		self.size = 0
	# insert a new node at head of linked list
	def insert(self, value):
		newNode = node(value) # New node instance with desired value
		newNode.setNext(self.head)
		self.head = newNode
		self.size += 1 # update list size
	# return size of linked list
	def listSize(self):
		print self.size
	# delete head and return its value
	def deleteHead(self):
		headValue = self.head.getVal()
		self.head = self.head.getNext()
		self.size -= 1 # update list size
		return headValue

# Stack Class
class stack:
	# constructor
	def __init__(self):
		self.stack = linkedList() # initialize empty linked list
		self.size = 0
	# push values onto stack
	def push(self, value):
		self.stack.insert(value) # push value onto stack
		self.size += 1
	# pop value off of stack
	def pop(self):
		if(self.is_empty()):
			return "StackError" # empty stack
		self.size -= 1
		return self.stack.deleteHead()
	# check if stack is empty
	def is_empty(self):
		if self.size == 0:
			return True
		return False

# Driver Code Starts Here
myStack = stack() # initialize empty stack

# Print Stack
import copy
def print_stack(s):
	str1 = ''
	tempStack = copy.deepcopy(s) # deep copy of stack to temporary stack object
	if tempStack.is_empty():
		print "Empty"
		return
	while(not tempStack.is_empty()):
		val = tempStack.pop()
		str1 = str(val) + str1
	print str1

# check if ch is a closed bracket
def isClosedBracket(ch):
	if(ch == '>' or ch == ']' or ch == ')'):
		return True
	else:
		return False

# check if a and b are a good pair of brackets (a is "open" and b is "closed")
def isGoodPair(left,right):
	if(left == '<' and right == '>'):
		return True
	elif(left == '(' and right == ')'):
		return True
	elif(left == '[' and right == ']'):
		return True
	else:
		return False

# check if brackets all match by counting them
def countCheckBrackets(s):
	count = [0,0,0,0,0,0] # corresponds with count of each char: []<>()
	for elem in s:
		if elem == '[':
			count[0] += 1
		elif elem == ']':
			count[1] += 1
		elif elem == '<':
			count[2] += 1
		elif elem == '>':
			count[3] += 1
		elif elem == '(':
			count[4] += 1
		elif elem == ')':
			count[5] += 1
	# now check the counts
	if count[0] == count[1] and count[2] == count[3] and count[4] == count[5]:
		return True # all brackets have a match
	else:
		return False # found unmatched brackets

# FUNCTION isWellFormed: CHECK IF STRING IS WELL FORMED
# check if the string is well formed
# recursive function (calls isWellFormed recursively to check if substrings are well formed)
def isWellFormedOld(s):
	# base case (empty stack) returns True (well formed)
	if(s.is_empty()):
		return True
	# otherwise check if first two brackets match
	top = s.pop()
	next = s.pop()
	# if top and next are a pair of brackets without a substring recurse on remaining stack
	if(isGoodPair(next,top)):
		# recurse on remaining stack with good pair removed (substring)
		return isWellFormed(s)
	# else remove outer brackets and recurse on remaining substring
	else:
		tempStack = stack() # create a new stack to push substring onto
		tempStack.push(next) # last popped element is part of substring 
		while(not s.is_empty()):
			tempStack.push(s.pop())
		# check if outer brackets are well formed
		# if they are well formed recurse on remaining substring
		last = tempStack.pop()
		if(isGoodPair(last,top)):
			# transfer back to original stack (to get order back)
			while(not tempStack.is_empty()):
				s.push(tempStack.pop())
			# recurse on substring
			return isWellFormed(s)
		else:
			# brackets do not match so the string is not well formed
			return False

def isWellFormed(s):
	# temporary storage stack
	tempStack = stack()
	# base case
	if(s.is_empty()):
		return True
	# remove all matching bracket pairs with nothing in between
	matchCount = 0
	matched = False
	top = s.pop()
	while(not s.is_empty()):
		next = s.pop()
		# pair does not match, so keep looking
		if(not isGoodPair(next,top)):
			matched = False
			# push top element onto temporary stack
			tempStack.push(top)
			top = next
		# found a matching pair without internal brackets, keep looking for more
		else:
			matched = True
			matchCount += 1
			if(not s.is_empty()):
				top = s.pop() # move on to next bracket
			else:
				top = None
	if(top != None):
		tempStack.push(top)
	if(matchCount == 0):
		return False # not well formed (should be at least one matching pair without internal substring)
	# push unmatched brackets from temporary stack back onto original stack
	while(not tempStack.is_empty()):
		s.push(tempStack.pop())
	# recurse on remaining substring
	return isWellFormed(tempStack)
		
		
# Process Text Input
def process(ln):
	# remove whitespace
	ln = ln.replace(" ","")
	str1 = list(ln)
	if fileinput.isfirstline():
		return
	theStack = stack()
	# push elements onto a stack
	for elem in str1:
		if elem != '\n':
			theStack.push(elem)
	# verify if the string is "Well Formed" using stack
	if(isWellFormed(theStack)):
		print "YES"
	else:
		print "NO"
	return

# Read text file for driver commands
import time
import fileinput
total = []
length = []
cnt = 1
for line in fileinput.input():
	t0 = time.time()
	process(line)
	t1 = time.time()
	total.append(t1 - t0)
	cnt += 2
	length.append(cnt)

# EXTRA ANALYSIS BELOW
if False:
	
	# plotting results
	import numpy as np
	import matplotlib.pyplot as plt

	# Create data
	N = 500
	colors = (0,0,0)
	area = np.pi*3

	# Plot
	plt.scatter(length, total, s=area, c=colors, alpha=0.5)
	plt.xlim(0,length[-1]+1)
	plt.ylim(0,max(total)+min(total))
	plt.title('Scatter plot pythonspot.com')
	plt.xlabel('x')
	plt.ylabel('y')
	plt.show()