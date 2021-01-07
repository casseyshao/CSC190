// Lab 3

#include <stdlib.h>
#include <stdio.h>

/* AVL tree is a binary tree with an additional element in the struct called balance factor 
 * balance factor indicates whether the node is heavy in the left or right directions, or balanced 
 * with AVL trees, we can tolerate an imbalance of at most 1 in any direction */
struct avlNode {
   int balance; /* -1 Left, 0 balanced, +1 Right */
   int val;
   struct avlNode *l;
   struct avlNode *r;
};
typedef struct avlNode avlNode;

/* function prototypes */
int isAVL(avlNode **root);
int height(avlNode *root);
int left_height_helper(avlNode *root);
int right_height_helper(avlNode *root);
int height_helper(avlNode *cNode);
int abs_diff(int a,int b);
int rotate(avlNode **root,unsigned int Left0_Right1);
int dblrotate(avlNode **root,unsigned int MajLMinR0_MajRMinL1);
int add_avl(avlNode **root,int val);

/* return 0 if tree pointed to by root is an avl tree or -1 if not */
/* determine if tree is AVL by calculating left and right subtree depths for all nodes
 * (i.e., do not assume that imbalance measure stored in each node is valid) */
int isAVL(avlNode **root) {
   if ((root == NULL) || ((*root) == NULL)) {
      return -1;
   }

   int left_height = height((*root)->l);
   int right_height = height((*root)->r);

   if ((abs_diff(right_height,left_height) <= 1) && isAVL(&((*root)->l)) && isAVL(&((*root)->r))) {
      return 0;
   } else {
      return -1;
   }
}

int height(avlNode *root) {
   if (root == NULL) {
      return 0;
   }

   int leftHeight = left_height_helper(root->l);
   int rightHeight = right_height_helper(root->r);

   if (leftHeight == 0 && rightHeight == 0) {
      return 0;
   } else if (leftHeight >= rightHeight) {
      return (1+height(root->l));
   } else {
      return (1+height(root->r));
   }

}

int left_height_helper(avlNode *root) {
   if (root == NULL) {
      return 0;
   }

   int leftHeight = 0;
   avlNode *curr = root;
   while (curr != NULL) {
      leftHeight++;
      curr = curr->l;
   }
   
   return leftHeight;
}

int right_height_helper(avlNode *root) {
   if (root == NULL) {
      return 0;
   }
   
   int rightHeight = 0;
   avlNode *curr = root;
   while (curr != NULL) {
      rightHeight++;
      curr = curr->r;
   }
   
   return rightHeight;
}

int abs_diff(int a,int b) {
   if (a == b) {
      return 0;
   } else if (a > b) {
      return (a-b);
   } else {
      return (b-a);
   }
}

int add_avl(avlNode **root,int val) {
   if (root == NULL) {
      return -1;
   }

   if (*root == NULL) {
      (*root) = (avlNode*)malloc(sizeof(avlNode));
      (*root)->val = val;
      (*root)->l = NULL;
      (*root)->r = NULL;
      (*root)->balance = 0;
   } else {
      if (val == (*root)->val) {
         return -1;
      } else if (val < (*root)->val) {
         return (add_avl(&((*root)->l),val));
      } else if (val > (*root)->val) {
         return (add_avl(&((*root)->r),val));
      }
   }

   return 0;
}

/* rotate the tree defined by root+pivot in the direction defined by Left0Right1
 * (if 0, go left; if 1 go right) */
int rotate(avlNode **root,unsigned int Left0_Right1) {
   if ((root == NULL) || ((*root) == NULL)) {
      return -1;
   }

   if ((Left0_Right1 != 0) && (Left0_Right1 != 1)) {
      return -1;
   }

   avlNode *newRoot = NULL;
   //successor is left successor of new root in left rotation (becomes right successor of old root)
   //successor is right successor of new root in right rotation (becomes left successor of old root)
   avlNode *successor = NULL;

   if (Left0_Right1 == 0) { //rotate left
      newRoot = (*root)->r;
      successor = newRoot->l;
      newRoot->l = (*root);
      (*root)->r = successor;
      (*root) = newRoot;
   } else { //rotate right
      newRoot = (*root)->l;
      successor = newRoot->r;
      newRoot->r = (*root);
      (*root)->l = successor;
      (*root) = newRoot;
   }

   return 0;
}

int dblrotate(avlNode **root,unsigned int MajLMinR0_MajRMinL1) {
   if ((root == NULL) || ((*root) == NULL)) {
      return -1;
   }

   if (MajLMinR0_MajRMinL1 != 0 && MajLMinR0_MajRMinL1 != 1) {
      return -1;
   }
   
   if (MajLMinR0_MajRMinL1 == 0) {
      rotate(&(*root)->r,1);
      rotate(root,0);
      return 0;
   } else {
      rotate(&(*root)->l,0);
      rotate(root,1);
      return 0;
   }
}

int printTreeInOrder(avlNode *root) {
   if (root == NULL) {
      return -1;
   } else {
      printTreeInOrder(root->l);
      printf("%d\n",root->val);
      printTreeInOrder(root->r);
      return 0;
   }
}
