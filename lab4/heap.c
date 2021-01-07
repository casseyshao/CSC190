// Lab 4

#include <stdio.h>
#include <stdlib.h>

/* Heaps are specializations of Binary Trees that relax the strict ordering of BSTs:
 * - root node is either less than or greater than its successors
 * - there is no relative ordering between the successor trees
 * a min-heap is one where root node is less than its successors
 * a max-heap is one where root node is greater than its successors
 * 
 * insertion point of a heap is always the last valid element in the heap
 * hence, one does not need to track or demark all leaf nodes, but just one
 * thus, only need to maintain an index that tracks this insertion point */

/* using a max-heap */
typedef struct {
   int *store;
   unsigned int size;
   unsigned int end;
} HeapType;

/* function prototypes */
int initHeap(HeapType *pHeap,int size);
int inorder(HeapType *pHeap, int **output, int *o_size);
int inorder_helper(int *store_heap, int *output, int o_size, int rootIndex, int *i);
int preorder(HeapType *pHeap, int **output, int *o_size);
int preorder_helper(int *store_heap, int *output, int o_size, int rootIndex, int *i);
int postorder(HeapType *pHeap, int **output, int *o_size);
int postorder_helper(int *store_heap, int *output, int o_size, int rootIndex, int *i);
int addHeap(HeapType *pHeap, int key);
int addHeap_helper(int index, int *store_heap);
int findHeap(HeapType *pHeap, int key);
int delHeap(HeapType *pHeap, int *key);
int delHeap_helper(int index, int *store_heap, int root);

/* Recall: Initialize by setting the valid slot of each node to 0 */
/* Arguments: pHeap is caller-allocated and size indicates how large the heap should be
 * Return: 0 for success and -1 otherwise */
int initHeap(HeapType *pHeap,int size) {
   if ((pHeap == NULL) || (size < 1)) {
      return -1;
   } else {
      pHeap->store = (int*)malloc(size*sizeof(int));
      pHeap->size = size;
      /* Initialize end to 0 because you have no valid elements at this point */
      /* end is defined as the index of the first invalid slot in the store */
      pHeap->end = 0;
      return 0;
   }
}

/* Note: for the following three functions, o_size is the return value */
/* Recall: In-Order is Left-Root-Right */
/* int **output is caller-unallocated array that will store the output data */
/* o_size should be the same size of valid slots as that of the input tree */
/* Return: 0 for success and -1 otherwise */
int inorder(HeapType *pHeap, int **output, int *o_size) {
   int i=0;
   if ((pHeap == NULL) || (output == NULL) || (o_size == NULL)) {
      return -1;
   }
   *o_size = pHeap->end;
   *output = (int*)malloc((*o_size)*sizeof(int));
   return inorder_helper(pHeap->store, *output, *o_size, 0, &i);
}

/* Recall: leftChild = 2*rootIndex+1; rightChild = 2*rootIndex+2; */
int inorder_helper(int *store_heap, int *output, int o_size, int rootIndex, int *i) {
   /* Once rootIndex is bigger than o_size, it means you've accumulated all the values */
   if (rootIndex >= o_size) {
      return 0;
   } else if (2*rootIndex+1>=o_size) {
      output[*i] = store_heap[rootIndex];
      (*i)=(*i)+1;
      return 0;
   } else {
      inorder_helper(store_heap, output, o_size, 2*rootIndex+1, i);
      output[*i]=store_heap[rootIndex];
      (*i)=(*i)+1;
      inorder_helper(store_heap, output, o_size, 2*rootIndex+2, i);
      return 0;
   }
}

/* Recall: Pre-Order is Root-Left-Right */
/* Return: 0 for success and -1 otherwise */
int preorder(HeapType *pHeap, int **output, int *o_size) {
   int i=0;
   if ((pHeap == NULL) || (output == NULL) || (o_size == NULL)) {
      return -1;
   }
   *o_size = pHeap->end;
   *output = (int*)malloc((*o_size)*sizeof(int));
   return preorder_helper(pHeap->store, *output, *o_size, 0, &i);
}

