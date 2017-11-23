# module rbTree
# by Andrew Cvitanovich (Nov '17)

# Color Enumeration
def enum(**enums):
	return type('Enum', (), enums)
Color = enum(RED = 0, BLACK = 1)

# Red Black Node Class
class rbNode(object):
	# constructor
	def __init__(self, value=None, color=Color.BLACK, 
		parent=None, leftChild=None, rightChild=None, SubTreeSize=0):
		self.value = value # Node value (data)
		self.color = color # defaults to RED
		self.parent = parent # defaults to None
		self.leftChild = leftChild # defaults to None
		self.rightChild = rightChild # defaults to None
		self.SubTreeSize = SubTreeSize # defaults to one
	def __eq__(self, other):
		if(isinstance(other, self.__class__)):
			return self.__dict__ == other.__dict__
		else:
			return False
	def __ne__(self, other):
		return (not self.__eq__(other))
	# update subtree size
	def updateSubTreeSize(self):
		self.SubTreeSize = 1
		if(self.getLeftChild().getVal() != None):
			self.SubTreeSize += self.getLeftChild().getSubTreeSize()
		if(self.getRightChild().getVal() != None):
			self.SubTreeSize += self.getRightChild().getSubTreeSize()
	# increment subtree size
	def incSubTreeSize(self):
		self.SubTreeSize += 1
	# decrement subtree size
	def decSubTreeSize(self):
		self.SubTreeSize -= 1
	# get subtree size
	def getSubTreeSize(self):
		return self.SubTreeSize
	# get node value
	def getVal(self):
		return self.value
	# get color
	def getColor(self):
		return self.color
	# get parent
	def getParent(self):
		if(self.parent == None):
			parent = rbNode(None, Color.BLACK, 
			parent=None, leftChild=None, rightChild=None)
			return parent
		return self.parent
	# get left child
	def getLeftChild(self):
		if(self.leftChild == None):
			leftChild = rbNode(None, Color.BLACK, 
			parent=None, leftChild=None, rightChild=None)
			return leftChild
		return self.leftChild
	# get right child
	def getRightChild(self):
		if(self.rightChild == None):
			rightChild = rbNode(None, Color.BLACK, 
			parent=None, leftChild=None, rightChild=None)
			return rightChild
		return self.rightChild
	# set node value
	def setVal(self, value):
		self.value = value
	# set node color
	def setColor(self, color):
		if(color == Color.RED or color == Color.BLACK):
			self.color = color
		else:
			print "setColor() type error!"
	# set parent
	def setParent(self, p):
		self.parent = p
	# set left child
	def setLeftChild(self, leftChild):
		self.leftChild = leftChild
	# set right child
	def setRightChild(self, rightChild):
		self.rightChild = rightChild
	# set SubTreeSize
	def setSubTreeSize(self, size):
		self.SubTreeSize = size

