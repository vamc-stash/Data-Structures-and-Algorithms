import sys

class Graph:
	def __init__(self, v):
		self.v = v
		self.adjList = [None] * self.v
		for i in range(self.v):
			self.adjList[i] = []

	def addEdge(self,u, v):
		self.adjList[u].append(v)
		if(u != v):
			self.adjList[v].append(u)

	def print(self):
		for i in range(0, self.v):
			print(i," : ", end = " ")
			for j in self.adjList[i]:
				print(j," -> ", end = "")
			print("null", end = "\n")

if __name__ == "__main__":

	sys.stdin = open('../input.txt', 'r')
	sys.stdout = open('../output.txt', 'w')

	v = int(sys.stdin.readline())

	g = Graph(v)

	for line in sys.stdin:

		if line[-1] == '\n':
			opt = line[:-1].split(" ")
		else:
			opt = line.split(" ")
		
		if opt[0] == "addEdge":
			u, v = int(opt[1]), int(opt[2])
			g.addEdge(u, v)

	g.print()