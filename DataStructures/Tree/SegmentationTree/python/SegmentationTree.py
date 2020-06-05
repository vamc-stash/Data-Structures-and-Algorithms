# Sum of given range implementation

import sys
import math

def updateUtil(st, s, e, i, diff, si):
	if(i < s or i > e):
		return
	st[si] += diff
	if(s != e):
		mid = s + ((e - s) // 2)
		updateUtil(st, s, mid, i, diff, 2*si + 1)
		updateUtil(st, mid+1, e, i, diff, 2*si + 2)

def update(st,  a,  n, index, newValue):
	if(index < 0 or index > n-1):
		print("Invalid input", end = "\n")
		return

	diff = newValue - a[index]
	a[index] = newValue

	updateUtil(st, 0, n-1, index, diff, 0)

def getSumUtil(st, s, e, l, r, si):
	if(s > e or l > e or r < s):
		return 0
	if(s >= l and e <= r):
		return st[si]
	mid = s + ((e - s) // 2)
	return getSumUtil(st, s, mid, l, r, 2*si + 1) + getSumUtil(st, mid + 1, e, l, r, 2*si + 2)

def getSum(st, n, l, r):
	if(l < 0 or r > n-1 or l > r):
		print("Invalid input: ")
		return -1

	print("sum in the range (",l,", ",r,") is ")
	return getSumUtil(st, 0, n-1, l, r, 0)

def buildSTutil(st, a, s, e, si):
	if(s == e):
		st[si] = a[s]
		return a[s]

	mid = s + ((e - s) // 2)

	st[si] = buildSTutil(st, a, s, mid, 2*si+1) + buildSTutil(st, a, mid+1, e, 2*si+2)
	return st[si]

def buildST(a, n):
	height = (int)(math.ceil(math.log2(n)))
	maxSize = 2*(int)(2**height) - 1

	st = [0] * maxSize
	buildSTutil(st, a, 0, n-1, 0)

	return st

if __name__ == "__main__":

	sys.stdin = open('../input.txt', 'r')
	sys.stdout = open('../output.txt', 'w')

	n = int(sys.stdin.readline())
	a = sys.stdin.readline().split(" ") # [:-1] to eliminate reading of newline
	a = [int(i) for i in a]

	st = buildST(a, n)

	for line in sys.stdin:

		if line[-1] == '\n':
			opt = line[:-1].split(" ")
		else:
			opt = line.split(" ")
		
		if opt[0] == "sum":
			l, r = int(opt[1]), int(opt[2])
			sum_ = getSum(st, n, l, r)
			print(sum_, end = "\n");
		elif opt[0] == "update":
			index, value = int(opt[1]), int(opt[2])
			update(st, a, n, index, value)