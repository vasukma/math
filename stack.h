/*
  Работе со стеком указателей
 */

#ifndef STACK_H

#include "stack_type.h"

int stack_init();
//int push_stack(ptr_node_stor_stack * head, int * stor_ptr);
int stack_push(struct stack_node * head, int * stor_ptr);

#endif // STACK_H
