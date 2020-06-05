import sys

class Stack:
	def __init__(self):
		self.arr = []

	def __isEmpty(self):
		return len(self.arr)

	def push(self, val):
		(self.arr).append(val)

	def pop(self):
		if self.__isEmpty() == 0:
			print("Stack is empty, cant perform pop()")
			return
		(self.arr).pop()

	def top(self):
		if self.__isEmpty() == 0:
			print("Stack is empty, cant retrieve top() : ", end = " ")
			return 403
		return (self.arr)[-1]

if __name__ == "__main__":

	sys.stdin = open('../input.txt', 'r')
	sys.stdout = open('../output.txt', 'w')

	s = Stack();

	for line in sys.stdin:
		if line[-1] == '\n':
			opt = line[:-1].split(" ")
		else:
			opt = line.split(" ")
		
		if opt[0] == "push":
			val = opt[1]
			s.push(val)
		elif opt[0] == "pop":
			s.pop()
		elif opt[0] == "top":
			print(s.top())