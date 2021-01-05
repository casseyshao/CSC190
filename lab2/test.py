# Lab 2

import tree
import binary_tree

# testing convert to binary tree from general tree
x=tree.tree(1)
y=tree.tree(2)
y.AddSuccessor(tree.tree(6))
x.AddSuccessor(y)
z=tree.tree(3)
z.AddSuccessor(tree.tree(7))
z.AddSuccessor(tree.tree(8))
z.AddSuccessor(tree.tree(9))
x.AddSuccessor(z)
x.AddSuccessor(tree.tree(4))
x.AddSuccessor(tree.tree(5))
x.Print_DepthFirst()
print(x.Get_LevelOrder()) # should print [1,2,3,4,5,6,7,8,9]
x_bt=x.ConvertToBinaryTree()
print(x_bt.Get_LevelOrder()) # should print [1,2,6,3,7,4,8,5,9]

# testing convert to general tree from binary tree
x_gt=x_bt.ConvertToTree() # returns length-2 list
print(x_gt[1].Get_LevelOrder()) # should print [1,2,3,4,5,6,7,8,9]

