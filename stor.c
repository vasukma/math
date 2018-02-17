/*
  Работа с оперетивным хранилищем
*/

#include <stdio.h>
#include <stdlib.h>
#include "stor.h"
//#include "stack.h"

//typedef struct member_statis_node_var
struct member_statis_node
{ /* Узел уровня статистики */
  struct member_statis_node * next;
  struct member_statis_node * prev;
  int value;
  int count_mistakes;
  int count_correct;
  int done;
};
typedef struct member_statis_node member_statis_node;


struct member_statis_layer_list
{ /* Структура управления узлами статистики */
  member_statis_node * head;
  //  member_statis_node * tail;
  member_statis_node * current;
  int done;
  int finished;
  struct member_layer_list * prev_member_layer;
};
typedef struct member_statis_layer_list member_statis_layer_list;

struct member_layer_node
{ /* Узел уровня членов */
  struct member_layer_node * next;
  struct member_layer_node * prev;
  struct member_layer_list * next_member_layer;
  member_statis_layer_list * member_statis_layer;
  int value;
  int done;
  //  int current_number_members;
};
typedef struct member_layer_node member_layer_node;

struct member_layer_list
{ /* Структура управления узлами уровней */
  member_layer_node * head;
  //  member_layer_node * tail;
   member_layer_node * current;
  int done;
  int finished;
  //  int finished_members; // количество правильно прорешшаных членов
  struct member_layer_list * prev_member_layer;
};
typedef struct member_layer_list member_layer_list;

//typedef struct
struct stor_type
{
  int true_answer; /* количество правильных ответов для члена */
                   /* для выполнения */
  int max_member_val;             /* максимальное кол. вариантов чл.*/
  int number_of_members;                /* количество членов     */
  member_layer_list * member_stor;      /* первый слой членов    */
  member_layer_list ** current_layers;  /* указатель на начало массива */
                                /* в котором хранятся указатели  */
                                /* на слои, которые используются */
                                /* в данный момент               */
  //  stack_node * head_ptr_stack; /* голова стека указателей */
  //} storage_type;
} * stor = NULL; /* сразу создаём указатель структуру управления хранилищем */
typedef struct stor_type stor_type;
//}
//storage_type * storage;
typedef struct stor_type stor_type;


static int add_node(member_layer_list * list, const int value, const int left_layer);
static int add_statis_node(member_statis_layer_list * list, const int value);

static member_layer_list * create_member_stor(const int number_of_layer);
static int create_tail(member_layer_list * list, int left_layer);
static member_layer_list * create_first_layer(void);
static member_layer_list * create_layer_tail(member_layer_list * list, int left_layer);
static int create_statis_layer_tail(member_layer_list * penult);

static stor_type * decl_stor(void);
static member_layer_list * decl_layer(void);
static member_statis_layer_list * decl_statis_layer(void);
static member_layer_node * decl_layer_node(void);
static member_statis_node * decl_statis_node(void);
inline static void do_next_node(member_layer_list * list)\
       {list->current = list->current->next;}
inline static void do_next_statis_node(member_statis_layer_list * list)\
       {list->current = list->current->next;}

static int find_member_layer_list(member_layer_list * list, int number);
static int find_or_add_member_layer(member_layer_list * list, int * number, const int left_layer);
static int find_or_add_member_statis_layer(member_statis_layer_list * list, int * number);

static void init_stor(stor_type * stor, int number_of_members, int max_member_val);
static void init_layer_list(member_layer_list * list, member_layer_list * prev_layer_list);
static void init_member_statis_layer_list(member_statis_layer_list * list, member_layer_list * prev_layer_list);
static void init_layer_node(member_layer_node * node, int value);
static void init_statis_node(member_statis_node * node, member_statis_node * head, int value);
static void insert_node(member_layer_list * list, member_layer_node * new_node);
static void insert_statis_node(member_statis_layer_list * list, member_statis_node * new_node);

inline static void reset_layer(member_layer_list * list) \
       {list->current = list->head;}
inline static void reset_statis_layer(member_statis_layer_list * list) \
       {list->current = list->head;}

static void show_layer(member_layer_list * layer);
static void show_layer_node(member_layer_node * node);
static void show_statis_layer(member_statis_layer_list * layer);
static void show_statis_node(member_statis_node * node);

