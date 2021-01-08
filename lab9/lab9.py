# Lab 9

# u is the list

def quicksort(u,ini,fin):
   if (ini < fin):
      pIndex = partition(u,ini,fin)
      quicksort(u,ini,pIndex-1)
      quicksort(u,pIndex+1,fin)
   return True

def partition(u,ini,fin):
   pivot = u[fin]
   i = ini
   j = fin-1

   done = False
   while not done:
      while (i <= j) and (u[i] <= pivot):
         i += 1
      while (i <= j) and (u[j] >= pivot):
         j -= 1
      if (i > j):
         done = True
      else:
         u[i],u[j] = u[j],u[i]

   u[fin],u[i] = u[i],u[fin]
   pIndex = i
   return pIndex

'''
where start, tmp, and final will be lists e.g., for n = 3:
start = [1,2,3]
tmp = []
final = []

after running hanoi:
final = [1,2,3]
tmp = []
start = []
'''
def hanoi(n,start,tmp,final):
   if (n > 0):
      hanoi(n - 1,start,final,tmp)
      final.append(start.pop())
      hanoi(n - 1,tmp,start,final)
      print(start,tmp,final)
      return True
   else:
      return True

# test code for quick sort:
x = [10,9,8,7,6,5,4,3,2,1,0]
y = [100,1,1000,9,8,7,2,2000,10]
quicksort(x,0,len(x)-1)
print(x)
quicksort(y,0,len(y)-1)
print(y)

# test code for hanoi:
n = 5
start = [1,2,3,4,5]
tmp = []
final = []
hanoi(n,start,tmp,final)