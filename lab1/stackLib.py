# Lab 1

# write a class for a stack which will implement a stack data structure (LIFO)

class stack:
   # internal list variable to handle data that is input to it
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
         self.lifo = self.lifo[0:len(self.lifo)-1]
         return pop_ele

   # for debugging:
   #def getStack(self):
   #   return self.lifo

'''
testing:
stackTest = stack()
stackTest.push(2)
stackTest.push(3)
stackTest.push(4)
stackTest.push(5)
print(stackTest.getStack())
stackTest.pop()
print(stackTest.getStack())
stackTest.pop()
stackTest.pop()
print(stackTest.getStack())
stackTest.pop()
print(stackTest.getStack())
'''