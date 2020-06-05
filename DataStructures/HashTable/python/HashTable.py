import sys

class HashMap:
	def __init__(self):
		self.hashmap = {}

	def insert(self, key, value):
		self.hashmap[key] = value

	def delete(self, key):
		self.hashmap.pop(key)

	def search(self, key):
		if key in self.hashmap:
			return self.hashmap[key]
		return None

	def display(self):
		print(self.hashmap)

if __name__ == "__main__":

	sys.stdin = open('../input.txt', 'r')
	sys.stdout = open('../output.txt', 'w')

	h = HashMap();

	for line in sys.stdin:
		if line[-1] == '\n':
			opt = line[:-1].split(" ")
		else:
			opt = line.split(" ")
		
		if opt[0] == "insert":
			key = opt[1]
			value = opt[2]
			h.insert(key,value)
		elif opt[0] == "search":
			key = opt[1]
			item = h.search(key)
			if item is not None:
				print("(", key, ", ", item, ") is found.",end = "\n")
			else:
				print(key, "is not found.", end = "\n")
		elif opt[0] == "delete":
			key = opt[1]
			h.delete(key)
		elif opt[0] == "display":
			h.display()