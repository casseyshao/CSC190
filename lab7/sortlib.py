# Lab 7

# for all functions, sort is to produce a list in ascending order
# input: u is a list
# output/return: True or False
# sorted list is returned via the arg list (often beneficial to sort inplace->less space complexity)

def selection_sort(u):
   for i in range(0,len(u),1):
      for j in range (i,len(u)):
         if u[j] < u[i]:
            temp = u[i]
            u[i] = u[j]
            u[j] = temp
   return True

def heapify(u):
   for i in range (0,len(u),1):
      helper_heapify(u,i)
   return True

def reheapify(u,end):
   for i in range (0,end,1):
      helper_heapify(u,i)
   return True

def helper_heapify(u,i):
   if i == 0:
      return True
   elif i%2 == 1:
      parent = int((i-1)/2)
   else:
      parent = int((i-2)/2)
   if u[i] > u[parent]:
      temp = u[parent]
      u[parent] = u[i]
      u[i] = temp
   helper_heapify(u,parent)
   return True 

def heap_sort(u):
   heapify(u)
   for i in range (len(u)-1,0,-1):
      temp_max = u[0]
      u[0] = u[i]
      u[i] = temp_max
      reheapify(u,i)
   return True

def merge_sort(u):
   if len(u) <= 1:
      return u
   else:
      mid = len(u)//2
      l = u[:mid]
      r = u[mid:]
      merge_sort(l)
      merge_sort(r)
      l_index = 0
      r_index = 0
      u_index = 0
      while l_index < len(l) and r_index < len(r):
         if l[l_index] < r[r_index]:
            u[u_index] = l[l_index]
            l_index = l_index+1
         else:
            u[u_index] = r[r_index]
            r_index = r_index+1
         u_index = u_index+1
      while l_index < len(l):
         u[u_index] = l[l_index]
         l_index = l_index+1
         u_index = u_index+1
      while r_index < len(r):
         u[u_index] = r[r_index]
         r_index = r_index+1
         u_index = u_index+1
   return True

# Example test code (provided in lab specifications):
v1=[10,9,8,7,6,5,4,3,2,1,0]
v2=[100,1,1000,9,8,7,2,2000,10]
v3=[100,10,1000,9,8,7,2,6,5,2,3,1]

for i in [ v1,v2,v3 ]:
   x=list(i)
   selection_sort(x)
   print(x)

   x=list(i)
   heap_sort(x)
   print(x)

   x=list(i)
   heap_sort(x)
   print(x)

   x=list(i)
   merge_sort(x)
   print(x)