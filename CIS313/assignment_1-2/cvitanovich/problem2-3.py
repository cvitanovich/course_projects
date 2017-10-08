# Problem 2.3 Restaurant

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
	if len(ln) == 1:
		numRestaurants = int(ln[0]) # number of Restaurants
		return numRestaurants
	elif len(ln) == 2:
		a = [int(ln[0]), int(ln[1])] # store values in 1x2 arrays
		myQueue.enqueue(a)
		return 0
	
# Calculate Restaurant Hops
def try2hop(q,start):
	tempQueue = copy.deepcopy(q) # deep copy of queue for processing
	# reorder queue to starting restaurant
	while start > 0:
		temp = tempQueue.dequeue()
		tempQueue.enqueue(temp)
		start -= 1
	# now try to hop through cycle of restaurants without reaching energy <= 0
	temp = tempQueue.dequeue()
	energy = temp[0] - temp[1]
	# keep hopping until energy exhausted or cycle complete
	while energy > 0:
		if tempQueue.is_empty():
			# success!
			return True
		else:
			# calculate energy remaining after hop to next restaurant
			temp = tempQueue.dequeue()
			energy = energy + temp[0] - temp[1]
	# failure: ran out of energy before completing restaurant cycle
	return False

# Find the first restaurant that is a good starting point
def findGoodStart(q,n):
	for start in range(0,n):
		result = try2hop(q,start)
		if(result):
			return start
	return None
			
	
# Read text file for driver commands
import fileinput
for line in fileinput.input():
    n = process(line)
    if n > 0:
    	numRestaurants = n

# Print a good starting point
import time
t0 = time.time()
x = findGoodStart(myQueue,numRestaurants)
t1 = time.time()
total = t1 - t0
print x
#print "Best start is " + str(x)
#print "Processing time for " + str(numRestaurants) + " Lines = " + str(total)