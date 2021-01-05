// Lab 3

/* tree sort: to sort a set of numbers, read them into a bst
 * and then print out the in order traversal of the bst */

/* compile via "gcc -pedantic treesort.c" 
 * test via "cat numbers.txt | ./a.out > sorted.txt" */

#include <stdlib.h>
#include <stdio.h>

struct bstNode {
   int val;
   struct bstNode *l;
   struct bstNode *r;
};
typedef struct bstNode bstNode;

int add_bst(bstNode **root,int val);
int printTreeInOrder(bstNode *root);

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

/* read integers from user until EOF
 * integers should be added into bst using add_bst()
 * after EOF, program should print out the list in sorted order: one int per line */
int main(void) {
   int value=0;
   int rvalue=0;
   bstNode *input_list=NULL;

   while (scanf("%d",&value) != EOF) {
      add_bst(&input_list,value);
   }

   rvalue = printTreeInOrder(input_list);

   if (rvalue == -1) {
      printf("ERROR: add_bst() returned an error\n");
   }

   return 0;
}
