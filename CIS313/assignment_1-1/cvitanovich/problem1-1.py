# Problem 1.1

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

# Stack Driver Code Starts Here
myStack = stack() # initialize empty stack

# Print Stack
import copy
def print_stack(s):
	tempStack = copy.deepcopy(s) # deep copy of stack to temporary stack object
	if tempStack.is_empty():
		print "Empty"
		return
	while(not tempStack.is_empty()):
		val = tempStack.pop()
		print val,
	print
# Process Text Input
def process(ln):
	ln = ln.split() # split line by whitespace
	if ln[0] == "print":
		print_stack(myStack)
	elif ln[0] == "pop":
		print myStack.pop()
	elif ln[0] == "push":
		myStack.push(ln[1])
		
# Read text file for driver commands
import fileinput
for line in fileinput.input():
    process(line)

# Ignore
if False:
	import sys
	with open(sys.argv[1], 'r') as f:
		contents = f.read()
	print contents


		
		