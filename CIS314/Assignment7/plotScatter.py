import numpy as np
import matplotlib.pyplot as plt
import csv

# data variables
x = []
y_old = []
y_new = []
speedup = []

# create plot
fig = plt.figure()
ax = fig.add_subplot(1,1,1,axisbg="1.0")

# load data from csv file
with open('data.csv','rb') as csvfile:
	reader = csv.reader(csvfile,delimiter=',',quotechar='|')
	for row in reader:
		x.append(float(row[0]))
		y_old.append(float(row[1]))
		y_new.append(float(row[2]))
		speedup.append(float(row[3]))

#jittered_x = [i*1.05 for i in x]
ax.scatter(x,y_old,alpha=0.8,c='red',edgecolors='red',facecolors='none',s=30,label="inner()")
ax.scatter(x,y_new,alpha=0.8,c='blue',marker='*',edgecolors='none',s=30,label="inner2()")
xlim = max(x) + 1000
ylim = max(max(y_old),max(y_new))
plt.axis([0,xlim,0,ylim])
plt.xlabel('Array Size')
plt.ylabel('Clock Time (s)')
plt.title('Performance of inner() vs inner2()')
plt.legend(loc=2)
plt.show()

print np.mean(speedup)