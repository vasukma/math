#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int
push_stack(stack_node * head, int * stor_ptr)
{
  stack_node * tmp = (stack_node *)malloc(sizeof(stack_node));
  if (!tmp)
    return 0;

  tmp->next = head;
  tmp->stor_ptr = stor_ptr;
  head = tmp;
  return 1;
}

int
stack_init()
{
  stack_node * stack;
  stack = (stack_node *)malloc(sizeof(stack_node));
  if (!stack) {
    //    fputs("Error stack_init()", stdout);
    return 0;
  }
  stack->next = NULL;
  return 1;
}

//stack_node
void
pop_stack(void)
{
  //  stack_node * tmp = ()
  
}

