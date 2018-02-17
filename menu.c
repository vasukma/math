#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "setting.h"
#include "input.h"

//char get_menu_choice(char * string);

static void menu_show(void);

int
menu_run(void)
{
  char menu_choice;
  int exit = 0;

  do {
    menu_show();
    //menu_choice = get_menu_choice(input_buffer);
    menu_choice = input_get_char();
    //    printf("menu_choice: %d\n", menu_choice);
    switch (menu_choice) {
    case '1':
      printf("1. The numbers of digits: _\b");
      setting_set_digits(input_get_number());
      break;
    case '2':
      printf("2. The numbers of numbers: _\b");
      setting_set_members(input_get_number());
      break;
    case '3':
      printf("3. Mode 'column(1) or normal(0)': _\b");
      {
	//menu_choice = get_menu_choice(input_buffer);
	int choice_value = 1;
	choice_value = input_get_number();
	while ( ( choice_value < 0 ) || ( choice_value > 1 ) )
	  {
	    printf("Error! Try again: _\b");
	    choice_value = input_get_number();
	  }
	setting_set_mode(choice_value);
	//	printf("menu_choice: %c\n", menu_choice);
      }
      break;
    case '4':
      printf("4. The type of operation: _\b");
      setting_set_operation(input_get_number());
      break;

    case 'r':
      //      menu_choice = 'r';
      exit =1;
      break;

    case 'q':
      //      exit(0);
      exit = 1;
      //      menu_choice = 'q';
      break;

    default:
      fputs("Error! Try again.\n", stdout);
    }
    //  } while (mennu_choice != 'r') || (menu_choice !='q'));
      } while (!exit);

  return menu_choice;
}

void
menu_show(void)
{

    printf("------------------------------\n");
    printf("Setting\n");
    printf("------------------------------\n");
    printf("1. The numbers of digits ......... %d\n", setting_get_digits());
    printf("2. The numbers of numbers ........ %d\n", setting_get_members());
    printf("3. Mode 'column(1) or normal(0)' . %d\n", setting_get_mode());
    printf("4. Operation 'mult(1) or summ(0)'  %d\n", setting_get_operation());
    printf("r. Run.\n");
    printf("q. Quit.\n");
    printf("------------------------------\n");
    printf("You choice: _\b");

}
