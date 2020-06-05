# Max Heap Implementation

import sys
import math

class PriorityQueue:
	def __init__(self):
		self.arr = []

	def __heapify_down(self, i):
		largest = i;
		left = 2*i + 1; # left child
		right = 2*i + 2; # right child
		if(left < len(self.arr) and (self.arr)[left] > (self.arr)[largest]):
			largest = left
		if(right < len(self.arr) and (self.arr)[right] > (self.arr)[largest]):
			largest = right
		if(largest != i):
			(self.arr)[i], (self.arr)[largest] = (self.arr)[largest], (self.arr)[i]
			self.__heapify_down(largest)

	def __heapify_up(self, i):
		p = math.floor((i-1)/2) # parent
		if(i != 0 and (self.arr)[p] < (self.arr)[i]):
			(self.arr)[i],(self.arr)[p] = (self.arr)[p], (self.arr)[i]
			self.__heapify_up(p);

	def insert(self, data):
		(self.arr).append(data);
		self.__heapify_up(len(self.arr)-1);

	def dequeue(self):
		if(len(self.arr) == 0):
			print("empty heap: could not remove priority element", end = "\n")
			return
		(self.arr).pop(0)

	def peek(self):
		if(len(self.arr) == 0):
			print("empty heap: could not retreive priority element: ", end = " ")
			return 403;
		return (self.arr)[0]

	def display(self):
		for i in self.arr:
			print(i,end = " ")
		print(end="\n")

if __name__ == "__main__":

	sys.stdin = open('../input.txt', 'r')
	sys.stdout = open('../output.txt', 'w')

	pq = PriorityQueue();

	for line in sys.stdin:
		if line[-1] == '\n':
			opt = line[:-1].split(" ")
		else:
			opt = line.split(" ")
		
		if opt[0] == "insert":
			val = opt[1]
			pq.insert(val)
		elif opt[0] == "dequeue":
			pq.dequeue()  # Remove priority element (max value element in this case)
		elif opt[0] == "peek":
			print(pq.peek()) # priority element of the heap
		elif opt[0] == "display":
			pq.display()  # display heap