int
stor_init(const int number_of_members, const int max_member_val)
{
  /* Инициализация укахателя на структуру */
  stor = decl_stor();
  if (!stor) {
    fputs("Error create storage.\n", stderr);
    return 0;
    }

  init_stor(stor, number_of_members, max_member_val);
  /* Создание уровней */
  stor->member_stor = create_member_stor(stor->number_of_members);
  if (!stor->member_stor) {
    fputs("Error create_members_stor()\n", stderr);
    return 0;
  }
  /*  // debug
  printf("stor->member_stor: %p\n", stor->member_stor);
  printf("stor->member_stor->done: %d\n", stor->member_stor->done);
  printf("stor->member_stor->current: %p\n", stor->member_stor->current);
  printf("stor->member_stor->current->prev: %p\n", stor->member_stor->current->prev);
  printf("stor->member_stor->current->next: %p\n", stor->member_stor->current->next);
  */
  return 1;
}

member_layer_list *
create_member_stor(const int number_of_layer)
{
  member_layer_list * first_layer = NULL;

  first_layer = create_first_layer();
  if (!first_layer) {
    fputs("Error create first member_layer_stor\n", stderr);
    return NULL;
  }

  /* 
     создание уровня членов и в конце уровня статистики
     первый уровень уже создан начинаем со второго
  */
  //  init_layer_list(first_layer, )

  if (!create_tail(first_layer, number_of_layer - 1)) {
    fputs("Error create tail\n", stderr);
    return NULL;
  }

  return first_layer;
}

member_layer_list *
create_first_layer(void)
{
  member_layer_list * list;

  list = decl_layer();
  if (!list) {
    fputs("Error create first member_layer_stor\n", stderr);
    return NULL;
  }
  init_layer_list(list, NULL);

  return list;
}

int
create_tail(member_layer_list * list, int left_layers)
{
  member_layer_list * penult = NULL;

  penult = create_layer_tail(list, left_layers);
  if (!penult) {
    fputs("Error create_layer_tail\n", stderr);
    return 0;
  }

  if (!create_statis_layer_tail(penult)) {
    fputs("Error create_statis_layer_tail\n", stderr);
    return 0;
  }
  return 1;
}

member_layer_list *
create_layer_tail(member_layer_list * list, int left_layers)
{
  member_layer_list * prev_layer = list;
  int i;

  //  printf("left 000 - left_layers: %d\n", left_layers);
  for (i = 0; i < left_layers - 1; i++) {
    prev_layer->current->next_member_layer = decl_layer();
    //    printf("left 111 - left_layers: %d\n", left_layers);
    if (!prev_layer->current->next_member_layer) {
      fputs("Error decl_member_layer_list()\n", stderr);
      return NULL;

    }

    init_layer_list(prev_layer->current->next_member_layer, prev_layer);
    prev_layer = prev_layer->current->next_member_layer;
  }
  //  printf("left 222 - left_layers: %d\n", left_layers);
  //  printf("l111 - layer: %p\n", prev_layer);
  //  show_layer(prev_layer);
  return prev_layer;
}

int
create_statis_layer_tail(member_layer_list * penult)
{
  penult->current->member_statis_layer = decl_statis_layer();
  if (!penult->current->member_statis_layer) {
    fputs("Error decl_member_statis_layer_list()\n", stderr);
    return 0;
  }
  init_member_statis_layer_list(penult->current->member_statis_layer, penult);

  return 1;
}

member_layer_list *
decl_layer(void)
{
  member_layer_list * list;

  list = (member_layer_list *)malloc(sizeof(member_layer_list));
  if (!list) {
    fputs("Error create member_layer_list\n", stderr);
    return NULL;
  }

  list->current = decl_layer_node();
  if (!list->current) {
    fputs("Error create node\n", stderr);
    return 0;
  }
  init_layer_node(list->current, 0);

  return list;
}

member_statis_layer_list *
decl_statis_layer(void)
{
  member_statis_layer_list * list;

  list = (member_statis_layer_list *)malloc(sizeof(member_statis_layer_list));
  if (!list) {
    fputs("Error create member_statis_layer\n", stderr);
    return NULL;
  }

  list->current = (member_statis_node *)malloc(sizeof(member_statis_node));
  if (!list->current) {
    fputs("Error create statistics node\n", stderr);
    return NULL;
  }
  init_statis_node(list->current, list->head, 0);

  return list;
}

