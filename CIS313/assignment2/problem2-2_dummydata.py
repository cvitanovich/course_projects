# create dummy data for problem 2-2
from random import randint
import os, sys

num = sys.argv[1]
f= open("dummy" + num + ".txt","w+")
f.seek(0)

N = int(num)
#randint(2, 200)

f.write(str(N) + os.linesep)

for i in range(0,N):
	val = randint(0,10**6)
	f.write(str(val) + os.linesep)