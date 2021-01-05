# Lab 2

from queue import *
import tree

# binary trees: trees with only two subtrees
# binary tree is either [], [val], or [val leftBinary rightBinary]
class binary_tree:

   def __init__(self,x):
      self.store = [x,' ',' '] # empty character space is a placeholder

   def AddLeft(self,x):
      self.store[1] = x
      return True

   def AddRight(self,x):
      self.store[2] = x
      return True

   def Get_LevelOrder(self):
      listA = []
      x = queue()
      x.enqueue(self) # self is the tree
      while (x.isEmpty() == False):
         r = x.dequeue()
         listA = listA + [r.store[0]]
         if (r.store[1] != ' '):
            x.enqueue(r.store[1])
         if (r.store[2] != ' '):
            x.enqueue(r.store[2])
      return listA

   # generate general tree representation from binary tree
   # return a length-2 list
   # first element of list is True (if conversion can be performed) or False (otherwise)
   # second element of list is tree that is created (if first element is True) or undefined (if False)
   # recall tree representation: [rootValue, [T1, T2, ...]]
   # algo idea: add left child as first successor, add left child's right child, then next right child... as siblings
   def ConvertToTree(self):
      root = self.store[0]
      successor = self.store[1] # left subtree
      sibling = self.store[2] # right subtree
      GTree = tree.tree(root) # GTree is our accumulator

      # root node should not have a right subtree according to instructions
      if (sibling != ' '):
         return [False,' ']

      if (successor != ' '):
         for node in self.ConvertToTree_Helper(successor):
            GTree.AddSuccessor(node)

      return [True,GTree]

   def ConvertToTree_Helper(self,successor):
      new_node = tree.tree(successor.store[0])
      left = successor.store[1]
      right = successor.store[2]

      if (left != ' '):
         for node in self.ConvertToTree_Helper(left):
            new_node.AddSuccessor(node)

      if (right != ' '):
         return([new_node] + self.ConvertToTree_Helper(right)) # concatenate lists

      return([new_node])
