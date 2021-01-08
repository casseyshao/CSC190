# Lab 8

# Radix Sort
# return sorted L
def sortr(L):

   maxA = L[0]
   for i in range(0,len(L)):
      if L[i] > maxA:
         maxA = L[i]
   digits = int(len(str(maxA)))+1

   for i in range(0,digits):
      arr = [[],[],[],[],[],[],[],[],[],[]] # one for each digit, i.e., 10
      for ele in L:
         arr_idx = (ele//(10**i))%10
         arr[arr_idx] += [ele]
      L[:] = []
      for i in range(0,len(arr)):
         for j in range(0,len(arr[i])):
            L = L + [arr[i][j]]

   return L

# test code:
L = [150,113,146,132,84,14,3,278,75]
print("Initial List:")
print(L)
print("Sorted List:")
print(sortr(L))