# Red Black Tree Class
class rbTree(object):
	# constructor
	def __init__(self):
		# self.nil acts as the sentinel
		self.nil = rbNode(None, Color.BLACK, 
			parent=None, leftChild=None, rightChild=None)
		# empty tree is just the self.nil node
		self.root = self.nil
		self.treeSize = 0
	
	# returns root node
	def getRoot(self):
		return self.root
		
	# GET SIZE
	def getSize(self):
		return self.treeSize
	
	# SELECT [Runs in O(log n) time because it recurses through height of the tree]
	def select(self, i, start = None):		
		x = self.root
		if (start != None):
			x = start
		r = 1
		if(x.getLeftChild() != None):
			r += x.getLeftChild().getSubTreeSize()
		if (i == r):
			return x
		elif (i < r):
			if(x.getLeftChild().getVal() == None):
				print "SelectError"
				return self.nil
			return self.select(i, x.getLeftChild())
		else:
			if(x.getRightChild().getVal() == None):
				print "SelectError2"
				return self.nil
			return self.select((i-r), x.getRightChild())
	
	# MEDIAN
	def median(self):
		size = self.getSize()
		if(size <= 0):
			return None
		m = 0
		if(size % 2):
			x = size/2
			x += 1
			m += self.select(x).getVal()
			return float(m)
		else:
			x = size/2
			y = x + 1
			m += self.select(x).getVal()
			m += self.select(y).getVal()
			m = float(m)
			m /= float(2)
			return m

	# MINIMUM
	def minimum(self,x = None):
		if(x == None):
			x = self.root
		if x.getVal() == None:
			return self.nil
		while x.getLeftChild() != self.nil:
			x = x.getLeftChild()
		return x
	# END MINIMUM
	
	# MAXIMUM
	def maximum(self, x = None):
		if(x == None):
			x = self.root
		if x.getVal() == None:
			return self.nil
		while x.getRightChild() != self.nil:
			x = x.getRightChild()
		return x
	# END MAXIMUM
	
	# RB TREE SEARCH
	def search(self, k, start = None):
		k = int(k)
		x = self.root
		if (start != None):
			x = start
		if (x.getVal() == None):
			return self.nil
		if (k == x.getVal()):
			return x
		if k < x.getVal():
			return self.search(k, x.getLeftChild())
		else:
			return self.search(k, x.getRightChild())
	# END SEARCH
		
	# LEFT ROTATE
	def left_rotate(self, x):
		y = x.getRightChild()
		x.setRightChild(y.getLeftChild())
		if y.getLeftChild() != self.nil:
			y.getLeftChild().setParent(x)
		y.setParent(x.getParent())
		if x.getParent() == self.nil:
			self.root = y
		elif x == x.getParent().getLeftChild():
			x.getParent().setLeftChild(y)
		else:
			x.getParent().setRightChild(y)
		y.setLeftChild(x)
		x.setParent(y)
		# update invalidated subtree sizes
		y.setSubTreeSize(x.getSubTreeSize())
		x.setSubTreeSize(x.getLeftChild().getSubTreeSize() + \
			x.getRightChild().getSubTreeSize() + 1)
	# END LEFT ROTATE
	
	# RIGHT ROTATE
	def right_rotate(self,y):
		x = y.getLeftChild()
		y.setLeftChild(x.getRightChild())
		if x.getRightChild() != self.nil:
			x.getRightChild().setParent(y)
		x.setParent(y.getParent())
		if y.getParent() == self.nil:
			self.root = x
		elif y == y.getParent().getRightChild():
			y.getParent().setRightChild(x)
		else:
			y.getParent().setLeftChild(x)
		x.setRightChild(y)
		y.setParent(x)
		# update invalidated subtree sizes
		x.setSubTreeSize(y.getSubTreeSize())
		y.setSubTreeSize(y.getLeftChild().getSubTreeSize() + \
			y.getRightChild().getSubTreeSize() + 1)
	# END RIGHT ROTATE
	
	# RB TREE INSERT
	def insert(self, value):
		self.treeSize += 1
		z = rbNode(value)
		z.setSubTreeSize(1)
		y = self.nil
		x = self.root
		while(x != self.nil):
			y = x
			y.incSubTreeSize() # increment subtree size as we descend the tree for insert
			if z.getVal() < x.getVal():
				x = x.getLeftChild()
			else:
				x = x.getRightChild()
		z.setParent(y)
		if y == self.nil:
			self.root = z
		elif z.getVal() < y.getVal():
			y.setLeftChild(z)
		else:
			y.setRightChild(z)
		z.setLeftChild(self.nil)
		z.setRightChild(self.nil)
		z.setColor(Color.RED)
		self.insertFixup(z)
	# END TREE INSERT
	
	# RB INSERT FIXUP
	def insertFixup(self,z):
		while z.getParent().getColor() == Color.RED:
			if z.getParent().getVal() == z.getParent().getParent().getLeftChild().getVal():
				y = z.getParent().getParent().getRightChild()
				if y.getColor() == Color.RED:
					z.setColor(Color.BLACK)
					y.setColor(Color.BLACK)
					z.getParent().getParent().setColor(Color.RED)
					z = z.getParent().getParent()
				else: 
					if z == z.getParent().getRightChild():
						z = z.getParent()
						self.left_rotate(z)
					z.getParent().setColor(Color.BLACK)
					z.getParent().getParent().setColor(Color.RED)
					self.right_rotate(z.getParent().getParent())
			else:
				y = z.getParent().getParent().getLeftChild()
				if y.getColor() == Color.RED:
					z.setColor(Color.BLACK)
					y.setColor(Color.BLACK)
					z.getParent().getParent().setColor(Color.RED)
					z = z.getParent().getParent()
				else:
					if z == z.getParent().getLeftChild():
						z = z.getParent()
						self.right_rotate(z)
					z.getParent().setColor(Color.BLACK)
					z.getParent().getParent().setColor(Color.RED)
					self.left_rotate(z.getParent().getParent())
		self.root.setColor(Color.BLACK)
	# END RB INSERT FIXUP
	
	# RB Tree Transplant
	# Replaces subtree at u with subtree at v
	def transplant(self,u,v):
		if u.getParent().getVal() == None:
			self.root = v
		elif u.getVal() == u.getParent().getLeftChild().getVal():
			u.getParent().setLeftChild(v)
		else: 
			u.getParent().setRightChild(v)
		v.setParent(u.getParent())
	# END RB Tree Transplant
	
	# RB Tree remove
	def remove(self,z):
		self.treeSize -= 1
		y = z
		# decrement subtree sizes for precursor nodes of z
		p = z.getParent()
		while(p.getVal() != None):
			p.decSubTreeSize()
			p = p.getParent()
		
		yOriginalColor = y.getColor()
		# there is no left subtree (z is smallest value)
		# replace z with right subtree
		if z.getLeftChild().getVal() == None:
			x = z.getRightChild()
			self.transplant(z,x)
		# there is no right subtree but there is a left subtree
		# replace z with left subtree
		elif z.getRightChild().getVal() == None:
			x = z.getLeftChild()
			self.transplant(z,z.getLeftChild())
		# both subtrees exist
		else:
			y = self.minimum(z.getRightChild())
			yOriginalColor = y.getColor()
			x = y.getRightChild()
			if y.getParent() == z:
				x.setParent(y)
			else:
				self.transplant(y,y.getRightChild())
				y.setRightChild(z.getRightChild())
				temp = y.getRightChild()
				temp.setParent(y)
			self.transplant(z,y)
			y.setLeftChild(z.getLeftChild())
			temp = y.getLeftChild()
			temp.setParent(y)
			y.setColor(z.getColor())
		if yOriginalColor == Color.BLACK:
			self.removeFixup(x)
	# END RB Tree remove
	
	# RB Tree remove Fixup
	def removeFixup(self, x):
		if(x.getVal() == None):
			return
		while (x != self.root) and (x.getColor() == Color.BLACK):
			if x == x.getParent().getLeftChild():
				w = x.getParent().getRightChild()
				if w.getColor() == Color.RED:
					w.setColor(Color.BLACK)
					x.getParent().setColor(Color.RED)
					self.left_rotate(x.getParent())
					w = x.getParent().getRightChild()
				if (w.getLeftChild().getColor() == Color.BLACK and
					 w.getRightChild().getColor() == Color.BLACK):
					w.setColor(Color.RED)
					x = x.getParent()
				else:
					if w.getRightChild().getColor() == Color.BLACK:
						w.getLeftChild().setColor(Color.BLACK)
						w.setColor(Color.RED)
						self.right_rotate(w)
						w = x.getParent().getRightChild()
					w.setColor(x.getParent().getColor())
					x.getParent().setColor(Color.BLACK)
					w.getRightChild().setColor(Color.BLACK)
					self.left_rotate(x.getParent())
					x = self.root
			else:
				# Same as then clause with right/left exchanged
				w = x.getParent().getLeftChild()
				if w.getColor() == Color.RED:
					w.setColor(Color.BLACK)
					x.getParent().setColor(Color.RED)
					self.right_rotate(x.getParent())
					w = x.getParent().getLeftChild()
				if (w.getRightChild().getColor() == Color.BLACK and
					 w.getLeftChild().getColor() == Color.RED):
					w.setColor(Color.RED)
					x = x.getParent()
				else:
					if w.getLeftChild().getColor() == Color.BLACK:
						w.getRightChild().setColor(Color.BLACK)
						w.setColor(Color.RED)
						self.left_rotate(w)
						w = x.getParent().getLeftChild()
					w.setColor(x.getParent().getColor())
					x.getParent().setColor(Color.BLACK)
					x.getLeftChild().setColor(Color.BLACK)
					self.right_rotate(x.getParent())
					x = self.root
		x.setColor(Color.BLACK)
	# END RB Tree remove Fixup
