// Lab 8

#include<stdio.h>
#include<stdlib.h>

/* 1 is True, 0 is False, -1 is error */
int bs(int *x,int size,int (*compare)(int x,int y));
int lt(int x,int y); // comparison function
int gt(int x,int y); // comparison function

/* int (*compare)(int x,int y) calls lt() and gt() */
/* Arguments: array, size of array, comparison function */
int bs(int *x,int size,int (*compare)(int x,int y)) {
   int swapped = 0;
   int temp = 0;
   int N = size;

   if (x == NULL) {return -1;}

   while (1) {
      swapped = 0;
      for (int j=0;j<N-1;j++) {
         if (((*compare)(x[j],x[j+1])) == 1) {
            temp = x[j];
            x[j] = x[j+1];
            x[j+1] = temp;
            swapped = 1;
         }
      }
      if (swapped == 0) {
         break;
      }
   }
   return 0;
}

/* descending order */
int lt(int x,int y) {
   if (x <= y) {return 1;}
   else {return 0;}
}

/* ascending order */
int gt(int x,int y) {
   if (x >= y) {return 1;}
   else {return 0;}
}

/* pseudocode for main given in lab instructions */
int main(void) {
   // build first array
   int vals[10];
   for (int i=0;i<10;i=i+1){
      vals[i]=100-i;
   }
   for (int i=0;i<10;i++){
      printf("in[%d]=%d\n",i,vals[i]);
   }

   // sort in ascending order
   bs(vals,10,gt);
   for (int i=0;i<10;i++){
      printf("out[%d]=%d\n",i,vals[i]);
   }

   // build second array
   int vals2[10];
   for (int i=0;i<10;i=i+1){
      vals2[i]=i;
   }
   for (int i=0;i<10;i++){
      printf("in[%d]=%d\n",i,vals2[i]);
   }

   // sort in descending order
   bs(vals2,10,lt);
   for (int i=0;i<10;i++){
      printf("out[%d]=%d\n",i,vals2[i]);
   }

   return 0;
}
