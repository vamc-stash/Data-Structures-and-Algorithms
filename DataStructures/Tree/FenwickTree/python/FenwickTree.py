# Sum of given range implementation

import sys
import math

def getSum(f, index):

	prefixSum = 0
	while(index > 0):
		prefixSum += f[index]
		index -= (index & (-index))
	return prefixSum

def update(f, n, index, val):
	while(index <= n):
		f[index] += val
		index += (index & (-index))

def build(a, n):

	fenwick = [0] * (n+1)
	for i in range(0, n):
		update(fenwick,n,i+1,a[i]);
	return fenwick

if __name__ == "__main__":

	sys.stdin = open('../input.txt', 'r')
	sys.stdout = open('../output.txt', 'w')

	n = int(sys.stdin.readline())
	a = sys.stdin.readline().split(" ") # [:-1] to eliminate reading of newline
	a = [int(i) for i in a]

	f = build(a, n)

	for line in sys.stdin:

		if line[-1] == '\n':
			opt = line[:-1].split(" ")
		else:
			opt = line.split(" ")
		
		if opt[0] == "sum":
			l, r = int(opt[1]), int(opt[2])
			if(l < 0  or r > n-1 or l > r):
				print("Invalid input ", end = "\n")
			else:
				sum_ = getSum(f, r+1) - getSum(f, l)
				print("sum in the range (",l,", ",r,") is ", sum_, end = "\n")
		elif opt[0] == "update":
			index, newval = int(opt[1]), int(opt[2])
			diff = newval-a[index];
			a[index] = newval;
			update(f, n, index+1, diff);