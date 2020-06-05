import sys

class Node:
	def __init__(self, data):
		self.data = data
		self.left = None
		self.right = None
		self.height = 1

class Avl:
	def __init__(self):
		self.root = None

	def __height(self, node):
		if node is None:
			return 0
		return node.height

	def __getBalance(self, node):
		if(node is None):
			return 0
		return self.__height(node.left) - self.__height(node.right);

	def __rightRotate(self, a):
		b = a.left
		t = b.right

		b.right = a
		a.left = t

		a.height = max(self.__height(a.left), self.__height(a.right)) + 1
		b.height = max(self.__height(b.left), self.__height(b.right)) + 1

		return b
	
	def __leftRotate(self, a):
		b = a.right
		t = b.left

		b.left = a
		a.right = t

		a.height = max(self.__height(a.left), self.__height(a.right)) + 1
		b.height = max(self.__height(b.left), self.__height(b.right)) + 1

		return b
	
	def __balancedTree(self, node, data):

		node.height = 1 + max(self.__height(node.left), self.__height(node.right))
		bal = self.__getBalance(node)

		# Right right case
		if(bal> 1 and data < node.left.data):
			return self.__rightRotate(node)

		# Left left case
		if(bal < -1 and data > node.right.data):
			return self.__leftRotate(node)

		# Left Right case
		if(bal > 1 and data > node.left.data):
			node.left =  self.__leftRotate(node.left)
			return self.__rightRotate(node)

		# Right left case
		if(bal < -1 and data < node.right.data):
			node.right = self.__rightRotate(node.right)
			return self.__leftRotate(node)

		return node

	def insert(self, root, data):
		if(root is None):
			return Node(data)
		if(data < root.data):
			root.left = self.insert(root.left, data)
		elif(data > root.data):
			root.right = self.insert(root.right, data)
		return self.__balancedTree(root, data)

	def preorder(self, root):
		if(root):
			print(root.data,end = " ")
			self.preorder(root.left)
			self.preorder(root.right)
		
	def inorder(self, root):
		if(root):
			print(root.data,end = " ")
			self.inorder(root.left)
			self.inorder(root.right)

	def postorder(self, root):
		if(root):
			print(root.data,end = " ")
			self.postorder(root.left)
			self.postorder(root.right)

	def search(self, root, data):
		if(root is None):
			return False
		if(root.data == data):
			return True
		elif(root.data < data):
			return self.search(root.right, data)
		else:
			return self.search(root.left, data)
		return False

	def getInorderSuccessor(self,temp):
		while(temp and temp.left):
			temp = temp.left;
		return temp;
	
	def delete(self, root, data):
		if(root is None):
			return root
		if(data < root.data):
			root.left = self.delete(root.left, data)
		elif(data > root.data):
			root.right = self.delete(root.right, data)
		else:
			#Node with one child or no child 
			if(root.left is None):
				temp = root.right
				root = None
				return temp
			elif(root.right is None):
				temp = root.left
				root = None
				return temp
			#Node with two child
			temp = self.getInorderSuccessor(root.right)
			root.data = temp.data
			root.right = self.delete(root.right, temp.data)

		return self.__balancedTree(root, data)


if __name__ == "__main__":

	sys.stdin = open('../input.txt', 'r')
	sys.stdout = open('../output.txt', 'w')

	n = sys.stdin.readline()
	a = sys.stdin.readline().split(" ") # [:-1] to eliminate reading of newline
	a = [int(i) for i in a]

	avl = Avl();

	for i in a:
		avl.root = avl.insert(avl.root, i)

	for line in sys.stdin:

		if line[-1] == '\n':
			opt = line[:-1].split(" ")
		else:
			opt = line.split(" ")
		
		if opt[0] == "search":
			key = opt[1]
			isFound = avl.search(avl.root,int(key))
			if(isFound is True):
				print(key," is found.", end = "\n");
			else:
				print(key," is not found.", end = "\n");
		elif opt[0] == "delete":
			key = opt[1]
			avl.delete(avl.root, int(key))
		elif opt[0] == "inorder":
			print("Inorder traversal: ")
			avl.inorder(avl.root)
			print(end = "\n")
		elif opt[0] == "preorder":
			print("Preorder traversal: ")
			avl.preorder(avl.root)
			print(end = "\n")
		elif opt[0] == "postorder":
			print("Postorder traversal: ")
			avl.postorder(avl.root)
			print(end = "\n")