int
stor_check_numbers(int * numbers)//, const int number_members)
{
  member_layer_list * current_layer = NULL;
  member_statis_layer_list * current_statis_layer = NULL;
  int left_layers = stor->number_of_members - 1;

  /*//debug
  int i;
  for ( i = 0; i < stor->number_of_members; i++) {
    printf("numbers[%d]: %d -- address: %p\n", i, numbers[i], (numbers + i));
  }
  printf("current_layer: %p\n", current_layer);
  //*/

    current_layer = stor->member_stor;
    //    left_layers = stor->number_of_members - 1;
    //    for (left_layer; left_layers > 1; left_layers--) {
      
      //    }

    do {
      if (!find_or_add_member_layer(current_layer, numbers, left_layers)) {
	fputs("Error find_or_add_member_layer() from stor_check_numbers()\n", stderr);
	return 0;
      }

      numbers++;
      left_layers--;

      if (current_layer->current->member_statis_layer) {
	current_statis_layer = current_layer->current->member_statis_layer;
	//	show_layer(current_layer);
	//	show_statis_layer(current_statis_layer);
      }
    } while ((current_layer = current_layer->current->next_member_layer));

    /*      while (current_layer->current->next_member_layer) {
r], stor->number_of_members)) {
    if (!find_or_add_member_layer(current_layer, numbers, left_layers)) {
      fputs("Error find_or_add_member_layer() from stor_check_numbers()\n", stderr);
      return 0;
    }
    current_layer = current_layer->current->next_member_layer;
    numbers++;
    left_layers--;
  }
  if (!find_or_add_member_layer(current_layer, numbers, left_layers)) {
    fputs("Error find_or_add_member_layer() from stor_check_numbers()\n", stderr);
    return 0;
  }

  left_layers--;
  numbers++;
*/
    
    //    if (!find_or_add_member_statis_layer(current_layer->current->member_statis_layer, numbers)) {
    if (!find_or_add_member_statis_layer(current_statis_layer, numbers)) {
      fputs("Error find_or_add_member_statis_layer() from stor_check_numbers()\n", stderr);
      return 0;
  }
    return 1;
}

int
find_member_layer_list(member_layer_list * list, int value)
{
  reset_layer(list);

  do {
    //  while (list->current->next) {
    if (list->current->value == value) {
      return 1;
    }
    if (list->current->value > value) {
      return 0;
    }
    do_next_node(list);
  } while (list->current != list->head);

  return 0;
}

int
find_member_statis_layer_list(member_statis_layer_list * list, int value)
{
  //  printf("v0 - numbers: %p - value: %d\n", &value, value);
  reset_statis_layer(list);
  //  printf("v1 - numbers: %p - value: %d\n", &value, value);
  do {
    if (list->current->value == value) {
      return 1;
    }
    if (list->current->value > value) {
      return 0;
    }
    do_next_statis_node(list);
  } while (list->current != list->head);

  return 0;
}

int
find_or_add_member_layer(member_layer_list * list, int * number, const int left_layer)
{
  if (find_member_layer_list(list, *number)) {
    if (list->current->done) {
      *number = -1;
      do {
	(*number)++;
	if (!find_member_layer_list(list, *number)) {
	  if(!add_node(list, *number,left_layer)) {
	    fputs("Error add_node() in find_or_add_member_layer()\n", stderr);
	    return 0;
	  } else {
	    return 1;
	  }
	}
      } while (list->current->done);
    }
    *number = list->current->value;
  } else {
    if (!add_node(list, *number, left_layer)) {
      fputs("Error add_node() in find_or_add_member_layer()\n", stderr);
      return 0;
    }
  }
  return 1;
}

int
find_or_add_member_statis_layer(member_statis_layer_list * list, int * number)
{
  if (find_member_statis_layer_list(list, *number)) {
    if (list->current->done) {
      *number = -1;
      do {
	(*number)++;
	if (!find_member_statis_layer_list(list, *number)) {
	  if(!add_statis_node(list, *number)) {
	    fputs("Error add_static_node() in find_or_add_member_static_layer()\n", stderr);
	    return 0;
	  } else {
	    return 1;
	  }
	}
      } while (list->current->done);
    }
    *number = list->current->value;
  } else {
    if(!add_statis_node(list, *number)) {
      fputs("Error add_static_node() in find_or_add_member_static_layer()\n", stderr);
      return 0;
    }
  }
  return 1;
}

int
add_node(member_layer_list * list, const int value, const int left_layer)
{
  member_layer_node * new_node = NULL;

  new_node = decl_layer_node();
  if (!new_node) {
    fputs("Error decl_layer_node in add_layer_node()\n", stderr);
    return 0;
  }
  init_layer_node(new_node, value);
  insert_node(list, new_node);
  if (!create_tail(list, left_layer)) {
      fputs("Error create_layer_tail in add_node()\n", stderr);
      return 0;
    }

  /*  if (!list->current->next_member_layer) {
    return 0;
    }*/

  return 1;
}


