#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "setting.h"
#include "input.h"
#include "stor.h"

static void generate_member_values(int * numbers);
static void generate_answer(void);
static int check_zero_or_one(int members[]);


///* Возвращает количество цифр в члене */
//static int get_number_digits(const int number_digits );

void
//operation( int operation, int max_val, int members, int mode )
operation(void)
{
  //  int numbers[members];
  int members[setting_get_members()];
  int count;
  int i;
  int answer = 0;

  do {
    count = 0;
    generate_member_values(members);
    stor_check_numbers(members);
    if (check_zero_or_one(members)) {
      for ( i = 0; i < setting_get_members(); i++ )
	{
	  switch (setting_get_mode()){
	  case SUMMATION:
	    printf("%d + ", members[i]);
	    count += members[i];
	    break;
	  case MULTIPLICATION:
	    printf("%d * ", members[i]);
	    if (i == 0 && count == 0)
	      count = members[i];
	    else
	      count *= members[i];
	    break;
	  default: printf("error operation\n");
	  };
	}
      printf( "\b\b = " );
      answer = input_get_number();
      if (answer == -1) {
	break;
      }
      if (count == answer) {
	//      printf("Well done!\n");
	if (stor_put_answer(answer, 1)) {
	  break;
	}
      }
      else {
	stor_put_answer(answer, 0);
	printf("True answer: %d\n", count);
      
      }

    } else {
      if (stor_put_answer(answer, 1)) {
	break;
      }
    }
    // Функция проверяющая прорешанность всех упражнений
    //    stor_show_all_values();
  } while (1);// (getchar() != 's');
  if (!(answer == -1)) {
    printf("All exercises finished!\n");
  } else {
    printf("User finished!\n");
  }
  stor_show_simple_report();
}

/*
get_number_digits( int number_digits )
{
  int max_val = 0;
  int j;
  int step = 9;
  
  for ( j = 0; j < number_digits; j++, step *= 10 )
    {
      max_val += step;
    }

  return max_val;
}
*/
  
void
generate_member_values(int * numbers)
{
  int i;

  srand( time( 0 ) );
  for ( i = 0; i < setting_get_members(); i++)
    {
      numbers[i] =  rand() % (setting_get_max_member_val() + 1);
    }
}

void
generate_answer(void)
{
  int i, j, x;
  int numbers[2];

  printf("Generate... \n");
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      numbers[0] = i;
      numbers[1] = j;

      //      printf("numbers[0]: %d, numbers[1]: %d\n", numbers[0], numbers[1]);
      for (x = 0; x < 3; x++) {
	stor_check_numbers(numbers);
	stor_put_answer((numbers[0] * numbers[1]), 1);
      }
      //      numbers[0] = j;
      //      numbers[]
    }
  }
}

int
check_zero_or_one(int members[])
{
  int i;

  for (i = 0; i < setting_get_members(); i++) {
    if ((members[i] == 0) || (members[i] == 1)) {
      return 0;
    }
  }

  return 1;
}
