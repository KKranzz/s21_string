#ifndef S21_UTILS_H
#define S21_UTILS_H

#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

void add_char(char *s, char c);

int is_delim(char c, const char *delim);

// sprintf
typedef struct flag_data {
  // flags
  int minus_flag;
  int plus_flag;
  int space_flag;
  int cell_flag;
  int zero_flag;
  // width
  int width;
  int width_set;
  // precion
  int precision;
  int precision_set;
  // length
  int l_prefix;
  int L_prefix;
  int h_prefix;

} flag_data;

void s21_handle_percent(char **iterator_str);

void s21_handle_character(char **iterator_str, va_list *args, flag_data fd);

void s21_handle_string(char **iterator_str, va_list *args, flag_data fd);

void int_to_string(char *res, long long digit);

void unsigned_to_string(char *res, unsigned long long digit);

void s21_handle_digital(char **iterator_str, va_list *args, flag_data fd);

void s21_handle_digital_int(char **iterator_str, va_list *args, flag_data fd);

void s21_handle_digital_int_long(char **iterator_str, va_list *args,
                                 flag_data fd);

void s21_handle_digital_int_short(char **iterator_str, va_list *args,
                                  flag_data fd);

void s21_handle_unsigned(char **iterator_str, va_list *args, flag_data fd);

void s21_handle_unsigned_long(char **iterator_str, va_list *args, flag_data fd);

void s21_handle_unsigned_short(char **iterator_str, va_list *args,
                               flag_data fd);

void s21_handle_unsigned_default(char **iterator_str, va_list *args,
                                 flag_data fd);

void s21_double_to_string(long double number, char *str, int precision,
                          int cell_flag);

void s21_handle_sign(long double *number, char **str);

void s21_round_number(long double *number, int precision);

long long s21_integer_partfn(long double number, long double *fractional_part);

void s21_write_integer_part(long long integer_part, char **str);

void s21_handle_overflow(char **str, int precision);

void s21_write_fractional_part(long double fractional_part, char **str,
                               int precision);

void s21_postfix_processor_double(const char *buffer, int size,
                                  char **iterator_str, flag_data fd);

void s21_handle_double(char **iterator_str, va_list *args, flag_data fd);

void s21_handle_double_default(char **iterator_str, va_list *args,
                               flag_data fd);

void s21_handle_double_long(char **iterator_str, va_list *args, flag_data fd);

void s21_mantissa_proc(double *double_arg, int *mantissa, int negative,
                       char *buffer, flag_data fd, int upper_case);

void s21_mantissa_proc_long(long double *double_arg, int *mantissa,
                            int negative, char *buffer, flag_data fd,
                            int upper_case);

void postfix_procc_e(flag_data fd, long double double_arg, char **iterator_str,
                     int size, const char *buffer);

void s21_handle_e(char **iterator_str, va_list *args, flag_data fd,
                  int upper_case);

void s21_handle_e_default(char **iterator_str, va_list *args, flag_data fd,
                          int upper_case);

void s21_handle_e_long(char **iterator_str, va_list *args, flag_data fd,
                       int upper_case);

int s21_count_significant_figures(double num, int precision, int mantissa,
                                  int cell_flag);

void s21_handle_g(char **iterator_str, va_list *args, flag_data fd,
                  int upper_case);

void to_hex_string(unsigned number, char *hex_str, int upper_case);

void to_hex_string_long(unsigned long long number, char *hex_str,
                        int upper_case);

void s21_handle_x(char **iterator_str, va_list *args, flag_data fd,
                  int upper_case);

void s21_handle_x_default(char **iterator_str, va_list *args, flag_data fd,
                          int upper_case);

void s21_handle_x_long(char **iterator_str, va_list *args, flag_data fd,
                       int upper_case);

void s21_handle_x_short(char **iterator_str, va_list *args, flag_data fd,
                        int upper_case);

void to_oct_string(unsigned int number, char *oct_str);

void to_oct_string_unsigned_long_long(unsigned long long number, char *oct_str);

void to_oct_string_unsigned_short(unsigned short number, char *oct_str);

void s21_handle_o(char **iterator_str, va_list *args, flag_data fd);
void s21_handle_o_default(char **iterator_str, va_list *args, flag_data fd);
void s21_handle_o_long(char **iterator_str, va_list *args, flag_data fd);
void s21_handle_o_short(char **iterator_str, va_list *args, flag_data fd);

void s21_handle_p(char **iterator_str, va_list *args, flag_data fd);

void s21_parse_flag(int *ch, const char **iterator_format, flag_data *fd);

void s21_swicther_spec(int *ch, char **iterator_str, va_list *args,
                       flag_data fd, const char **iterator_format);

void s21_sprintf_spec_processor(int *ch, char **iterator_str,
                                const char **iterator_format, va_list *args);

// end sprintf
#endif  // S21_UTILS_H