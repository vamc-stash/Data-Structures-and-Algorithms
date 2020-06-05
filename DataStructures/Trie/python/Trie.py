import sys

class Trie:
	def __init__(self):
		self.isLeaf = False
		self.map = {}

	def insert(self, word):
		curr = self;
		for i in word:
			if curr.map.get(i) is None:
				curr.map[i] = Trie()

			curr = curr.map[i]
		curr.isLeaf = True;
	
	def search(self, word):
		curr = self
		if curr is None:
			return False
		for i in word:
			curr = curr.map.get(i)
			if curr is None:
				return False
		return curr.isLeaf
	
	def delete(self, curr, word, i):
		if len(word) == i:
			curr.isLeaf = False
			return bool(curr.map)

		char = word[i]
		if char not in curr.map:
			return True

		flag = self.delete(curr.map[char], word, i+1)
		if(flag):
			return True 
		curr.map.pop(char)
		return bool(curr.map) or curr.isLeaf
		

if __name__ == "__main__":

	sys.stdin = open('../input.txt', 'r')
	sys.stdout = open('../output.txt', 'w')

	head = Trie();

	for line in sys.stdin:

		if line[-1] == '\n':
			opt = line[:-1].split(" ")
		else:
			opt = line.split(" ")
		
		if opt[0] == "insert":
			word = opt[1]
			head.insert(word)
		elif opt[0] == "search":
			word = opt[1]
			isFound = head.search(word)
			if(isFound is True):
				print(word," is found.", end = "\n");
			else:
				print(word," is not found.", end = "\n");
		elif opt[0] == "delete":
			word = opt[1]
			head.delete(head, word, 0)