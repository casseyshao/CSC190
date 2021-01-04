// Lab 1

#include <stdio.h>
#include <stdlib.h>

struct llnode {
   char value;
   struct llnode *next;
};
typedef struct llnode llnode;

int llnode_add_to_head(llnode **head,char value) {
   if (head == NULL) {
      return -1;
   }
	llnode *old_head = *head;

   *head = (llnode *) malloc(sizeof(llnode));
   (*head) -> value = value;
	(*head) -> next = old_head;
	return 0;
}

int llnode_add_to_tail(llnode **x,char value) {
   if (x==NULL) {
      return -1;
   }

   if (*x==NULL) {
      *x = (llnode *) malloc(sizeof(llnode));
      (*x)->value = value;
      (*x)->next = NULL;
      return 0;
   } else {
      return llnode_add_to_tail(&((*x)->next),value);
   }
}

int llnode_print_from_head(llnode *x) {
   if (x==NULL) {
      return 0;
   } else {
      printf("%c\n",x->value);
      return llnode_print_from_head(x->next);
   }
}

int llnode_print_from_tail(llnode *x) {
   if (x==NULL) {
      return 0;
   } else {
      if (x->next == NULL) {
         printf("%c\n",x->value);
	      return 0;
      } else {
         llnode_print_from_tail(x->next);
         printf("%c\n",x->value);
	      return 0;
      }
   }
}

/* use llnode_add_to_head() to add value to linked list so that it behaves like a stack */
/* llnode_add_to_head() function returns 0 and -1 */
int push(llnode **x,char value) {
   return llnode_add_to_head(x,value);
}

int ll_del_from_head(llnode **ppList) {
   /* check if list is empty */
   if (ppList == NULL | *ppList == NULL) {
      return -1;
   }
   llnode *temp = *ppList;
   *ppList = temp->next;
   free(temp);
   return 0;
}

/* assign to *return_value the head node value so that list behaves like a stack */
/* (1) check that array and head exist
 * (2) store popped value
 * (3) delete popped value */
/* return 0 for success and -1 for failure */
int pop(llnode **x,char *return_value) {
   if (x == NULL | *x == NULL) {
      return -1;
   }
   *return_value = ((*x)->value);

   return ll_del_from_head(x);
}

/* modify main() so that instead of calling add/print, it calls push/pop */
int main(void) {
   int n=0;
   char value='a';
   int rvalue=0;
   llnode *input_list=NULL;

   while (scanf("%c",&value) != EOF) {
      n=n+1;
      push(&input_list,value);
   }

   printf("INFO: you entered %d items\n",n);

   while (input_list != NULL) {
      //llnode_print_from_head(input_list);
      //printf("\n");
      rvalue=pop(&input_list,&value);
   }

   if ( !(rvalue==0) ) {
      printf("ERR: llnode_print returned an error\n");
   }

   return 0;
}
