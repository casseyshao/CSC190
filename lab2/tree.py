# Lab 2

from queue import *
from binary_tree import *

class tree:

   def __init__(self,x):
      self.store = [x,[]]

   def AddSuccessor(self,x):
      self.store[1] = self.store[1] + [x]
      return True

   def getTree(self):
      return self.store

   # print using indentation
   def Print_DepthFirst(self):
      # use helper so you can pass in more arguments
      return self.Print_DepthFirst_Help(0)

   def Print_DepthFirst_Help(self,x): # x is the level index
      indent = "   " * x
      print(indent+str(self.store[0]))
      for i in self.store[1]:
         i.Print_DepthFirst_Help(x+1)
      return True

   # does a level order traversal
   # return a flat linear list of the level order traversal values
   def Get_LevelOrder(self):
      listA = []
      x = queue()
      x.enqueue(self) # self is the tree
      
      while x.isEmpty() == False:
         r = x.dequeue()
         listA = listA + [r.store[0]]
         for subtree in r.store[1]:
             x.enqueue(subtree)

      return listA

   # generate equivalent binary tree representation of tree and return that binary tree
   # algo idea: add first successor as left child, add next successor as right child of first successor
   def ConvertToBinaryTree(self):
      root = self.store[0]
      children = self.store[1]
      BTree = binary_tree(root)

      # from instructions:
      # right subtree of the root node of a binary tree (that was converted from a general tree) will not be present
      if (children!=[]):
         first_child = children[0]
         other_children = children[1:len(children)] # other children are first_child siblings
         left_BTree = first_child.ConvertToBinaryTree_Helper(other_children)
         BTree.AddLeft(left_BTree)
      
      return BTree

   def ConvertToBinaryTree_Helper(self,sibling):
      root = self.store[0]
      children = self.store[1]
      BTree = binary_tree(root)

      # add children left
      if (children!=[]):
         first_child = children[0]
         other_children = children[1:len(children)]
         left_BTree = first_child.ConvertToBinaryTree_Helper(other_children)
         BTree.AddLeft(left_BTree)

      # add siblings right
      if (sibling!=[]):
         first_sibling = sibling[0]
         other_siblings = sibling[1:len(sibling)]
         right_BTree = first_sibling.ConvertToBinaryTree_Helper(other_siblings)
         BTree.AddRight(right_BTree)

      return BTree
