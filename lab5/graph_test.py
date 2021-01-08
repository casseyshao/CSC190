# Lab 5

from graph import *

# testing
g = graph()

# test adding vertices
rVal = g.addVertex(5)
print("Number of vertices in graph:",rVal)
print("Initial graph:",g.store)

# test adding edges
g.addEdge(4,0,True,1)
g.addEdge(1,4,False,1)
g.addEdge(1,3,False,1)
g.addEdge(1,2,True,1)
g.addEdge(2,3,True,1)
g.addEdge(3,4,True,1)
print("Graph after adding edges:",g.store)

# test adding more vertices
rVal = g.addVertex(2)
print("Total number of vertices in graph:",rVal)
print("Graph after adding 2 more vertices",g.store)

# test breadth traverse with no start index
print("Breadth traversal with no start index:",g.traverse(None,True))
# test breadth traverse with start index
print("Breadth traversal start from index 4:",g.traverse(4,True))
# test depth traverse with no start index
print("Depth traversal with no start index:",g.traverse(None,False))
# test depth traverse with start index
print("Depth traversal start from index 4:",g.traverse(4,False))

# test connectivity for directed edge
print(g.connectivity(3,4))
# test connectivity for undirected edge
print(g.connectivity(0,4))
# test connectivity where no path exists between two vertices
print(g.connectivity(0,5))

# testing path
g.addEdge(3,5,True,1)
print("Depth traversal start from index 3:",g.traverse(3,False))
print("[[path from 3 to 5],[path from 5 to 3]]:",g.path(3,5))
print("Depth traversal start from index 2:",g.traverse(2,False))
print("[[path from 4 to 2],[path from 2 to 4]]:",g.path(4,2))
print("[[path from 1 to 3],[path from 3 to 1]]:",g.path(1,3))