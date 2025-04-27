#include "../s21_string.h"
#include "../s21_types.h"
#include "../s21_utils.h"

void s21_handle_percent(char** iterator_str) {
  **iterator_str = '%', (*iterator_str)++;
}

void s21_handle_character(char** iterator_str, va_list* args, flag_data fd) {
  if (fd.minus_flag == 0) {
    for (int i = 0; i < fd.width - 1; i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }
  **iterator_str = (char)va_arg(*args, int), (*iterator_str)++;
  if (fd.minus_flag == 1) {
    for (int i = 0; i < fd.width - 1; i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }
}

void s21_handle_string(char** iterator_str, va_list* args, flag_data fd) {
  char* str_arg = va_arg(*args, char*);
  int str_length =
      fd.precision < (int)s21_strlen(str_arg) && fd.precision_set != 0
          ? fd.precision
          : (int)s21_strlen(str_arg);

  if (fd.minus_flag == 0) {
    for (int i = 0; i < fd.width - str_length; i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }

  for (int i = 0; i < str_length; i++, str_arg++) {
    **iterator_str = *str_arg, (*iterator_str)++;
  }

  if (fd.minus_flag == 1) {
    for (int i = 0; i < fd.width - str_length; i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }
}

void int_to_string(char* res, long long digit) {
  long long tmp_digit = llabs(digit);
  char reverse_record_int[1000] = {0};
  for (int i = 0; tmp_digit / 10 != 0; i++, tmp_digit /= 10) {
    reverse_record_int[i] = (tmp_digit % 10) + '0';
  }

  reverse_record_int[s21_strlen(reverse_record_int)] = (tmp_digit % 10) + '0';

  for (int i = s21_strlen(reverse_record_int) - 1, j = 0; i >= 0; i--, j++) {
    res[j] = reverse_record_int[i];
  }
}

void unsigned_to_string(char* res, unsigned long long digit) {
  unsigned long long tmp_digit = digit;
  char reverse_record_unsig[1000] = {0};
  for (int i = 0; tmp_digit / 10 != 0; i++, tmp_digit /= 10) {
    reverse_record_unsig[i] = (tmp_digit % 10) + '0';
  }

  reverse_record_unsig[s21_strlen(reverse_record_unsig)] =
      (tmp_digit % 10) + '0';

  for (int i = s21_strlen(reverse_record_unsig) - 1, j = 0; i >= 0; i--, j++) {
    res[j] = reverse_record_unsig[i];
  }
}
void s21_handle_digital_int(char** iterator_str, va_list* args, flag_data fd);

void s21_handle_digital(char** iterator_str, va_list* args, flag_data fd) {
  if (fd.l_prefix == 1) {
    s21_handle_digital_int_long(iterator_str, args, fd);
  } else if (fd.h_prefix == 1) {
    s21_handle_digital_int_short(iterator_str, args, fd);
  } else {
    s21_handle_digital_int(iterator_str, args, fd);
  }
}

void s21_handle_digital_int(char** iterator_str, va_list* args, flag_data fd) {
  int int_arg = va_arg(*args, int), tmp_int_arg = int_arg, length_arg = 1;
  if (fd.minus_flag == 1 || fd.precision_set == 1) {
  } else if (fd.zero_flag == 1 && fd.precision_set == 0) {
    fd.precision = fd.width;
    if (int_arg < 0 || fd.plus_flag == 1 || fd.space_flag == 1) fd.precision--;
  }

  while (abs(tmp_int_arg) >= 10) {
    tmp_int_arg /= 10;
    length_arg++;
  }

  length_arg = fd.precision > length_arg ? fd.precision : length_arg;

  for (int i = 0;
       i < fd.width - length_arg -
               (int_arg < 0 || fd.plus_flag == 1 || fd.space_flag == 1) &&
       fd.minus_flag == 0;
       i++) {
    **iterator_str = ' ', (*iterator_str)++;
  }

  if (int_arg >= 0 && (fd.plus_flag == 1 || fd.space_flag == 1)) {
    char predict = fd.plus_flag == 1 ? '+' : ' ';
    **iterator_str = predict, (*iterator_str)++;
  } else if (int_arg < 0) {
    **iterator_str = '-', (*iterator_str)++;
  }

  char int_converted[1000] = {0};
  int_to_string(int_converted, int_arg);
  for (int i = 0; i < fd.precision - (int)s21_strlen(int_converted); i++) {
    **iterator_str = '0', (*iterator_str)++;
  }

  for (int i = 0; i < (int)s21_strlen(int_converted); i++) {
    **iterator_str = int_converted[i], (*iterator_str)++;
  }

  if (fd.minus_flag == 1) {
    for (int i = 0;
         i < fd.width - length_arg -
                 (int_arg < 0 || fd.plus_flag == 1 || fd.space_flag == 1);
         i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }
}

void s21_handle_digital_int_long(char** iterator_str, va_list* args,
                                 flag_data fd) {
  long long int_arg = va_arg(*args, long long), tmp_int_arg = int_arg,
            length_arg = 1;
  if (fd.minus_flag == 1 || fd.precision_set == 1) {
  } else if (fd.zero_flag == 1 && fd.precision_set == 0) {
    fd.precision = fd.width;
    if (int_arg < 0 || fd.plus_flag == 1 || fd.space_flag == 1) fd.precision--;
  }

  for (int j = 0; llabs(tmp_int_arg) >= 10; tmp_int_arg /= 10, j++) {
    length_arg++;
  }

  length_arg = fd.precision > length_arg ? fd.precision : length_arg;

  for (int i = 0;
       i < fd.width - length_arg -
               (int_arg < 0 || fd.plus_flag == 1 || fd.space_flag == 1) &&
       fd.minus_flag == 0;
       i++) {
    **iterator_str = ' ', (*iterator_str)++;
  }

  if (int_arg >= 0 && (fd.plus_flag == 1 || fd.space_flag == 1)) {
    char predict = fd.plus_flag == 1 ? '+' : ' ';
    **iterator_str = predict, (*iterator_str)++;
  } else if (int_arg < 0)
    **iterator_str = '-', (*iterator_str)++;

  char int_converted[1000] = {0};
  int_to_string(int_converted, int_arg);

  for (int i = 0; i < fd.precision - (int)s21_strlen(int_converted); i++) {
    **iterator_str = '0', (*iterator_str)++;
  }

  for (int i = 0; i < (int)s21_strlen(int_converted); i++) {
    **iterator_str = int_converted[i], (*iterator_str)++;
  }

  if (fd.minus_flag == 1) {
    for (int i = 0;
         i < fd.width - length_arg -
                 (int_arg < 0 || fd.plus_flag == 1 || fd.space_flag == 1);
         i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }
}

void s21_handle_digital_int_short(char** iterator_str, va_list* args,
                                  flag_data fd) {
  short int_arg = va_arg(*args, int), tmp_int_arg = int_arg, length_arg = 1;
  if (fd.minus_flag == 1 || fd.precision_set == 1) {
  } else if (fd.zero_flag == 1 && fd.precision_set == 0) {
    fd.precision = fd.width;
    if (int_arg < 0 || fd.plus_flag == 1 || fd.space_flag == 1) fd.precision--;
  }

  while (abs(tmp_int_arg) >= 10) {
    tmp_int_arg /= 10;
    length_arg++;
  }

  length_arg = fd.precision > length_arg ? fd.precision : length_arg;

  for (int i = 0;
       i < fd.width - length_arg -
               (int_arg < 0 || fd.plus_flag == 1 || fd.space_flag == 1) &&
       fd.minus_flag == 0;
       i++) {
    **iterator_str = ' ', (*iterator_str)++;
  }

  if (int_arg >= 0 && (fd.plus_flag == 1 || fd.space_flag == 1)) {
    char predict = fd.plus_flag == 1 ? '+' : ' ';
    **iterator_str = predict, (*iterator_str)++;
  } else if (int_arg < 0) {
    **iterator_str = '-', (*iterator_str)++;
  }

  char int_converted[1000] = {0};
  int_to_string(int_converted, int_arg);
  for (int i = 0; i < fd.precision - (int)s21_strlen(int_converted); i++) {
    **iterator_str = '0', (*iterator_str)++;
  }

  for (int i = 0; i < (int)s21_strlen(int_converted); i++) {
    **iterator_str = int_converted[i], (*iterator_str)++;
  }

  if (fd.minus_flag == 1) {
    for (int i = 0;
         i < fd.width - length_arg -
                 (int_arg < 0 || fd.plus_flag == 1 || fd.space_flag == 1);
         i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }
}

void s21_handle_unsigned(char** iterator_str, va_list* args, flag_data fd) {
  if (fd.l_prefix == 1) {
    s21_handle_unsigned_long(iterator_str, args, fd);
  } else if (fd.h_prefix == 1) {
    s21_handle_unsigned_short(iterator_str, args, fd);
  } else {
    s21_handle_unsigned_default(iterator_str, args, fd);
  }
}

void s21_handle_unsigned_short(char** iterator_str, va_list* args,
                               flag_data fd) {
  unsigned short int_arg = va_arg(*args, unsigned);
  unsigned short tmp_int_arg = int_arg;
  int length_arg = 1;

  if (fd.minus_flag == 1 || fd.precision_set == 1) {
  } else if (fd.zero_flag == 1 && fd.precision_set == 0) {
    fd.precision = fd.width;
  }

  while (tmp_int_arg >= 10) {
    tmp_int_arg /= 10;
    length_arg++;
  }

  length_arg = fd.precision > length_arg ? fd.precision : length_arg;

  if (fd.minus_flag == 0) {
    for (int i = 0; i < fd.width - length_arg; i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }

  char unsig_converted[1000] = {0};
  unsigned_to_string(unsig_converted, int_arg);

  for (int i = 0; i < fd.precision - (int)s21_strlen(unsig_converted); i++) {
    **iterator_str = '0', (*iterator_str)++;
  }

  for (int i = 0; i < (int)s21_strlen(unsig_converted); i++) {
    **iterator_str = unsig_converted[i], (*iterator_str)++;
  }

  if (fd.minus_flag == 1) {
    for (int i = 0; i < fd.width - length_arg; i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }
}

void s21_handle_unsigned_long(char** iterator_str, va_list* args,
                              flag_data fd) {
  unsigned long long int_arg = va_arg(*args, unsigned long long);
  unsigned long long tmp_int_arg = int_arg;
  int length_arg = 1;

  if (fd.minus_flag == 1 || fd.precision_set == 1) {
  } else if (fd.zero_flag == 1 && fd.precision_set == 0) {
    fd.precision = fd.width;
  }

  while (tmp_int_arg >= 10) {
    tmp_int_arg /= 10;
    length_arg++;
  }

  length_arg = fd.precision > length_arg ? fd.precision : length_arg;

  if (fd.minus_flag == 0) {
    for (int i = 0; i < fd.width - length_arg; i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }

  char unsig_converted[1000] = {0};
  unsigned_to_string(unsig_converted, int_arg);

  for (int i = 0; i < fd.precision - (int)s21_strlen(unsig_converted); i++) {
    **iterator_str = '0', (*iterator_str)++;
  }

  for (int i = 0; i < (int)s21_strlen(unsig_converted); i++) {
    **iterator_str = unsig_converted[i], (*iterator_str)++;
  }

  if (fd.minus_flag == 1) {
    for (int i = 0; i < fd.width - length_arg; i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }
}

void s21_handle_unsigned_default(char** iterator_str, va_list* args,
                                 flag_data fd) {
  unsigned int_arg = va_arg(*args, unsigned);
  unsigned tmp_int_arg = int_arg;
  int length_arg = 1;

  if (fd.minus_flag == 1 || fd.precision_set == 1) {
  } else if (fd.zero_flag == 1 && fd.precision_set == 0) {
    fd.precision = fd.width;
  }

  while (tmp_int_arg >= 10) {
    tmp_int_arg /= 10;
    length_arg++;
  }

  length_arg = fd.precision > length_arg ? fd.precision : length_arg;

  if (fd.minus_flag == 0) {
    for (int i = 0; i < fd.width - length_arg; i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }

  char unsig_converted[1000] = {0};
  unsigned_to_string(unsig_converted, int_arg);

  for (int i = 0; i < fd.precision - (int)s21_strlen(unsig_converted); i++) {
    **iterator_str = '0', (*iterator_str)++;
  }

  for (int i = 0; i < (int)s21_strlen(unsig_converted); i++) {
    **iterator_str = unsig_converted[i], (*iterator_str)++;
  }

  if (fd.minus_flag == 1) {
    for (int i = 0; i < fd.width - length_arg; i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }
}

void s21_double_to_string(long double number, char* str, int precision,
                          int cell_flag) {
  s21_handle_sign(&number, &str);

  s21_round_number(&number, precision);

  long double fractional_part;
  long long integer_part = s21_integer_partfn(number, &fractional_part);

  s21_write_integer_part(integer_part, &str);

  if (precision > 0 || cell_flag == 1) {
    *str++ = '.';
    s21_write_fractional_part(fractional_part, &str, precision);
  }

  *str = '\0';
}

void s21_handle_sign(long double* number, char** str) {
  if (*number < 0) {
    **str = '-';
    (*str)++;
    *number = -(*number);
  }
}

void s21_round_number(long double* number, int precision) {
  long double factor = powl(10, precision);
  *number = roundl(*number * factor) / factor;
}

long long s21_integer_partfn(long double number, long double* fractional_part) {
  long long int_part = number;
  *fractional_part = number - int_part;
  return int_part;
}

void s21_write_integer_part(long long integer_part, char** str) {
  char temp[2048];
  int i = 0;

  if (integer_part == 0) {
    temp[i++] = '0';
  } else {
    while (integer_part > 0) {
      temp[i++] = (integer_part % 10) + '0';
      integer_part /= 10;
    }
  }

  for (int j = i - 1; j >= 0; j--) {
    **str = temp[j];
    (*str)++;
  }
}

void s21_write_fractional_part(long double fractional_part, char** str,
                               int precision) {
  for (int j = 0; j < precision; j++) {
    fractional_part *= 10.0;
    long long frac_digit = fractional_part;
    **str = frac_digit + '0';
    (*str)++;
    fractional_part -= frac_digit;

    if (j == precision - 1 && fractional_part >= 0.5) {
      (*str)[-1]++;
    }
  }

  if ((*str)[-1] > '9') {
    (*str)[-1] = '0';
    s21_handle_overflow(str, precision);
  }
}

void s21_handle_overflow(char** str, int precision) {
  for (int k = 1; k <= precision; k++) {
    if ((*str)[-1 - k] == '9') {
      (*str)[-1 - k] = '0';
      if (k == precision) {
        for (int m = precision; m > 0; m--) {
          (*str)[m] = (*str)[m - 1];
        }
        **str = '1';
        (*str)++;
      }
    } else {
      (*str)[-1 - k]++;
      k = precision;
    }
  }
}

void s21_handle_double(char** iterator_str, va_list* args, flag_data fd) {
  if (fd.L_prefix == 1) {
    s21_handle_double_long(iterator_str, args, fd);
  } else {
    s21_handle_double_default(iterator_str, args, fd);
  }
}
void s21_handle_double_long(char** iterator_str, va_list* args, flag_data fd) {
  double double_arg = va_arg(*args, long double);
  fd.precision = fd.precision_set == 1 ? fd.precision : 6;

  if (double_arg < 0) {
    fd.plus_flag = 0;
    fd.space_flag = 0;
  }
  char buffer[4096] = {0};
  s21_double_to_string(double_arg, buffer, fd.precision, fd.cell_flag);
  int size = s21_strlen(buffer);

  if (fd.minus_flag == 1) {
    fd.zero_flag = 0;
  }

  char filler = fd.zero_flag == 1 ? '0' : ' ';

  if (fd.zero_flag == 1) {
    if ((fd.plus_flag || fd.space_flag) && double_arg >= 0) {
      if (fd.plus_flag == 1) {
        **iterator_str = '+', (*iterator_str)++;
      } else {
        **iterator_str = ' ', (*iterator_str)++;
      }
    }
  }

  for (int i = 0; i < fd.width - size - (fd.plus_flag || fd.space_flag) &&
                  fd.minus_flag == 0;
       i++) {
    **iterator_str = filler, (*iterator_str)++;
  }

  if (fd.zero_flag == 0) {
    if ((fd.plus_flag || fd.space_flag) && double_arg >= 0) {
      if (fd.plus_flag == 1) {
        **iterator_str = '+', (*iterator_str)++;
      } else {
        **iterator_str = ' ', (*iterator_str)++;
      }
    }
  }

  s21_postfix_processor_double(buffer, size, iterator_str, fd);
}

void s21_handle_double_default(char** iterator_str, va_list* args,
                               flag_data fd) {
  double double_arg = va_arg(*args, double);
  fd.precision = fd.precision_set == 1 ? fd.precision : 6;

  if (double_arg < 0) {
    fd.plus_flag = 0;
    fd.space_flag = 0;
  }
  char buffer[4096] = {0};
  s21_double_to_string(double_arg, buffer, fd.precision, fd.cell_flag);
  int size = s21_strlen(buffer);

  if (fd.minus_flag == 1) {
    fd.zero_flag = 0;
  }

  char filler = fd.zero_flag == 1 ? '0' : ' ';

  if (fd.zero_flag == 1) {
    if ((fd.plus_flag || fd.space_flag) && double_arg >= 0) {
      if (fd.plus_flag == 1) {
        **iterator_str = '+', (*iterator_str)++;
      } else {
        **iterator_str = ' ', (*iterator_str)++;
      }
    }
  }

  for (int i = 0; i < fd.width - size - (fd.plus_flag || fd.space_flag) &&
                  fd.minus_flag == 0;
       i++) {
    **iterator_str = filler, (*iterator_str)++;
  }

  if (fd.zero_flag == 0) {
    if ((fd.plus_flag || fd.space_flag) && double_arg >= 0) {
      if (fd.plus_flag == 1) {
        **iterator_str = '+', (*iterator_str)++;
      } else {
        **iterator_str = ' ', (*iterator_str)++;
      }
    }
  }

  s21_postfix_processor_double(buffer, size, iterator_str, fd);
}

void s21_postfix_processor_double(const char* buffer, int size,
                                  char** iterator_str, flag_data fd) {
  for (int i = 0; i < size; i++) {
    if (buffer[i] != '\0') {
      **iterator_str = buffer[i], (*iterator_str)++;
    }
  }

  for (int i = 0; i < fd.width - size - (fd.plus_flag || fd.space_flag) &&
                  fd.minus_flag == 1;
       i++) {
    **iterator_str = ' ', (*iterator_str)++;
  }
}

void s21_mantissa_proc_long(long double* double_arg, int* mantissa,
                            int negative, char* buffer, flag_data fd,
                            int upper_case) {
  if (*double_arg >= 10) {
    while (*double_arg >= 10) {
      (*double_arg) /= 10;
      (*mantissa)++;
    }
    (*double_arg) = negative == 1 ? -1 * (*double_arg) : (*double_arg);

    s21_double_to_string(*double_arg, buffer, fd.precision, fd.cell_flag);
    int left = (*mantissa) / 10 + '0';
    int right = (*mantissa) % 10 + '0';
    buffer[s21_strlen(buffer)] = upper_case == 1 ? 'E' : 'e';
    buffer[s21_strlen(buffer)] = '+';
    buffer[s21_strlen(buffer)] = (char)left;
    buffer[s21_strlen(buffer)] = (char)right;
  } else if (*double_arg < 1.0) {
    while (*double_arg < 1.0) {
      (*double_arg) *= 10;
      (*mantissa)++;
    }
    (*double_arg) = negative == 1 ? (*double_arg) * -1 : (*double_arg);

    s21_double_to_string(*double_arg, buffer, fd.precision, fd.cell_flag);

    int left = (*mantissa) / 10 + '0';
    int right = (*mantissa) % 10 + '0';
    buffer[s21_strlen(buffer)] = upper_case == 1 ? 'E' : 'e';
    buffer[s21_strlen(buffer)] = '-';
    buffer[s21_strlen(buffer)] = (char)left;
    buffer[s21_strlen(buffer)] = (char)right;

  } else {
    (*double_arg) = negative == 1 ? (*double_arg) * -1 : (*double_arg);
    s21_double_to_string(*double_arg, buffer, fd.precision, fd.cell_flag);

    char left = '0';
    char right = '0';
    buffer[s21_strlen(buffer)] = upper_case == 1 ? 'E' : 'e';
    buffer[s21_strlen(buffer)] = '+';
    buffer[s21_strlen(buffer)] = left;
    buffer[s21_strlen(buffer)] = right;
  }
}

void s21_mantissa_proc(double* double_arg, int* mantissa, int negative,
                       char* buffer, flag_data fd, int upper_case) {
  if (*double_arg >= 10) {
    while (*double_arg >= 10) {
      (*double_arg) /= 10;
      (*mantissa)++;
    }
    (*double_arg) = negative == 1 ? -1 * (*double_arg) : (*double_arg);

    s21_double_to_string(*double_arg, buffer, fd.precision, fd.cell_flag);

    int left = (*mantissa) / 10 + '0';
    int right = (*mantissa) % 10 + '0';
    buffer[s21_strlen(buffer)] = upper_case == 1 ? 'E' : 'e';
    buffer[s21_strlen(buffer)] = '+';
    buffer[s21_strlen(buffer)] = (char)left;
    buffer[s21_strlen(buffer)] = (char)right;
  } else if (*double_arg < 1.0) {
    while (*double_arg < 1.0) {
      (*double_arg) *= 10;
      (*mantissa)++;
    }
    (*double_arg) = negative == 1 ? (*double_arg) * -1 : (*double_arg);

    s21_double_to_string(*double_arg, buffer, fd.precision, fd.cell_flag);

    int left = (*mantissa) / 10 + '0';
    int right = (*mantissa) % 10 + '0';
    buffer[s21_strlen(buffer)] = upper_case == 1 ? 'E' : 'e';
    buffer[s21_strlen(buffer)] = '-';
    buffer[s21_strlen(buffer)] = (char)left;
    buffer[s21_strlen(buffer)] = (char)right;

  } else {
    (*double_arg) = negative == 1 ? (*double_arg) * -1 : (*double_arg);
    s21_double_to_string(*double_arg, buffer, fd.precision, fd.cell_flag);
    char left = '0';
    char right = '0';
    buffer[s21_strlen(buffer)] = upper_case == 1 ? 'E' : 'e';
    buffer[s21_strlen(buffer)] = '+';
    buffer[s21_strlen(buffer)] = left;
    buffer[s21_strlen(buffer)] = right;
  }
}

void s21_handle_e(char** iterator_str, va_list* args, flag_data fd,
                  int upper_case) {
  if (fd.L_prefix == 1) {
    s21_handle_e_long(iterator_str, args, fd, upper_case);
  } else {
    s21_handle_e_default(iterator_str, args, fd, upper_case);
  }
}

void s21_handle_e_long(char** iterator_str, va_list* args, flag_data fd,
                       int upper_case) {
  long double double_arg = va_arg(*args, long double);
  fd.precision = fd.precision_set == 1 ? fd.precision : 6;

  if (double_arg < 0) {
    fd.plus_flag = 0;
    fd.space_flag = 0;
  }

  int negative = double_arg < 0 ? 1 : 0;
  double_arg = negative == 1 ? double_arg * -1 : double_arg;

  int mantissa = 0;
  char buffer[4096] = {0};
  s21_mantissa_proc_long(&double_arg, &mantissa, negative, buffer, fd,
                         upper_case);

  int size = s21_strlen(buffer);

  if (fd.minus_flag == 1) {
    fd.zero_flag = 0;
  }

  char filler = fd.zero_flag == 1 ? '0' : ' ';

  if (fd.zero_flag == 1) {
    if ((fd.plus_flag || fd.space_flag) && double_arg >= 0) {
      if (fd.plus_flag == 1) {
        **iterator_str = '+', (*iterator_str)++;
      } else {
        **iterator_str = ' ', (*iterator_str)++;
      }
    }
  }

  for (int i = 0; i < fd.width - size - (fd.plus_flag || fd.space_flag) &&
                  fd.minus_flag == 0;
       i++) {
    **iterator_str = filler, (*iterator_str)++;
  }

  postfix_procc_e(fd, double_arg, iterator_str, size, buffer);
}

void s21_handle_e_default(char** iterator_str, va_list* args, flag_data fd,
                          int upper_case) {
  double double_arg = va_arg(*args, double);
  fd.precision = fd.precision_set == 1 ? fd.precision : 6;

  if (double_arg < 0) {
    fd.plus_flag = 0;
    fd.space_flag = 0;
  }

  int negative = double_arg < 0 ? 1 : 0;
  double_arg = negative == 1 ? double_arg * -1 : double_arg;

  int mantissa = 0;
  char buffer[4096] = {0};
  s21_mantissa_proc(&double_arg, &mantissa, negative, buffer, fd, upper_case);

  int size = s21_strlen(buffer);

  if (fd.minus_flag == 1) {
    fd.zero_flag = 0;
  }

  char filler = fd.zero_flag == 1 ? '0' : ' ';

  if (fd.zero_flag == 1) {
    if ((fd.plus_flag || fd.space_flag) && double_arg >= 0) {
      if (fd.plus_flag == 1) {
        **iterator_str = '+', (*iterator_str)++;
      } else {
        **iterator_str = ' ', (*iterator_str)++;
      }
    }
  }

  for (int i = 0; i < fd.width - size - (fd.plus_flag || fd.space_flag) &&
                  fd.minus_flag == 0;
       i++) {
    **iterator_str = filler, (*iterator_str)++;
  }

  postfix_procc_e(fd, double_arg, iterator_str, size, buffer);
}

void postfix_procc_e(flag_data fd, long double double_arg, char** iterator_str,
                     int size, const char* buffer) {
  if (fd.zero_flag == 0) {
    if ((fd.plus_flag || fd.space_flag) && double_arg >= 0) {
      if (fd.plus_flag == 1) {
        **iterator_str = '+', (*iterator_str)++;
      } else {
        **iterator_str = ' ', (*iterator_str)++;
      }
    }
  }

  for (int i = 0; i < size; i++) {
    if (buffer[i] != '\0') {
      **iterator_str = buffer[i], (*iterator_str)++;
    }
  }

  for (int i = 0; i < fd.width - size - (fd.plus_flag || fd.space_flag) &&
                  fd.minus_flag == 1;
       i++) {
    **iterator_str = ' ', (*iterator_str)++;
  }
}

int s21_count_significant_figures(double num, int precision, int mantissa,
                                  int cell_flag) {
  num = fabs(num);
  int final_sig = 0;
  int zero_sig = 0;
  int int_num = num;
  double fragment = num - int_num;

  while ((int_num != 0 && final_sig < precision)) {
    int_num /= 10;
    final_sig++;
  }

  if (mantissa) {
    precision--;
    final_sig = 0;
  } else {
    precision -= final_sig;
    final_sig = 0;
  }
  int exit = 0;
  while ((final_sig < precision && zero_sig < precision) && exit == 0) {
    fragment *= 10;
    int elem = fragment;

    if (elem == 0 && cell_flag == 0) {
      zero_sig++;
    } else {
      if (!(final_sig + zero_sig >= precision)) {
        final_sig += zero_sig;
        zero_sig = 0;
        final_sig++;
      } else {
        exit = 1;
      }
    }
    fragment -= elem;
  }

  return final_sig;
}

void s21_handle_g(char** iterator_str, va_list* args, flag_data fd,
                  int upper_case) {
  va_list args_copy;
  va_copy(args_copy, *args);

  double double_arg = va_arg(args_copy, double);

  fd.precision = fd.precision_set == 1 ? fd.precision : 6;
  fd.precision_set = 1;
  int new_precion = 0;

  if (pow(10, -4) <= fabs(double_arg) &&
      fabs(double_arg) < pow(10, fd.precision)) {
    new_precion = s21_count_significant_figures(double_arg, fd.precision, 0,
                                                fd.cell_flag);
    fd.precision = fd.precision > new_precion ? new_precion : fd.precision;
    s21_handle_double(iterator_str, args, fd);
  } else {
    new_precion = s21_count_significant_figures(double_arg, fd.precision, 1,
                                                fd.cell_flag);
    fd.precision = fd.precision > new_precion ? new_precion : fd.precision;
    s21_handle_e(iterator_str, args, fd, upper_case);
  }

  va_end(args_copy);
}

void to_hex_string(unsigned number, char* hex_str, int upper_case) {
  const char* hex_digits =
      upper_case == 1 ? "0123456789ABCDEF" : "0123456789abcdef";
  char buffer[9];

  if (number == 0) {
    hex_str[0] = '0';
    hex_str[1] = '\0';
  } else {
    int index = 7;
    buffer[8] = '\0';

    while (number > 0 && index >= 0) {
      buffer[index--] = hex_digits[number % 16];
      number /= 16;
    }

    int start_index = index + 1;
    for (int i = 0; i < 8 - start_index; i++) {
      hex_str[i] = buffer[start_index + i];
    }
    hex_str[8 - start_index] = '\0';
  }
}

void to_hex_string_long(unsigned long long number, char* hex_str,
                        int upper_case) {
  const char* hex_digits = upper_case ? "0123456789ABCDEF" : "0123456789abcdef";

  char buffer[17] = {0};
  int index = 15;

  if (number == 0) {
    buffer[index--] = '0';
  } else {
    while (number > 0 && index >= 0) {
      buffer[index--] = hex_digits[number % 16];
      number /= 16;
    }
  }

  int start_index = index + 1;
  for (int i = 0; i < 16 - start_index; i++) {
    hex_str[i] = buffer[start_index + i];
  }
  hex_str[16 - start_index] = '\0';
}

void s21_handle_x(char** iterator_str, va_list* args, flag_data fd,
                  int upper_case) {
  if (fd.l_prefix == 1) {
    s21_handle_x_long(iterator_str, args, fd, upper_case);
  } else if (fd.h_prefix) {
    s21_handle_x_short(iterator_str, args, fd, upper_case);
  } else {
    s21_handle_x_default(iterator_str, args, fd, upper_case);
  }
}

void s21_handle_x_long(char** iterator_str, va_list* args, flag_data fd,
                       int upper_case) {
  unsigned long long hex = va_arg(*args, unsigned long long);
  char buffer[1024] = {0};

  to_hex_string_long(hex, buffer, upper_case);

  int length_arg = s21_strlen(buffer);
  if (fd.cell_flag == 1 && fd.precision_set == 0) length_arg += 2;

  if (fd.minus_flag == 1 || fd.precision_set == 1) {
  } else if (fd.zero_flag == 1 && fd.precision_set == 0) {
    fd.precision = fd.width;
  }

  int size = fd.precision > length_arg ? fd.precision : length_arg;

  if (fd.minus_flag == 0) {
    for (int i = 0;
         i < fd.width - size - (fd.precision_set == 1 && fd.cell_flag == 1) * 2;
         i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }

  if (fd.cell_flag == 1) {
    **iterator_str = '0', (*iterator_str)++;
    **iterator_str = upper_case == 1 ? 'X' : 'x', (*iterator_str)++;
  }

  for (int i = 0; i < fd.precision - length_arg; i++) {
    **iterator_str = '0', (*iterator_str)++;
  }

  for (int i = 0; i < (int)s21_strlen(buffer); i++) {
    **iterator_str = buffer[i], (*iterator_str)++;
  }

  if (fd.minus_flag == 1) {
    for (int i = 0;
         i < fd.width - size - (fd.precision_set == 1 && fd.cell_flag == 1) * 2;
         i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }
}

void s21_handle_x_short(char** iterator_str, va_list* args, flag_data fd,
                        int upper_case) {
  unsigned short hex = va_arg(*args, unsigned);
  char buffer[1024] = {0};

  to_hex_string(hex, buffer, upper_case);
  int length_arg = s21_strlen(buffer);
  if (fd.cell_flag == 1 && fd.precision_set == 0) length_arg += 2;

  if (fd.minus_flag == 1 || fd.precision_set == 1) {
  } else if (fd.zero_flag == 1 && fd.precision_set == 0) {
    fd.precision = fd.width;
  }

  int size = fd.precision > length_arg ? fd.precision : length_arg;

  if (fd.minus_flag == 0) {
    for (int i = 0;
         i < fd.width - size - (fd.precision_set == 1 && fd.cell_flag == 1) * 2;
         i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }

  if (fd.cell_flag == 1) {
    **iterator_str = '0', (*iterator_str)++;
    **iterator_str = upper_case == 1 ? 'X' : 'x', (*iterator_str)++;
  }

  for (int i = 0; i < fd.precision - length_arg; i++) {
    **iterator_str = '0', (*iterator_str)++;
  }

  for (int i = 0; i < (int)s21_strlen(buffer); i++) {
    **iterator_str = buffer[i], (*iterator_str)++;
  }

  if (fd.minus_flag == 1) {
    for (int i = 0;
         i < fd.width - size - (fd.precision_set == 1 && fd.cell_flag == 1) * 2;
         i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }
}

void s21_handle_x_default(char** iterator_str, va_list* args, flag_data fd,
                          int upper_case) {
  unsigned hex = va_arg(*args, unsigned);
  char buffer[1024] = {0};

  to_hex_string_long(hex, buffer, upper_case);
  int length_arg = s21_strlen(buffer);
  if (fd.cell_flag == 1 && fd.precision_set == 0) length_arg += 2;

  if (fd.minus_flag == 1 || fd.precision_set == 1) {
  } else if (fd.zero_flag == 1 && fd.precision_set == 0) {
    fd.precision = fd.width;
  }

  int size = fd.precision > length_arg ? fd.precision : length_arg;

  if (fd.minus_flag == 0) {
    for (int i = 0;
         i < fd.width - size - (fd.precision_set == 1 && fd.cell_flag == 1) * 2;
         i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }

  if (fd.cell_flag == 1) {
    **iterator_str = '0', (*iterator_str)++;
    **iterator_str = upper_case == 1 ? 'X' : 'x', (*iterator_str)++;
  }

  for (int i = 0; i < fd.precision - length_arg; i++) {
    **iterator_str = '0', (*iterator_str)++;
  }

  for (int i = 0; i < (int)s21_strlen(buffer); i++) {
    **iterator_str = buffer[i], (*iterator_str)++;
  }

  if (fd.minus_flag == 1) {
    for (int i = 0;
         i < fd.width - size - (fd.precision_set == 1 && fd.cell_flag == 1) * 2;
         i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }
}

void to_oct_string(unsigned int number, char* oct_str) {
  const char* oct_digits = "01234567";
  char buffer[12];

  buffer[11] = '\0';

  if (number == 0) {
    oct_str[0] = '0';
    oct_str[1] = '\0';

  } else {
    int index = 10;
    while (number > 0) {
      buffer[index--] = oct_digits[number % 8];
      number /= 8;
    }

    int length = 11 - index - 1;
    for (int i = 0; i < length; i++) {
      oct_str[i] = buffer[index + 1 + i];
    }
    oct_str[length] = '\0';
  }
}

void to_oct_string_unsigned_short(unsigned short number, char* oct_str) {
  const char* oct_digits = "01234567";
  char buffer[6];

  buffer[5] = '\0';

  if (number == 0) {
    oct_str[0] = '0';
    oct_str[1] = '\0';

  } else {
    int index = 5;
    while (number > 0) {
      buffer[--index] = oct_digits[number % 8];
      number /= 8;
    }

    int length = 5 - index;
    for (int i = 0; i < length; i++) {
      oct_str[i] = buffer[index + i];
    }
    oct_str[length] = '\0';
  }
}

void to_oct_string_unsigned_long_long(unsigned long long number,
                                      char* oct_str) {
  const char* oct_digits = "01234567";
  char buffer[22];

  buffer[21] = '\0';

  if (number == 0) {
    oct_str[0] = '0';
    oct_str[1] = '\0';
  } else {
    int index = 21;
    while (number > 0) {
      buffer[--index] = oct_digits[number % 8];
      number /= 8;
    }

    int length = 21 - index;
    for (int i = 0; i < length; i++) {
      oct_str[i] = buffer[index + i];
    }
    oct_str[length] = '\0';
  }
}

void s21_handle_o(char** iterator_str, va_list* args, flag_data fd) {
  if (fd.l_prefix == 1) {
    s21_handle_o_long(iterator_str, args, fd);
  } else if (fd.h_prefix == 1) {
    s21_handle_o_short(iterator_str, args, fd);
  } else {
    s21_handle_o_default(iterator_str, args, fd);
  }
}

void s21_handle_o_default(char** iterator_str, va_list* args, flag_data fd) {
  unsigned hex = va_arg(*args, unsigned);
  char buffer[1024] = {0};
  to_oct_string(hex, buffer);
  int length_arg = s21_strlen(buffer);
  if (fd.cell_flag == 1) length_arg++;

  if (fd.minus_flag == 1 || fd.precision_set == 1) {
  } else if (fd.zero_flag == 1 && fd.precision_set == 0) {
    fd.precision = fd.width;
  }

  int size = fd.precision > length_arg ? fd.precision : length_arg;

  if (fd.minus_flag == 0) {
    for (int i = 0; i < fd.width - size; i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }

  if (fd.cell_flag == 1) {
    **iterator_str = '0', (*iterator_str)++;
  }

  for (int i = 0; i < fd.precision - length_arg; i++) {
    **iterator_str = '0', (*iterator_str)++;
  }

  for (int i = 0; i < (int)s21_strlen(buffer); i++) {
    **iterator_str = buffer[i], (*iterator_str)++;
  }

  if (fd.minus_flag == 1) {
    for (int i = 0; i < fd.width - size; i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }
}

void s21_handle_o_long(char** iterator_str, va_list* args, flag_data fd) {
  unsigned long long hex = va_arg(*args, unsigned long long);
  char buffer[1024] = {0};
  to_oct_string_unsigned_long_long(hex, buffer);
  int length_arg = s21_strlen(buffer);
  if (fd.cell_flag == 1) length_arg++;

  if (fd.minus_flag == 1 || fd.precision_set == 1) {
  } else if (fd.zero_flag == 1 && fd.precision_set == 0) {
    fd.precision = fd.width;
  }

  int size = fd.precision > length_arg ? fd.precision : length_arg;

  if (fd.minus_flag == 0) {
    for (int i = 0; i < fd.width - size; i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }

  if (fd.cell_flag == 1) {
    **iterator_str = '0', (*iterator_str)++;
  }

  for (int i = 0; i < fd.precision - length_arg; i++) {
    **iterator_str = '0', (*iterator_str)++;
  }

  for (int i = 0; i < (int)s21_strlen(buffer); i++) {
    **iterator_str = buffer[i], (*iterator_str)++;
  }

  if (fd.minus_flag == 1) {
    for (int i = 0; i < fd.width - size; i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }
}

void s21_handle_o_short(char** iterator_str, va_list* args, flag_data fd) {
  unsigned short hex = va_arg(*args, unsigned);
  char buffer[1024] = {0};
  to_oct_string_unsigned_short(hex, buffer);
  int length_arg = s21_strlen(buffer);
  if (fd.cell_flag == 1) length_arg++;

  if (fd.minus_flag == 1 || fd.precision_set == 1) {
  } else if (fd.zero_flag == 1 && fd.precision_set == 0) {
    fd.precision = fd.width;
  }

  int size = fd.precision > length_arg ? fd.precision : length_arg;

  if (fd.minus_flag == 0) {
    for (int i = 0; i < fd.width - size; i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }

  if (fd.cell_flag == 1) {
    **iterator_str = '0', (*iterator_str)++;
  }

  for (int i = 0; i < fd.precision - length_arg; i++) {
    **iterator_str = '0', (*iterator_str)++;
  }

  for (int i = 0; i < (int)s21_strlen(buffer); i++) {
    **iterator_str = buffer[i], (*iterator_str)++;
  }

  if (fd.minus_flag == 1) {
    for (int i = 0; i < fd.width - size; i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }
}

void s21_handle_p(char** iterator_str, va_list* args, flag_data fd) {
  uintptr_t ptr = (uintptr_t)va_arg(*args, void*);

  char buffer[1024] = {0};

  to_hex_string_long(ptr, buffer, 0);

  int length_arg = s21_strlen(buffer);
  if (fd.precision_set == 0) length_arg += 2;

  if (fd.minus_flag == 1 || fd.precision_set == 1) {
  } else if (fd.zero_flag == 1 && fd.precision_set == 0) {
    fd.precision = fd.width;
  }

  int size = fd.precision > length_arg ? fd.precision : length_arg;

  if (fd.minus_flag == 0) {
    for (int i = 0; i < fd.width - size - (fd.precision_set == 1) * 2 -
                            (fd.plus_flag || fd.space_flag);
         i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }

  if ((fd.plus_flag || fd.space_flag)) {
    if (fd.plus_flag == 1) {
      **iterator_str = '+', (*iterator_str)++;
    } else {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }

  **iterator_str = '0', (*iterator_str)++;
  **iterator_str = 'x', (*iterator_str)++;

  for (int i = 0; i < fd.precision - length_arg; i++)
    **iterator_str = '0', (*iterator_str)++;

  for (int i = 0; i < (int)s21_strlen(buffer); i++)
    **iterator_str = buffer[i], (*iterator_str)++;

  if (fd.minus_flag == 1) {
    for (int i = 0; i < fd.width - size - (fd.precision_set == 1) * 2 -
                            (fd.plus_flag || fd.space_flag);
         i++) {
      **iterator_str = ' ', (*iterator_str)++;
    }
  }
}

void s21_parse_flag(int* ch, const char** iterator_format, flag_data* fd) {
  while ((*ch < '1' || *ch > '9') && *ch != 'd' && *ch != 'c' && *ch != 's' &&
         *ch != 'f' && *ch != 'e' && *ch != 'E' && *ch != 'g' && *ch != 'G' &&
         *ch != 'x' && *ch != 'X' && *ch != 'u' && *ch != 'o' && *ch != 'p' &&
         *ch != 'h' && *ch != 'l' && *ch != 'L' && *ch != '%' && *ch != '.' &&
         *ch != '*') {
    switch (*ch) {
      case '-':
        fd->minus_flag = 1;
        break;
      case '+':
        fd->plus_flag = 1;
        fd->space_flag = 0;
        break;
      case ' ':
        fd->space_flag = fd->plus_flag == 1 ? 0 : 1;
        break;
      case '0':
        fd->zero_flag = 1;
        break;
      case '#':
        fd->cell_flag = 1;
        break;
      default:
        break;
    }
    *ch = (char)(**iterator_format), (*iterator_format)++;
  }
}

void s21_swicther_spec(int* ch, char** iterator_str, va_list* args,
                       flag_data fd, const char** iterator_format) {
  switch (*ch) {
    case '%':
      s21_handle_percent(iterator_str);
      break;
    case 'c':
      s21_handle_character(iterator_str, args, fd);
      break;
    case 's':
      s21_handle_string(iterator_str, args, fd);
      break;
    case 'd':
      s21_handle_digital(iterator_str, args, fd);
      break;
    case 'u':
      s21_handle_unsigned(iterator_str, args, fd);
      break;
    case 'f':
      s21_handle_double(iterator_str, args, fd);
      break;
    case 'e':
      s21_handle_e(iterator_str, args, fd, 0);
      break;
    case 'E':
      s21_handle_e(iterator_str, args, fd, 1);
      break;
    case 'g':
      s21_handle_g(iterator_str, args, fd, 0);
      break;
    case 'G':
      s21_handle_g(iterator_str, args, fd, 1);
      break;
    case 'x':
      s21_handle_x(iterator_str, args, fd, 0);
      break;
    case 'X':
      s21_handle_x(iterator_str, args, fd, 1);
      break;
    case 'o':
      s21_handle_o(iterator_str, args, fd);
      break;
    case 'p':
      s21_handle_p(iterator_str, args, fd);
      break;
    default:
      (*iterator_format)++;
      break;
  }
}

void s21_sprintf_spec_processor(int* ch, char** iterator_str,
                                const char** iterator_format, va_list* args) {
  flag_data fd = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  s21_parse_flag(ch, iterator_format, &fd);

  if (*ch == '*') {
    fd.width_set = 1;
    fd.width = va_arg(*args, int);
    *ch = (char)(**iterator_format), (*iterator_format)++;
  } else {
    for (int j = 0; *ch >= '0' && *ch <= '9';
         *ch = (char)(**iterator_format), (*iterator_format)++, j++) {
      fd.width_set = 1;
      fd.width = (fd.width * 10) + (*ch - '0');
    }
  }

  if (*ch == '.') {
    *ch = (char)(**iterator_format), (*iterator_format)++;
    if (*ch == '*') {
      fd.precision_set = 1;
      fd.precision = va_arg(*args, int);
      *ch = (char)(**iterator_format), (*iterator_format)++;
    } else {
      for (int j = 0; *ch >= '0' && *ch <= '9';
           *ch = (char)(**iterator_format), (*iterator_format)++, j++) {
        fd.precision_set = 1;
        fd.precision = (fd.precision * 10) + (*ch - '0');
      }
    }
  }

  while (*ch == 'h' || *ch == 'L' || *ch == 'l') {
    switch (*ch) {
      case 'h':
        fd.h_prefix = 1;
        break;
      case 'L':
        fd.L_prefix = 1;
        break;
      case 'l':
        fd.l_prefix = 1;
        break;
      default:
        break;
    }
    *ch = (char)(**iterator_format), (*iterator_format)++;
  }

  s21_swicther_spec(ch, iterator_str, args, fd, iterator_format);
}

int s21_sprintf(char* str, const char* format, ...) {
  va_list args;
  va_start(args, format);
  int ch, spec_processing = 0;
  const char* iterator_format = format;
  char* iterator_str = str;

  while ((ch = *iterator_format++) != '\0') {
    if (ch == '%' && spec_processing == 0) {
      spec_processing = 1;
    } else if (spec_processing == 1) {
      s21_sprintf_spec_processor(&ch, &iterator_str, &iterator_format, &args);
      spec_processing = 0;
    } else {
      *iterator_str++ = ch;
    }
  }

  va_end(args);

  *iterator_str = '\0';

  return (int)s21_strlen(str);
}