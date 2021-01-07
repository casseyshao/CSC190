// Lab 4

#include <stdio.h>
#include <stdlib.h>
#include "heap.c"

/* Recall: pHeap is caller-allocated */
int main(void) {
   HeapType *tree = NULL;
   int *output = NULL;
   int o_size = -1;

   // build heap tree (size 10)
   tree = (HeapType*)malloc(10*sizeof(HeapType));
   initHeap(tree,10);
   addHeap(tree,1);
   addHeap(tree,2);
   addHeap(tree,3);
   addHeap(tree,7);
   addHeap(tree,5);
   addHeap(tree,4);

   printf("Heap tree:\n");
   for (int i=0;i<10;i++) {
      printf("%d ",tree->store[i]);
   }
   printf("\n");

   // test inorder traversal
   int r = inorder(tree,&output,&o_size);
   printf("In-order traversal:\n");
   for (int i=0;i<o_size;i++) {
      printf("%d ",output[i]);
   }
   printf("\n");

   // test preorder traversal
   free(output);
   r = preorder(tree,&output,&o_size);
   printf("Pre-order traversal:\n");
   for (int i=0;i<o_size;i++) {
      printf("%d ",output[i]);
   }
   printf("\n");

   // test postorder traversal
   free(output);
   r = postorder(tree,&output,&o_size);
   printf("Post-order traversal:\n");
   for (int i=0;i<o_size;i++) {
      printf("%d ",output[i]);
   }
   printf("\n");

   // test adding to heap
   addHeap(tree,25);
   printf("New heap tree:\n");
   for (int i=0;i<10;i++) {
      printf("%d ",tree->store[i]);
   }
   printf("\n");

   // test finding elements in heap
   r = findHeap(tree,7);
   printf("Should be 1 (for found): %d\n",r);
   r = findHeap(tree,25);
   printf("Should be 1 (for found): %d\n",r);
   r = findHeap(tree,15);
   printf("Should be 0 (for not found): %d\n",r);

   // test deleting from heap
   //delHeap(HeapType *pHeap, int *key)
   int maxKey = -1;
   r = delHeap(tree,&maxKey);
   printf("Removed max element of value: %d\n",maxKey);
   printf("New heap tree:\n");
   for (int i=0;i<10;i++) {
      printf("%d ",tree->store[i]);
   }
   printf("\n");
   r = delHeap(tree,&maxKey);
   printf("Removed max element of value: %d\n",maxKey);
   printf("New heap tree:\n");
   for (int i=0;i<10;i++) {
      printf("%d ",tree->store[i]);
   }
   printf("\n");
   r = delHeap(tree,&maxKey);
   printf("Removed max element of value: %d\n",maxKey);
   printf("New heap tree:\n");
   for (int i=0;i<10;i++) {
      printf("%d ",tree->store[i]);
   }
   printf("\n");
   
   return 0;   
}
