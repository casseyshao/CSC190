// Lab 8

#include<stdio.h>
#include<stdlib.h>

/* return value is 0 for success, -1 for error */
/* the use of < or lt() will result in a descending sort, and a max heap */
/* the use of > or gt() will result in an ascending sort, and a min heap */

typedef struct {
   int *store;
   unsigned int size;
   unsigned int end;
   int (*compare)(int x,int y);
} intHeap_T;

/* function prototypes */
int store(intHeap_T* heap,int value);
int helper_store(int index,int* store_heap,intHeap_T* heap);
int retrieve(intHeap_T* heap,int *rvalue);
int helper_retrieve(int index,int* store_heap,int root,intHeap_T* heap);
int lt(int x,int y);
int gt(int x,int y);
int hs(int *x,int size,int (*compare)(int x,int y));

int store(intHeap_T* heap,int value) {
   if (heap == NULL) {return -1;}
   if (heap->end == heap->size) {return -1;}

   (heap->store)[heap->end] = value;
   helper_store(heap->end,heap->store,heap);
   (heap->end) = (heap->end)+1;

   return 0;
}

/* Recall: if val(node)>val(node's predecessor), swap node and predecessor */
int helper_store(int index, int* store_heap, intHeap_T* heap) {
   int parent = 0;
   int temp_var = 0;

   if (store_heap == NULL) {return -1;}

   if (index > 0) {
      parent = (index-1)/2;
      if ((*(heap->compare))(store_heap[parent],store_heap[index]) == 1) {
         temp_var = store_heap[parent];
         store_heap[parent] = store_heap[index];
         store_heap[index] = temp_var;
         helper_store(parent,store_heap,heap);
      }
   }

   return 0;
}

/* stores the root value in rvalue */
int retrieve(intHeap_T* heap,int *rvalue) {
   if (heap == NULL) {return -1;}
   if (rvalue == NULL) {return -1;}
   if ((heap->end) == 0) {return -1;}

   *rvalue = (heap->store)[0];
   (heap->end)=(heap->end)-1;
   heap->store[0] = heap->store[heap->end];
   helper_retrieve(heap->end,heap->store,0,heap);

   return 0;
}

int helper_retrieve(int index,int* store_heap,int root,intHeap_T* heap) {
   int temp = 0;
   int left_child = 0;
   int right_child = 0;
   int max_child = 0;

   if (store_heap == NULL) {return -1;}

   left_child = 2*root+1;
   right_child = 2*root+2;

   if (left_child>=index) {
      return 0;
   } else if (right_child>=index) {
      if ((*(heap->compare))(store_heap[root],store_heap[left_child]) == 1) {
         temp = store_heap[root];
         store_heap[root] = store_heap[left_child];
         store_heap[left_child] = temp;
      }
   } else if (((*(heap->compare))(store_heap[root],store_heap[right_child]) == 1) && ((*(heap->compare))(store_heap[root],store_heap[left_child]) == 1)) {
      if ((*(heap->compare))(store_heap[left_child],store_heap[right_child]) == 1) {
         max_child = right_child;
      } else {
         max_child = left_child;
      }
      temp = store_heap[root];
      store_heap[root] = store_heap[max_child];
      store_heap[max_child] = temp;
      helper_retrieve(index,store_heap, max_child,heap);
   } else if ((*(heap->compare))(store_heap[root],store_heap[right_child]) == 1) {
      temp = store_heap[root];
      store_heap[root] = store_heap[right_child];
      store_heap[right_child] = temp;
      helper_retrieve(index,store_heap,right_child,heap);
   } else if ((*(heap->compare))(store_heap[root],store_heap[left_child]) == 1) {
      temp = store_heap[root];
      store_heap[root] = store_heap[left_child];
      store_heap[left_child] = temp;
      helper_retrieve(index,store_heap,left_child,heap);
   }

   return 0;
}

int lt(int x,int y) {
   if (x <= y) {return 1;}
   else {return 0;}
}

int gt(int x,int y){
   if (x >= y) {return 1;}
   else {return 0;}
}

/* control the type of sort (ascending or descending) by passing an appropriate compare function */
int hs(int *x,int size,int (*compare)(int x,int y)) {
   intHeap_T heap;
   heap.store = (int*)malloc(1000*sizeof(int));
   heap.size = 1000;
   heap.end = 0;
   heap.compare = compare;

   if (x == NULL) {return -1;}

   for (int i=0;i<size;i++) {
      store(&heap,x[i]);
   }

   int i = 0;
   while (i<size) {
      retrieve(&heap,&(x[i]));
      i = i+1;
   }

   return 0;
}

int main(void) {
   int x[] = {6,2,1,7,3,4,5};
   int size = 7;
   printf("Initial Array: ");
   printf("%d %d %d %d %d %d %d\n",x[0],x[1],x[2],x[3],x[4],x[5],x[6]);
   hs(x,size,gt);
   printf("Sorted Array: ");
   printf("%d %d %d %d %d %d %d\n",x[0],x[1],x[2],x[3],x[4],x[5],x[6]);
   return 0;
}
