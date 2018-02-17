#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stor.h"
#include "setting.h"
#include "menu.h"
#include "input.h"
#include "operation.h"

//void clear_input(void);
//static void operation(int operation, int max_val, int numbers, int mode);

//static void summation( void );
//static void multiplication(int numbers[], int members);


//static void summation_column_mode( const int numbers[] );
//static void summation_normal_mode( const int numbers[] );


int
main(void)
{
  //  int tmp = 0;
  printf("Mathematics new\n");
  while (menu_run() != 'q') {
    //    if (menu_run() == 'q') {
    //      exit(0);
    //    };
  //  printf("tmp: %d\n", tmp);
  //  storage = create_storage(settings.members);
    if (!stor_init(setting_get_members(), setting_get_max_member_val())) {
	fputs("Error init_storage()", stderr);
	exit(100);
      }
    //    stor_show_all_current();
    //    printf("########################\n");
  /*  do {
    //    switch (settings.operation) {
    switch (setting_get_operation()) {
      //    case MULTIPLICATION: multiplication();
      //      break;
    default: summation();
    };
    //    summation();

    operation(setting_get_operation(),
	      get_number_digits( setting_get_digits() ),
	      setting_get_members(),
	      setting_get_mode()
	      );
  */
    
    operation();

    
    //  } while (1);
  };
  
  return 0;
}


/* void clear_input(void) */
/* { */
/*   while (getchar() != '\n') */
/*     { */
/*       //      printf("clear\n"); */
/*       continue; */
/*     } */
/* } */

void
summation( void ) // delete
{
  /*  int max_val = get_number_digits( setting_get_digits() );

  int numbers[setting_get_members()];

  printf("Run summation...\n");

  do {

    srand( time( 0 ) );
    int i;
    //    int number;
    //    sum = 0;
    for ( i = 0; i < setting_get_members(); i++)
      {
	numbers[i] = rand() % max_val + 1;
	//	sum += numbers[i];
      }
    if ( setting_get_mode() )
      summation_column_mode( numbers );
    else
      summation_normal_mode( numbers );

  } while (getchar() != 's');
  */
}

void
summation_column_mode( const int numbers[] )
{
  int i;
  int sum = 0;

  //  printf("numbers[0]: %d\n", numbers[0]);
  printf("----------------------------\n");
  for ( i = 0; i < setting_get_members(); i++ )
    {
      printf("    %2d: %10d\n", i + 1, numbers[i]);
      sum += numbers[i];
    }
  printf("----------------------------\n");
  //s_gets(input_buffer, INPUT_BUFFER_SIZE);
  input_read();
  //    clear_input();
  printf("Answer: %10d\n", sum);
  printf("----------------------------\n");

}

void
summation_normal_mode( const int numbers[] )
{
  int i;
  int sum = 0;
  
  printf("----------------------------\n");
  for ( i = 0; i < setting_get_members(); i++ ) {
      printf("%d + ", numbers[i]);
      sum += numbers[i];
    }
  printf( "\b\b = " );
  //s_gets(input_buffer, INPUT_BUFFER_SIZE);
  input_read();
  //  if ( sum == atoi( input_buffer ) )
  if ( sum == input_get_number() )
    printf("Well done!\n");
  else
    printf("True answer: %d\n", sum);
  //  printf("----------------------------\n");

}


int get_digits(char * string)
{
  return atoi(string);
}



void
multiplication(int numbers[], int members)
{
  printf("Умножение\n");
  //  printf("numbers: %d, %d\n", numbers[0], members);

}


void
show_head_expession(void)
{
  printf("----------------------------\n");
}

/*
void
init_storage(int number_members)
{
  if (!reate_member_stor(number_members))
    exit(101);
  
  if (!init_stor_stack())
    exit(102);
}
*/
