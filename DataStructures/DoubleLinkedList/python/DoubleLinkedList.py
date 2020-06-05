import sys

class Node:
	def __init__(self, data, prev = None, nexxt = None):
		self.data = data
		self.prev = prev
		self.next = nexxt

class DLList:
	def __init__(self):
		self.head = None
		self.tail = None

	def insert(self, data):
		newnode = Node(data)
		self.tail = newnode
		if self.head is None:
			self.head = newnode
		else:
			temp = self.head
			while temp.next is not None:
				temp = temp.next
			temp.next = newnode 
			newnode.prev = temp
		return

	def insert_at_head(self, data):
		newnode = Node(data)
		newnode.next = self.head 
		if self.head is not None:
			self.head.prev = newnode
		else:
			self.tail = newnode
		self.head = newnode
		return 

	def search(self, val):
		temp = self.head
		while(temp):
			if(temp.data == val):
				return True
			temp = temp.next
		return False

	def remove(self, val):
		temp = self.head
		while(temp):
			if(temp.data == val):
				break
			temp = temp.next
		if(temp):
			if(temp.prev is None):
				self.head = temp.next
				if self.head is not None:
					self.head.prev = None
				else:
					self.tail = None
			else:
				temp.prev.next = temp.next;
				if temp.next is not None:
					temp.next.prev = temp.prev;
				else:
					self.tail = temp.prev;
			temp = None
		self.display()

	def reverse(self, head):
		if head.next is None:
			self.head = head
			return
		self.reverse(head.next)
		head.next.next = head
		head.next = None

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
		slowptr.next.prev = None
		slowptr.next = None
		return fHalf, sHalf

	def __merge(self, a, b):
		temp = None
		while(a != None and b != None):
			if(a.data <= b.data):
				if(temp == None):
					temp = a;
				t = a.next
				a.next = b
				if(b.prev != None):
					b.prev.next = a
				
				b.prev = a
				a = t
			else:
				if(temp == None):
					temp = b
				t = b.next
				b.next = a
				if(a.prev != None):
					a.prev.next = b
				a.prev = b
				b = t
		if(a != None):
			while(a.next != None):
				a = a.next;
			self.tail = a;
		elif(b != None):
			while(b.next != None):
				b = b.next;
			self.tail = b;
		
		return temp;	

	def mergeSort(self, head):
		if head is None or head.next is None:
			return head
		fHalf, sHalf = self.__split(head)
		fHalf = self.mergeSort(fHalf)
		sHalf = self.mergeSort(sHalf)
		return self.__merge(fHalf, sHalf)

	def display(self):
		temp = self.head
		print("null",end = "")
		while(temp):
			print(" <-- ",temp.data,end = " --> ")
			temp = temp.next
		print("null")

	def displayReverse(self):
		temp = self.tail
		print("null",end = "")
		while(temp):
			print(" <-- ",temp.data,end = " --> ")
			temp = temp.prev
		print("null")

if __name__ == '__main__':

	sys.stdin = open('../input.txt', 'r')
	sys.stdout = open('../output.txt', 'w')

	n = sys.stdin.readline();
	a = sys.stdin.readline().split(" ")[:-1] # [:-1] to eliminate reading of newline
	a = [int(i) for i in a]

	dlist = DLList()

	#Insertion
	print("Insertion at tail",end = "\n")
	for i in a:
		dlist.insert(i)
	dlist.display()
	dlist.displayReverse()

	dlist2 = DLList()
	print("Insertion at head",end = "\n")
	for i in a:
		dlist2.insert_at_head(i)
	dlist2.display()
	dlist2.displayReverse()

	#search
	sval = int(sys.stdin.readline())
	isAvailable = dlist.search(sval)
	if(isAvailable):
		print(sval," is found.")
	else:
		print(sval," is not found.")

	#delete
	dval = int(sys.stdin.readline())
	print("After deletion of node ", dval,end = "\n")
	dlist.remove(dval)

	# merge sort
	print("Sorted List", end = "\n")
	dlist.head = dlist.mergeSort(dlist.head)
	dlist.display()
	print("Traversing Sorted List in descending order", end = "\n")
	dlist.displayReverse()