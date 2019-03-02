import sys
import random

maxBurstTime = 10
maxBurstNum = 10
threadNum = 100
arriveTimeRange = 5
priorityRange = 10

# random.seed(9001)

if __name__ == "__main__":

	#check
	if threadNum < 1:
		exit()
	if maxBurstTime<=1:
		exit()

	fo = open("tests/test.txt", "w")
	

	arriveTime = 0
	for i in range(threadNum):

		burstNum = random.randint(1, maxBurstNum)
		priority = random.randint(1, priorityRange)

		fo.write(str(arriveTime))
		fo.write(",")
		fo.write(str(priority))
		for i in range(burstNum):
			burstTime = random.randint(1, maxBurstTime)
			fo.write(",")
			fo.write(str(burstTime))
		fo.write("\n")
		arriveTime += random.randint(1, arriveTimeRange)

	fo.close()