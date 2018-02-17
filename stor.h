#ifndef STOR_H

/*
   Работа с оперативным хранилищем
 */
int stor_check_numbers(int * numbers);
/* Инициализация хранилища */
int stor_init(const int number_members, const int max_member_val);
int stor_put_answer(const int answer, const int correct);
void stor_show_all_current(void);
void stor_show_all_values(void);
void stor_show_simple_report(void);


#endif // STOR_H