member_layer_node *
decl_layer_node(void)
{
  //  member_layer_list * list;

  return (member_layer_node *)malloc(sizeof(member_layer_node));
  //  return list;
}

member_statis_node *
decl_statis_node(void)
{
  return (member_statis_node *)malloc(sizeof(member_statis_node));
}

void
init_layer_node(member_layer_node * node, int value)
{
  node->next = NULL;
  node->prev = NULL;
  node->next_member_layer = NULL;
  node->member_statis_layer = NULL;
  node->value = value;
  node->done = 0;
}


void
insert_node(member_layer_list * list, member_layer_node * new_node)
{
  new_node->prev = list->current->prev;
  new_node->next = list->current;
  list->current->prev->next = new_node;
  list->current->prev = new_node;
  list->current = new_node;
}

void
init_layer_list(member_layer_list * list, member_layer_list * prev_layer_list)
{
  list->done = 0;
  list->finished = 0;
  list->head = list->current;
  list->current->next = list->head;
  list->current->prev = list->head;
  list->prev_member_layer = prev_layer_list;
}

void
init_member_statis_layer_list(member_statis_layer_list * list, member_layer_list * prev_layer_list)
{
  list->done = 0;
  list->finished = 0;
  list->head = list->current;
  list->current->next = list->head;
  list->current->prev = list->head;
  list->prev_member_layer = prev_layer_list;
}

void
init_statis_node(member_statis_node * node, member_statis_node * head, int value)
{
  if (value) {
    node->next = NULL;
    node->prev = NULL;
    node->value = value;
    node->count_mistakes = 0;
    node->count_correct = 0;
    node->done = 0;
  } else {
    node->next = head;
    node->prev = head;
    node->value = 0;
    node->count_mistakes = 0;
    node->count_correct = 0;
    node->done = 0;
  }
}

int
add_statis_node(member_statis_layer_list * list, const int value)
{
  member_statis_node * new_node;

  new_node = decl_statis_node();
  if (!new_node) {
    fputs("Error create member_statis_layer_node in add_statis_layer_node()\n", stderr);
    return 0;
  }
  init_statis_node(new_node, NULL, value);
  insert_statis_node(list, new_node);
  /*
  create_tail(list, left_layer);
  if (!list->current->next_member_layer) {
    return 0;
  }
  */
  return 1;
}

void
insert_statis_node(member_statis_layer_list * list, member_statis_node * new_node)
{
  new_node->prev = list->current->prev;
  new_node->next = list->current;
  list->current->prev->next = new_node;
  list->current->prev = new_node;
  list->current = new_node;

  //  return new_layer_node;
}

stor_type *
decl_stor(void)
{
  return (stor_type *)malloc(sizeof(stor_type));
}

void
init_stor(stor_type * stor, int number_of_members, int max_member_val)
{
  stor->number_of_members = number_of_members;
  stor->true_answer = 1;
  stor->max_member_val = max_member_val + 1;
  stor->member_stor = NULL;
}

int
stor_put_answer(const int answer, const int correct)
{
  member_layer_list * current_layer = stor->member_stor;
  member_statis_layer_list * current_statis_layer;

  while (current_layer->current->next_member_layer) {
    current_layer = current_layer->current->next_member_layer;
  }
  current_statis_layer = current_layer->current->member_statis_layer;
  if (correct) {
    current_statis_layer->current->count_correct++;
    if (current_statis_layer->current->count_correct == (current_statis_layer->current->count_mistakes + stor->true_answer)) {
      current_statis_layer->current->done = 1;
      current_statis_layer->finished++;
      if (current_statis_layer->finished == stor->max_member_val) {
	current_statis_layer->done = 1;
	current_layer->current->done = 1;
	current_layer->finished++;
	while(current_layer->finished == stor->max_member_val) {
	  current_layer->done = 1;
	  if (current_layer->prev_member_layer) {
	    current_layer = current_layer->prev_member_layer;
	    current_layer->finished++;
	  } else {
	    break;
	  }
	}
      }
    }
  } else {
    current_statis_layer->current->count_mistakes++; 
  }
  if (stor->member_stor->done) {
    return 1;
  }
  //  printf("last member: %d\n", current_statis_layer->current->value);
  //  printf("stor->max_member_val: %d\n", stor->max_member_val);
  //  show_layer(current_layer);
  //  show_layer_node(current_layer->current);
  //  show_statis_layer(current_statis_layer);
  //  show_statis_node(current_statis_layer->current);

  return 0;
}

