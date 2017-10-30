import os
import time
import math

sz = range(2,100000,500)
tm = []

for i in sz:
	callstr = str(i)
	t0 = time.time()
	os.system('python problem2-2.py dummy100000.txt ' + callstr)
	t1 = time.time()
	tm.append(t1-t0)
	print "For nLines = {0} processing time was {1}".format(callstr, t1 - t0)
	
import matplotlib.pyplot as plt
plt.plot(sz,tm)
plt.ylabel('some numbers')
plt.show()