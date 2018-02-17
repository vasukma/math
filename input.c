#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

#define INPUT_BUFFER_SIZE 8
static char input_buffer[INPUT_BUFFER_SIZE];


//void s_gets(char * string, int n);
static void s_gets();

void
input_read(void)
{
  //s_gets(intput_buffer, INPUT_BUFFER_SIZE);
  s_gets();
}


void
s_gets(void)
{
  char * new_line;

  //  fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
  //  if (input_buffer)
  if (fgets(input_buffer, INPUT_BUFFER_SIZE, stdin))
    {
      if ((new_line =  strchr( input_buffer, '\n')))
	*new_line = '\0';
      else
	while (getchar() != '\n')
	  continue;
    }
}

int
input_get_number(void)
{
  s_gets();
  return atoi(input_buffer);
}

char
input_get_char(void)
{
  s_gets();
  return input_buffer[0];
}

/*
  char
  //get_menu_choice(char * string)
  input__menu_choice(char * string)
  {
  s_gets(string, INPUT_BUFFER_SIZE);
  
  //return atoi(string);
  return string[0];
  }
*/
