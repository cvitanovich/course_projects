import random
import sys
n = sys.argv[1]
text_file = open("Output.txt", "w")
text_file.write(str(n) + '\n')
for i in range(0,int(n)):
	v = []
	v.append(random.randint(1,101))
	v.append(random.randint(1,101))
	text_file.write(str(v[0]) + ' ' + str(v[1]) + '\n')
text_file.close()