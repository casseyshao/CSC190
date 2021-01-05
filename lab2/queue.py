# Lab 2

class queue:

   def __init__(self):
      self.fifo = []

   def enqueue(self,ele):
      self.fifo = self.fifo + [ele]
      return True

   def dequeue(self):
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
