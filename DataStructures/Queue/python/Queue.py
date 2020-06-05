import sys

class Queue:
	def __init__(self):
		self.arr = []

	def __isEmpty(self):
		return len(self.arr)

	def enqueue(self, val):
		(self.arr).append(val)

	def dequeue(self):
		if self.__isEmpty() == 0:
			print("Queue is empty, cant perform pop()")
			return
		(self.arr).pop(0)

	def peek(self):
		if self.__isEmpty() == 0:
			print("Queue is empty, cant retrieve top() : ", end = " ")
			return 403
		return (self.arr)[0]

if __name__ == "__main__":

	sys.stdin = open('../input.txt', 'r')
	sys.stdout = open('../output.txt', 'w')

	q = Queue();

	for line in sys.stdin:
		if line[-1] == '\n':
			opt = line[:-1].split(" ")
		else:
			opt = line.split(" ")
		
		if opt[0] == "enqueue":
			val = opt[1]
			q.enqueue(val)
		elif opt[0] == "dequeue":
			q.dequeue()
		elif opt[0] == "peek":
			print(q.peek())