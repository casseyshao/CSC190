// Lab 3

#include <stdlib.h>
#include <stdio.h>

struct bstNode {
   int val;
   struct bstNode *l;
   struct bstNode *r;
};
typedef struct bstNode bstNode;

struct avlNode {
   int balance; /* -1 Left, 0 balanced, +1 Right */
   int val;
   struct avlNode *l;
   struct avlNode *r;
};
typedef struct avlNode avlNode;

/* qNode used to implement a linked list of avlNode *
 * needed for print in level order function */
struct qNode {
   avlNode *pval;
   struct qNode *nxt;
};
typedef struct qNode qNode;

/* function prototypes */
int add_bst(bstNode **root,int val);
int printTreeInOrder(bstNode *root);
int printLevelOrder(bstNode *root);
int printLevelOrder_Helper(bstNode *BSTNode);

/* In this function, you are adding values to the Binary Search Tree */
int add_bst(bstNode **root,int val) {
   if (root == NULL) {
      return -1;
   }

   if (*root == NULL) {
      (*root) = (bstNode*)malloc(sizeof(bstNode));
      (*root)->val = val;
      (*root)->l = NULL;
      (*root)->r = NULL;
   } else {
      if (val == (*root)->val) {
         return -1;
      } else if (val < (*root)->val) {
         return (add_bst(&((*root)->l),val));
      } else if (val > (*root)->val) {
         return (add_bst(&((*root)->r),val));
      }
   }
   
   return 0;
}

/* Use *root not **root because not changing it */
/* Order: left->root->right */
int printTreeInOrder(bstNode *root) {
   if (root == NULL) {
      return -1;
   } else {
      printTreeInOrder(root->l);
      printf("%d\n",root->val);
      printTreeInOrder(root->r);
      return 0;
   }
}

int printLevelOrder(bstNode *root) {
   if (root == NULL) {
      return -1;
   }

   printf("%d ",root->val);
   printLevelOrder_Helper(root);
   printf("\n");

   return 0;
}

int printLevelOrder_Helper(bstNode *BSTNode) {
   if (BSTNode == NULL) {
      return -1;
   }

   if (BSTNode->l != NULL) {
      printf("%d ", (BSTNode->l)->val);
   }

   if (BSTNode->r != NULL) {
      printf("%d ", (BSTNode->r)->val);
   }

   printLevelOrder_Helper(BSTNode->l);
   printLevelOrder_Helper(BSTNode->r);

   return 0;
}

/* the following should output:
 * 1
 * 3
 * 4 
 * 5
 * 6
 * 7
 * 8
 * 5 3 7 1 4 6 8 */
int main(void) {
   bstNode *root=NULL;
   add_bst(&root,5);
   add_bst(&root,3);
   add_bst(&root,1);
   add_bst(&root,4);
   add_bst(&root,7);
   add_bst(&root,6);
   add_bst(&root,8);
   printTreeInOrder(root);
   printLevelOrder(root);
   return 0;
}
