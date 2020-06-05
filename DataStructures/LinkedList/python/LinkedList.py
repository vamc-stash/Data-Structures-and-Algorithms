import sys

class Node:
	def __init__(self, data, nexxt = None):
		self.data = data
		self.next = nexxt

class LList:
	def __init__(self):
		self.head = None

	def insert(self, data):
		newnode = Node(data)
		if self.head is None:
			self.head = newnode
		else:
			temp = self.head
			while temp.next is not None:
				temp = temp.next
			temp.next = newnode 

	def insert_at_head(self, data):
		newnode = Node(data)
		if self.head is None:
			self.head = newnode
		else:
			newnode.next = self.head 
			self.head = newnode

	def search(self, val):
		temp = self.head
		while(temp):
			if(temp.data == val):
				return True
			temp = temp.next
		return False

	def remove(self, val):
		temp = self.head
		prev = None
		while(temp):
			if(temp.data == val):
				break
			prev = temp
			temp = temp.next
		if(temp):
			if(prev is None):
				self.head = temp.next
			else:
				prev.next = temp.next
			temp = None
		self.display()

	def reverse(self, head):
		if head.next is None:
			self.head = head
			return
		self.reverse(head.next)
		head.next.next = head
		head.next = None

	#private method should start with two underscores '__example()'
	def __split(self, head):    
		if head is None or head.next is None:
			return head, None
		slowptr = head
		fastptr = head.next
		while(fastptr):
			fastptr = fastptr.next
			if(fastptr):
				slowptr = slowptr.next
				fastptr = fastptr.next
		fHalf = head
		sHalf = slowptr.next
		slowptr.next = None
		return fHalf, sHalf

	def __merge(self, a, b):
		if a is None:
			return b
		if b is None:
			return a
		temp = None
		if a.data <= b.data:
			temp = a
			temp.next = self.__merge(a.next, b)
		else:
			temp = b
			temp.next = self.__merge(a, b.next)
		return temp		

	def mergeSort(self, head):
		if head is None or head.next is None:
			return head
		fHalf, sHalf = self.__split(head)
		fHalf = self.mergeSort(fHalf)
		sHalf = self.mergeSort(sHalf)
		return self.__merge(fHalf, sHalf)

	def display(self):
		temp = self.head
		while(temp):
			print(temp.data,end = " --> ")
			temp = temp.next
		print("null")

	def displayReverse(self, head):
		if head is None:
			return
		self.displayReverse(head.next)
		print(head.data, end = " ")

if __name__ == '__main__':

	sys.stdin = open('../input.txt', 'r')
	sys.stdout = open('../output.txt', 'w')

	n = sys.stdin.readline();
	a = sys.stdin.readline().split(" ")[:-1] # [:-1] to eliminate reading of newline
	a = [int(i) for i in a]

	slist = LList()

	#Insertion
	print("Insertion at tail",end = "\n")
	for i in a:
		slist.insert(i)
	slist.display()

	slist2 = LList()
	print("Insertion at head",end = "\n")
	for i in a:
		slist2.insert_at_head(i)
	slist2.display()

	#search
	sval = int(sys.stdin.readline())
	isAvailable = slist.search(sval)
	if(isAvailable):
		print(sval," is found.")
	else:
		print(sval," is not found.")

	#delete
	dval = int(sys.stdin.readline())
	print("After deletion of node ", dval,end = "\n")
	slist.remove(dval)

	#reverse
	print("Reversing List", end = "\n")
	slist.reverse(slist.head)
	slist.display()
	
	# traverse reverse
	print("Traversing reverse", end = "\n")
	slist.displayReverse(slist.head)

	# merge sort
	print("Sorted List", end = "\n")
	slist.head = slist.mergeSort(slist.head)
	slist.display()