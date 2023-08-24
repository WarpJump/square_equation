#include "colors.h"
#include "core.h"
#include "test.h"

/*!
    \file
    \brief File with function needed to parse command line flags
*/

ErrorCodes ParseString(char *str, char first_symbol_to_find,
                       char second_symbol_to_find, char **first_char,
                       char **second_char) {
  AssertError(str && first_char && second_char, ErrorCodes::NullPointer);

  char *current_char = str;
  *first_char = nullptr;
  *second_char = nullptr;

  while (*current_char != '\0') {
    if (*current_char == first_symbol_to_find) {
      if (*first_char == nullptr) {
        *first_char = current_char;
      }

    } else if (*current_char == second_symbol_to_find) {
      if (*second_char == nullptr) {
        *second_char = current_char;
      }
    }
    ++current_char;
  }

  return ErrorCodes::Ok;
}

char *CreateString(size_t valuable_size) {
  char *new_string = reinterpret_cast<char *>(
      calloc(valuable_size + 1, sizeof(char)));
  new_string[valuable_size] = '\0';
  return new_string;
}

void DestroyString(char *old_string) { free(old_string); }

void CopyFirstCharsString(char *target, char *source, size_t number) {
  memcpy(target, source, number);
}

ErrorCodes ParseOneFlag(CoeffsAndRoots *equation, char *flag) {
  char *mi_sign = nullptr;
  char *eq_sign = nullptr;
  ErrorCodes is_parse_error = ParseString(flag, '-', '=', &mi_sign, &eq_sign);

  if (is_parse_error != ErrorCodes::Ok) {
    return is_parse_error;
  }

  if ((mi_sign == nullptr) || (eq_sign == nullptr)) {
    printf(RedText("Error"));

    printf("Wrong symbols in flag arguments\n");
    return ErrorCodes::Ok;
  }

  const int kSizeOfToken = eq_sign - mi_sign - 1;
  char *token = CreateString(kSizeOfToken);
  CopyFirstCharsString(token, mi_sign + 1, kSizeOfToken);

  double value = strtold(eq_sign + 1, NULL);

  if ((*token) == 'a') {
    equation->a_coef = value;
  } else if ((*token) == 'b') {
    equation->b_coef = value;
  } else if ((*token) == 'c') {
    equation->c_coef = value;
  }

  DestroyString(token);
  return ErrorCodes::Ok;
}

ErrorCodes ParseCommandLine(CoeffsAndRoots *equation, int argc, char **argv) {
  AssertError(equation != nullptr, ErrorCodes::NullPointer);
  AssertError(argv != nullptr, ErrorCodes::NullPointer);

  equation->a_coef = 0;
  equation->b_coef = 0;
  equation->c_coef = 0;

  for (int i = 1; i < argc; ++i) {
    ParseOneFlag(equation, argv[i]);
  }
  return ErrorCodes::Ok;
}