int preorder_helper(int *store_heap, int *output, int o_size, int rootIndex, int *i) {
   if (rootIndex >= o_size) {
      return 0;
   } else {
      output[*i]=store_heap[rootIndex];
      (*i)=(*i)+1;
      preorder_helper(store_heap, output, o_size, 2*rootIndex+1, i);
      preorder_helper(store_heap, output, o_size, 2*rootIndex+2, i);
      return 0;
   }
}

/* Recall: Pre-Order is Left-Right-Root */
/* Return: 0 for success and -1 otherwise */
int postorder(HeapType *pHeap, int **output, int *o_size) {
   int i=0;
   if ((pHeap == NULL) || (output == NULL) || (o_size == NULL)) {
      return -1;
   }
   *o_size = pHeap->end;
   *output = (int*)malloc((*o_size)*sizeof(int));
   return postorder_helper(pHeap->store, *output, *o_size, 0, &i);
}

int postorder_helper(int *store_heap, int *output, int o_size, int rootIndex, int *i) {
   if (rootIndex >= o_size) {
      return 0;
   } else if (2*rootIndex+1>=o_size) {
      output[*i] = store_heap[rootIndex];
      (*i)=(*i)+1;
      return 0;
   } else {
      postorder_helper(store_heap, output, o_size, 2*rootIndex+1, i);
      postorder_helper(store_heap, output, o_size, 2*rootIndex+2, i);
      output[*i]=store_heap[rootIndex];
      (*i)=(*i)+1;
      return 0;
   }
}

/* add "key" to the binary heap stored in "input" */
int addHeap(HeapType *pHeap, int key) {
   if (pHeap == NULL) {
      return -1;
   }
   if (pHeap->end == pHeap->size) {
      return -1;
   } else {
      (pHeap->store)[pHeap->end] = key;
      addHeap_helper(pHeap->end, pHeap->store);
      (pHeap->end) = (pHeap->end)+1;
      return 0;
   }
}

/* Recall: if val(node)>val(node's predecessor), swap node and predecessor */
int addHeap_helper(int index, int *store_heap) {
   int parent = 0;
   int temp_var = 0;
   if (store_heap == NULL) {
      return -1;
   }
   /* Below checks to ensure tree is not empty */
   if (index > 0) {
      parent = (index-1)/2;
      if (store_heap[parent] < store_heap[index]) {
         temp_var = store_heap[parent];
         store_heap[parent] = store_heap[index];
         store_heap[index] = temp_var;
         addHeap_helper(parent,store_heap);
      }
   }
   return 0;
}

/* look for whether there is an element key in the heap
 * Return: -1 for error, 0 for not found, 1 for found */
int findHeap(HeapType *pHeap, int key) {
   int i = 0;
   if (pHeap == NULL) {
      return -1;
   }
   for (i=0;i<(pHeap->end);i=i+1) {
      if ((pHeap->store)[i] == key) {
         return 1;
      }
   }
   return 0;
}

/* Recall: In a max-heap, max value is at the root */
/* remove the max value from the max-heap pHeap and return it to caller via "key" */
int delHeap(HeapType *pHeap, int *key) {
   if (pHeap == NULL) {return -1;}
   if (key == NULL) {return -1;}
   if ((pHeap->end) == 0) {return -1;}

   *key = (pHeap->store)[0];
   (pHeap->end)=(pHeap->end)-1;
   delHeap_helper(pHeap->end, pHeap->store, 0);
   return 0;
}

int delHeap_helper(int index, int *store_heap, int root) {
   int temp = 0;
   int left_child = 0;
   int right_child = 0;
   int max_child = 0;

   if (store_heap == NULL) {return -1;}

   left_child = 2*root+1;
   right_child = 2*root+2;

   if (right_child > index) {
      temp = store_heap[index];
      store_heap[index] = store_heap[root];
      store_heap[root] = temp;
   } else {
      if (store_heap[left_child]<=store_heap[right_child]) {
         max_child = right_child;
      } else {
         max_child = left_child;
      }

      store_heap[root] = store_heap[max_child];
      store_heap[max_child] = 0; // set value back to 0
      delHeap_helper(index,store_heap,max_child);
   }

   return 0;
}
