import os

for i in range(0,250,25):
	os.system("python dummyfile.py " + str(i))
	os.system("python problem2-3.py Output.txt")
	os.remove("Output.txt")
