# Problem 1.2

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

# Double Ended Linked List Class
class doubleEndedLinkedList:
	# constructor
	def __init__(self):
		self.head = None # Points to oldest node in list
		self.tail = None # Points to newest node
		self.size = 0
	# insert a new node at TAIL of linked list
	def insertAtTail(self, value):
		newNode = node(value) # New node instance with desired value
		if(self.size == 0):
			self.head = newNode
			self.tail = self.head
			self.size += 1 # update list size
		else:
			self.tail.setNext(newNode)
			self.tail = newNode
			self.size += 1
	# return size of linked list
	def listSize(self):
		print self.size
	# delete head and return its value
	def deleteHead(self):
		headValue = self.head.getVal()
		self.head = self.head.getNext()
		self.size -= 1 # update list size
		return headValue

# Queue Class
class queue:
	# constructor
	def __init__(self):
		self.queue = doubleEndedLinkedList() # initialize empty linked list
		self.size = 0
	def enqueue(self,value):
		self.queue.insertAtTail(value) # enqueue new node with value
		self.size += 1
		# pop value off of stack
	def dequeue(self):
		if(self.is_empty()):
			return "QueueError" # empty queue
		self.size -= 1
		return self.queue.deleteHead()
	# check if queue is empty
	def is_empty(self):
		if self.size == 0:
			return True
		return False

# Queue Driver Code Starts Here
myQueue = queue() # initialize empty queue

# Print Queue
import copy
def print_queue(q):
	tempQueue = copy.deepcopy(q) # deep copy of queue to temporary queue object
	if tempQueue.is_empty():
		print "Empty"
		return
	while(not tempQueue.is_empty()):
		val = tempQueue.dequeue()
		print val,
	print

# Process Text Input
def process(ln):
	ln = ln.split() # split line by whitespace
	if ln[0] == "print":
		print_queue(myQueue)
	elif ln[0] == "dequeue":
		print myQueue.dequeue()
	elif ln[0] == "enqueue":
		myQueue.enqueue(ln[1])
		
# Read text file for driver commands
import fileinput
for line in fileinput.input():
    process(line)
	
	
	
	
	