#ifndef SETTING_H
/*
  Работа с настройками программы
 */

enum Operation {SUMMATION, MULTIPLICATION};

int setting_get_operation(void);
void setting_set_operation(const int operation);
int setting_get_digits(void);
void setting_set_digits(const int digits);
int setting_get_members(void);
void setting_set_members(const int members);
int setting_get_mode(void);
void setting_set_mode(const int mode);
int setting_get_max_member_val(void);
#endif // SET_H
