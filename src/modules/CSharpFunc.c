#include "../s21_string.h"
#include "../s21_types.h"

void *s21_to_upper(const char *str) {
  char *result = S21_NULL;
  if (str != S21_NULL) {
    s21_size_t len = s21_strlen(str);
    result = calloc(len + 1, sizeof(char));
    if (result) {
      for (s21_size_t i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
          result[i] = str[i] - ('a' - 'A');
        } else {
          result[i] = str[i];
        }
      }
      result[len] = '\0';
    }
  }
  return result;
}

void *s21_to_lower(const char *str) {
  char *result = S21_NULL;
  if (str != S21_NULL) {
    s21_size_t len = s21_strlen(str);
    result = calloc(len + 1, sizeof(char));
    if (result) {
      for (s21_size_t i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          result[i] = str[i] + ('a' - 'A');
        } else {
          result[i] = str[i];
        }
      }
      result[len] = '\0';
    }
  }
  return result;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = S21_NULL;

  if (str != S21_NULL) {
    s21_size_t str_len = s21_strlen(str);

    if (src == S21_NULL) {
      result = (char *)calloc(str_len + 1, sizeof(char));
      if (result != S21_NULL) {
        s21_strncpy(result, str, str_len + 1);
      }
    } else {
      s21_size_t src_len = s21_strlen(src);

      if (start_index <= src_len) {
        result = (char *)calloc(src_len + str_len + 1, sizeof(char));
        if (result != S21_NULL) {
          s21_strncpy(result, src, start_index);

          s21_strncpy(result + start_index, str, str_len);

          s21_strncpy(result + start_index + str_len, src + start_index,
                      src_len - start_index + 1);
        }
      }
    }
  }

  return result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = S21_NULL;

  if (src && trim_chars) {
    s21_size_t start = 0;

    s21_size_t src_len = 0;

    src_len = s21_strlen(src);

    while (start < src_len && s21_strrchr(trim_chars, src[start])) {
      start++;
    }

    if (start == src_len) {
      result = (char *)calloc(1, sizeof(char));
      if (result) {
        result[0] = '\0';
      }
    } else {
      s21_size_t end = 0;
      end = src_len - 1;
      s21_size_t new_length = 0;
      while (end > start && s21_strrchr(trim_chars, src[end])) {
        end--;
      }

      new_length = end - start + 1;

      result = (char *)calloc(new_length + 1, sizeof(char));
      if (result) {
        for (s21_size_t j = 0; j < new_length; j++) {
          result[j] = src[start + j];
        }
        result[new_length] = '\0';
      }
    }
  }

  return result;
}