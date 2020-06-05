import sys

class DisjointSet:
	def __init__(self, n):
		self.n = n
		self.rank = [0] * self.n
		self.parent = [0] *self.n
		for i in range(n):
			self.parent[i] = i

	def find(self, x):
		if(self.parent[x] != x):
			self.parent[x] = self.find(self.parent[x])
		return self.parent[x]
	
	def _union(self, u, v):
		uset = self.find(u)
		vset = self.find(v)

		if(uset == vset):
			return

		if(self.rank[uset] < self.rank[vset]):
			self.parent[uset] = vset
		elif(self.rank[uset] > self.rank[vset]):
			self.parent[vset] = uset;
		else:
			self.parent[vset] = uset;
			self.rank[uset] += 1;

if __name__ == "__main__":

	sys.stdin = open('../input.txt', 'r')
	sys.stdout = open('../output.txt', 'w')

	n = int(sys.stdin.readline())

	ds = DisjointSet(n)

	for line in sys.stdin:

		if line[-1] == '\n':
			opt = line[:-1].split(" ")
		else:
			opt = line.split(" ")
		
		if opt[0] == "union":
			u, v = int(opt[1]), int(opt[2])
			ds._union(u, v)
		elif opt[0] == "find":
			u, v = int(opt[1]), int(opt[2])
			if(ds.find(u) == ds.find(v)):
				print(u,", ",v," belongs to same set.", end = "\n")
			else:
				print(u,", ",v," belongs to different sets.", end = "\n")
