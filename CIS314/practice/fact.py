# Different ways to compute factorial

def factWhile(n):
	result=1;
	while(n>1):
		result*=n;
		n-=1;
	return result;

def factFor(n):
	if(n==0):
		return 1;
	result=1;
	for x in range(n):
		result*=(n-x);
	return result;

def factRecursive(n):
	if(n<=1):
		return 1;
	else:
		return n * factRecursive(n-1);

# Testing each function for n=0,1,...,10

for n in range(10):
	print "factWhile(" + str(n) + ") = " + str(factWhile(n))
	print "factFor(" + str(n) + ") = " + str(factFor(n))
	print "factRecursive(" + str(n) + ") = " + str(factRecursive(n))