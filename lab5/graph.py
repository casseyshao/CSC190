# Lab 5

'''
G=(V,E)
Let V be the set v0,v1,v2,...
(i.e., with ascending non-negative indices)
and E be the set e0,e1,e2,...
(i.e., with ascending non-negative indices)
'''

class stack:

   def __init__(self):
      self.lifo = []

   def push(self,ele):
      self.lifo = self.lifo + [ele]
      return True

   def pop(self):
      if self.lifo == []:
         return False
      else:
         pop_ele = self.lifo[-1]
         self.lifo = self.lifo[0:-1]
         return pop_ele

   def isEmpty(self):
      if self.lifo == []:
         return True
      else:
         return False

class queue:

   def __init__(self):
      self.fifo = []

   def push(self,ele):
      self.fifo = self.fifo + [ele]
      return True

   def pop(self):
      if self.fifo == []:
         return False
      else:
         pop_ele = self.fifo[0]
         self.fifo = self.fifo[1:len(self.fifo)]
         return pop_ele

   def isEmpty(self):
      if self.fifo == []:
         return True
      else:
         return False

class graph:

   # create an empty store for the graph, which will be an adjacency list
   def __init__(self):
      self.store = []

   # add "n" vertices to the graph
   # return the value of the final number of vertices in the graph
   # if there is an error return -1
   def addVertex(self,n):
      if (n <= 0):
         return -1
      for i in range (0,n):
         self.store = self.store + [[]]
      return len(self.store)

   # from_idx and to_idx are nonnegative integers
   # directed is either True or False
   # weight is any integer other than 0
   # this function adds an edge (a directed edge if directed==True, otherwise an undirected edge) from vertex<from_idx> to vertex<to_idx> with "weight"
   # if there is an error return False, else True
   def addEdge(self,from_idx,to_idx,directed,weight):
      if (from_idx not in range (0,len(self.store))) or (to_idx not in range (0,len(self.store))) or type(directed) != bool or weight == 0:
         return False
      self.store[from_idx] = self.store[from_idx] + [[to_idx,weight]]
      if directed == False:
         self.store[to_idx] = self.store[to_idx] + [[from_idx,weight]]
      return True

   # return a list obtained from a breadth (typeBreadth==True) or depth (typeBreadth==False) traversal of the graph
   # breadth traversal uses queue
   # depth traversal uses stack
   # if there is an error, return an empty list
   # return a list consisting of all nodes visited via the traversal
   # if start is set, this will be one list
   # if start is not set, this will be a list of lists
   def traverse(self,start,typeBreadth):
      # initialize C to empty
      if typeBreadth == True: # breadth traversal
         C = queue()
      elif typeBreadth == False: # depth traversal
         C = stack()
      else:
         return []

      while C.isEmpty == False:
         C.pop()

      # initialize Discovered and Processed to have as many slots as there are v in V
      # set all slots of Discovered and Processed to be False
      Discovered = []
      Processed = []
      for i in range (0,len(self.store)):
          Discovered += [False]
          Processed += [False]
      rlist = []

      V = []
      # if start==None->traversal must traverse the entire graph
      if start == None:
         V = list(range(0,len(self.store)))
      # if start is integer in range of graph vertices indices, traversal is only to vertices that are connected to it
      elif type(start) == int:
         if start not in range (0,len(self.store)):
            return []
         V = [start]
      else:
         return []

      for v in V:
         sublist = []
         if Discovered[v] == False:
            C.push(v)
            Discovered[v] = True
            
         w = C.pop()
         while (type(w) == int):
            if (Processed[w] == False):
               sublist = sublist + [w]
               Processed[w] = True
            # for x = all vertices adjacent to w
            for x in self.store[w]:
               if Discovered[x[0]] == False:
                  C.push(x[0])
                  Discovered[x[0]] = True
            w = C.pop()

         if start == None:
            rlist = rlist + [sublist]
         else:
            rlist = rlist + sublist

      return rlist

   # return a 2-list
   # element[0] is True if there is a path from vx to vy, else False
   # element[1] is True if there is a path from vy to vx, else False
   def connectivity(self,vx,vy):
      rlist = [False,False]
      for i in self.traverse(vx,False):
         if (i == vy):
            rlist[0] = True

      for i in self.traverse(vy,False):
         if (i == vx):
            rlist[1] = True

      return rlist

   # return a 2-list
   # element[0] is a list of vertices from vx to vy, if there is a path, otherwise []
   # element[1] is a list of vertices from vy to vx, if there is a path, otherwise []
   # include endpoints
   def path(self,vx,vy):
      rlist = [[],[]]
      
      if (self.connectivity(vx,vy)[0] == True):
         rlist[0] = self.helper_path(vx,vy,[])

      if (self.connectivity(vx,vy)[1] == True):
         rlist[1] = self.helper_path(vy,vx,[])

      return rlist

   def helper_path(self,vx,vy,temp_list):
      found = False

      if (vx == vy):
         temp_list += [vx]
         return temp_list

      vy_idx = -1
      cnt = 0
      for i in self.traverse(vx,False):
         if (i == vy):
            found = True
            vy_idx = cnt
            break
         cnt+=1

      # find the last directly connected vertex to vx on path to vy
      last_idx = -1
      for i in range(0,len(self.traverse(vx,False))):
         for j in range(0,len(self.store[vx])):
            if (self.traverse(vx,False)[i] == self.store[vx][j]) and (i<vy_idx):
               if (i > last_idx):
                  last_idx = i
               else:
                  break

      # add all elements in depth search from last directly connected to vy to vy to path
      for i in range(last_idx+1,vy_idx):
         if (self.connectivity(self.traverse(vx,False)[i],vy)[0] == True):
            temp_list += [self.traverse(vx,False)[i]]

      temp_list += [self.traverse(vx,False)[vy_idx]]
         
      return temp_list