# END RB Tree Class

# Walk the Tree in order and print values
def inorder_tree_walk(node):
	if(node == None):
		return
	if(node.getVal() != None):
		inorder_tree_walk(node.getLeftChild())
		if(node.getColor() == Color.BLACK):
			col = "BLACK"
		else:
			col = "RED"
		print str(node.getVal()),
		if(False):
			print str(node.getVal()), "{", str(node.getSubTreeSize()), \
				",", col, ",", str(node.getParent().getVal()), \
				",", str(node.getLeftChild().getVal()), \
				",", str(node.getRightChild().getVal()), \
				"}",
		inorder_tree_walk(node.getRightChild())

# Wrappers for Tree Methods:
# Print the Tree using inorder_tree_walk()	
def printTree(T):
	if (type(T) is rbTree):
		node = T.getRoot()
		if(node.getVal() == None):
			print "Empty"
			return
		else:
			# Inorder Traversal
			inorder_tree_walk(node)
			print
	else:
		print "Invalid type for printTree!"
		return


# Search the Tree
def searchTree(T, k):
	node = T.search(k)
	if node.getVal() == None:
		print "NotFound"
	else:
		print "Found"

# Remove a node
def removeNode(T, k):
	node = T.search(k)
	if node.getVal() == None:
		print "TreeError"
	else:
		T.remove(node)

# Insert into the Tree
def insertNode(T, k):
	T.insert(int(k))

# Print Max
def printMax(T):
	max = T.maximum()
	if(max.getVal() == None):
		print "Empty"
	else:
		print max.getVal()

# Print Min
def printMin(T):
	min = T.minimum()
	if(min.getVal() == None):
		print "Empty"
	else:
		print min.getVal()

# Print Median
def printMedian(T):
	m = T.median()
	if(m == None):
		print "Empty"
	else:
		print '{0:g}'.format(m)
	
# ADD
def add(T, k):
	insertNode(T, k)
	printMedian(T)

# REMOVE
def remove(T, k):
	removeNode(T, k)
	printMedian(T)

	