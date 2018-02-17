/* Типы для работы со стеком */

#ifndef STACK_TYPE_H

struct stack_node
{ /* Стек указателей хранилища */
  int *               stor_ptr;
  struct stack_node * next;
};
typedef struct stack_node stack_node;

#endif // STACK_TYPE_H
