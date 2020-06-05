import sys

class Node:
	def __init__(self, data):
		self.data = data
		self.left = None
		self.right = None

class BST:
	def __init__(self):
		self.root = None

	def insert(self, root, data):
		if(root is None):
			return Node(data)
		if(data < root.data):
			root.left = self.insert(root.left, data)
		elif(data > root.data):
			root.right = self.insert(root.right, data)
		return root

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

		return root


if __name__ == "__main__":

	sys.stdin = open('../input.txt', 'r')
	sys.stdout = open('../output.txt', 'w')

	n = sys.stdin.readline()
	a = sys.stdin.readline().split(" ") # [:-1] to eliminate reading of newline
	a = [int(i) for i in a]

	bst = BST();

	for i in a:
		bst.root = bst.insert(bst.root, i)

	for line in sys.stdin:

		if line[-1] == '\n':
			opt = line[:-1].split(" ")
		else:
			opt = line.split(" ")
		
		if opt[0] == "search":
			key = opt[1]
			isFound = bst.search(bst.root,int(key))
			if(isFound is True):
				print(key," is found.", end = "\n");
			else:
				print(key," is not found.", end = "\n");
		elif opt[0] == "delete":
			key = opt[1]
			bst.delete(bst.root, int(key))
		elif opt[0] == "inorder":
			print("Inorder traversal: ")
			bst.inorder(bst.root)
			print(end = "\n")
		elif opt[0] == "preorder":
			print("Preorder traversal: ")
			bst.preorder(bst.root)
			print(end = "\n")
		elif opt[0] == "postorder":
			print("Postorder traversal: ")
			bst.postorder(bst.root)
			print(end = "\n")