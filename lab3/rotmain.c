// Lab 3

#include <stdlib.h>
#include <stdio.h>
#include "avlrot.c"

int main(void) {
   
   // build a balanced AVL tree
   printf("Tree 1:\n");
   avlNode *root = NULL;
   add_avl(&root,7);
   add_avl(&root,5);
   add_avl(&root,9);
   add_avl(&root,4);
   add_avl(&root,6);
   add_avl(&root,8);
   add_avl(&root,10);
   printf("Should be 0 (is AVL): %d\n",isAVL(&root));
   printf("Height: %d\n",height(root));

   // make the AVL tree unbalanced
   add_avl(&root,2);
   add_avl(&root,1);
   printTreeInOrder(root);
   printf("Should be -1 (is not AVL->need rotation): %d\n",isAVL(&root));
   printf("Height: %d\n",height(root));
   printf("Before rotation: %d\n",(root->l->l->val));

   // fix the unbalance by rotating (requires right rotation)
   int r = rotate(&(root->l->l),1);
   printf("After rotation: %d\n",(root->l->l->val));
   printf("Should be 0 (is AVL): %d\n",isAVL(&root));
   printf("Height: %d\n",height(root));

   // build a new unbalanced AVL tree
   printf("Tree 2:\n");
   avlNode *root2 = NULL;
   add_avl(&root2,13);
   add_avl(&root2,12);
   add_avl(&root2,17);
   add_avl(&root2,18);
   add_avl(&root2,15);
   add_avl(&root2,16);
   add_avl(&root2,14);
   printf("Should be -1 (is not AVL->need rotation): %d\n",isAVL(&root2));
   printf("Height: %d\n",height(root2));
   printf("Before rotation root value (should be 13): %d\n",(root2->val));

   // fix the unbalance by double-rotating (requires major left minor right rotation)
   r = dblrotate(&root2,0);
   printf("After rotation root value (should be 15): %d\n",(root2->val));
   printf("Should be 0 (is AVL): %d\n",isAVL(&root2));
   printf("Height: %d\n",height(root2));

   return 0;
}
