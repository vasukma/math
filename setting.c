#include "setting.h"


// default settings
// max the nimbers digits in a number
#define DIGITS 1
// the number numbers in exercises
#define NUMBERS 2
// mode colum (1) or normal (0)
#define MODE 1
// the type of operation:
// 1 - multiplication
//#define OPERATION 1

struct {
  int digits;   /* количество цифр в членах */
  int members;  /* количество членов */
  int mode;     /* режим отображения */
  int operation;/* тип действия */
} setting = {DIGITS, NUMBERS, MODE, MULTIPLICATION};

int
setting_get_operation(void)
{
  return setting.operation;
}

void
setting_set_operation(const int operation)
{
  setting.operation = operation;
}

int
setting_get_digits(void)
{
  return setting.digits;
}

void
setting_set_digits(const int digits)
{
  setting.digits = digits;
}

int
setting_get_members(void)
{
  return setting.members;
}

void
setting_set_members(const int members)
{
  setting.members = members;
}

int
setting_get_mode(void)
{
  return setting.mode;
}

void
setting_set_mode(const int mode)
{
  setting.mode = mode;
}

int
setting_get_max_member_val(void)
{
  int max_val = 0;
  int j;
  int step = 9;
  
  for ( j = 0; j < setting.digits; j++, step *= 10 )
    {
      max_val += step;
    }

  return max_val;

} 