void
stor_show_all_current(void)
{
  member_layer_list * layer = stor->member_stor;

  while (layer->current->next_member_layer) {
    printf("error\n");
    //    show_layer(layer);
    layer = layer->current->next_member_layer;
  }
  show_layer(layer);
  show_statis_layer(layer->current->member_statis_layer);
  printf("-----------------------------------\n");
}

void
show_layer(member_layer_list * layer)
{
  printf("layer -----------------------------\n");
  printf("address:\t%p\n", layer);
  printf("finished:\t%d\n", layer->finished);
  printf("done:\t\t%d\n", layer->done);
  printf("node ------------------------------\n");
  show_layer_node(layer->current);
  printf("-----------------------------------\n");
}

void
show_layer_node(member_layer_node * node)
{
  printf("address:\t\t%p\n", node);
  printf("next_member_layer:\t%p\n", node->next_member_layer);
  printf("member_statis_layer:\t%p\n", node->member_statis_layer);
  printf("value:\t\t%d\n", node->value);
  printf("done:\t\t%d\n", node->done);
}

void
show_statis_layer(member_statis_layer_list * layer)
{
  printf("statis layer ----------------------\n");
  printf("address:\t%p\n", layer);
  printf("finished:\t%d\n", layer->finished);
  printf("done:\t\t%d\n", layer->done);
  printf("statis node -----------------------\n");
  show_statis_node(layer->current);
}
void
show_statis_node(member_statis_node * node)
{
  printf("address:\t%p\n", node);
  printf("value:\t\t%d\n", node->value);
  printf("done:\t\t%d\n", node->done);
  printf("count_mistakes:\t%d\n", node->count_mistakes);
  printf("count_correct:\t%d\n", node->count_correct);
}

void
stor_show_all_values(void)
{
  member_layer_list * current_layer = stor->member_stor;
  member_statis_layer_list * current_statis_layer;

  reset_layer(current_layer);
  printf("%p ", current_layer);
  printf("finished: %d ", current_layer->finished);
  printf("done: %d\n", current_layer->done);
  do {
    printf("\t%d - %p\n", current_layer->current->value, current_layer->current);

    current_statis_layer = current_layer->current->member_statis_layer;
    //    do {
      reset_statis_layer(current_statis_layer);
      printf("\t\t%p ", current_statis_layer);
      printf("finished: %d ", current_statis_layer->finished);
      printf("done: %d\n", current_statis_layer->done);
      do {
	printf("\t\t\t%d - %p ", current_statis_layer->current->value, current_statis_layer->current);
	printf("correct: %d ", current_statis_layer->current->count_correct);
	printf("done: %d\n", current_statis_layer->current->done);
	do_next_statis_node(current_statis_layer);
      } while (current_statis_layer->current != current_statis_layer->head);
	//    } while ();
    do_next_node(current_layer);
    //    printf("current_layer->current: %p\n", current_layer->current);
    //    printf("current_layer->head: %p\n", current_layer->head);
  } while (current_layer->current != current_layer->head);
}

/*
void
stor_show_report(void)
{
  member_layer_list * current_layer = stor->member_stor;
  member_statis_layer_list * curent_statis_layer = NULL;
  
  reset_layer(current_layer);
  do {
    do
    if (current_layer->current->)


  } while (current_layer->current != current_layer->head);

  do {
    reset_layer(current_layer);
    do {
      if
    } 
  } while (current_layer);

  
}
*/
void
stor_show_simple_report(void)
{
  member_layer_list * current_layer = stor->member_stor;
  member_statis_layer_list * current_statis_layer;

  reset_layer(current_layer);
  //  printf("%p ", current_layer);
  //  printf("finished: %d ", current_layer->finished);
  //  printf("done: %d\n", current_layer->done);
  do {
    printf("%2d * ", current_layer->current->value);

    current_statis_layer = current_layer->current->member_statis_layer;
    reset_statis_layer(current_statis_layer);
    //      printf("  %p ", current_statis_layer);
    //      printf("finished: %d ", current_statis_layer->finished);
    //      printf("done: %d\n", current_statis_layer->done);
    do {
      printf("\t%2d | ", current_statis_layer->current->value);
      printf("correct: %d; ", current_statis_layer->current->count_correct);
      printf("mistakes: %d\n", current_statis_layer->current->count_mistakes);
      do_next_statis_node(current_statis_layer);
    } while (current_statis_layer->current != current_statis_layer->head);
    do_next_node(current_layer);
  } while (current_layer->current != current_layer->head);
}
