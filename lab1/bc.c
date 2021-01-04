// Lab 1

/* test with: echo "1+2*(3+4*[5-6*{100+200}])" | ./a.out */

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

int ll_del_from_head(llnode **ppList) {
   if (ppList == NULL) {
      return -1;
   }
   llnode *temp = *ppList;
   *ppList = temp -> next;
   free(temp);
   return 0;
}

int push(llnode **x,char value) {
   return llnode_add_to_head(x,value);
}

int pop(llnode **x,char *return_value) {
   if (x == NULL | *x == NULL) {
      *return_value = ' ';
      return -1;
   }
   *return_value = ((*x)->value);

   return ll_del_from_head(x);
}

/* algorithm:
 * read in an expression from user (e.g., 1+2*(3+4*[5-6*{100+200}]))
 * in while loop:
 * - everytime you get a left bracket input, push it onto the stack
 * - everytime you get a right bracket input, pop stack to a variable (popped_value)
 * - make sure that popped_value is the correct opening bracket
 * - if it is, continue, otherwise, break */
int main(void) {
   int i = 0;
   char value = 'a';
   char popped_value = 'b';
   llnode *input_list=NULL;

   /* print out "PASS" or "FAIL, x" where x indicates failure at the xth char input */
   while (scanf("%c",&value) != EOF) {
      if ((value == '(') || (value == '[') || (value == '{')) {
         push(&input_list,value);
      } else if ((value == ')') || (value == ']') || (value == '}')) {
         pop(&input_list,&popped_value);
         if ((popped_value != '(') && (value == ')')) {
            printf("FAIL,%d\n",i);
            return -1;
         } else if ((popped_value != '[') && (value == ']')) {
            printf("FAIL,%d\n",i);
            return -1;
         } else if ((popped_value != '{') && (value == '}')) {
            printf("FAIL,%d\n",i);
            return -1;
         }
      }
      i = i+1;
   }
      
   /* ensure there are no more brackets in the stack */
   if (pop(&input_list,&popped_value) == -1){
      printf("PASS\n");
      return 0;
   } else {
      printf("FAIL,%d\n",i);
      return -1;
   }
}
