/*!
\file
\brief File with functions definition
*/

#include "core.h"

void Initialize(CoeffsAndRoots *structure) {
  structure->a_coef = NAN;
  structure->b_coef = NAN;
  structure->c_coef = NAN;
  structure->num_of_roots = NotARoot;
  structure->root_1 = NAN;
  structure->root_2 = NAN;
}

void Destroy(CoeffsAndRoots *structure) {
  structure->a_coef = NAN;
  structure->b_coef = NAN;
  structure->c_coef = NAN;
  structure->num_of_roots = NotARoot;
  structure->root_1 = NAN;
  structure->root_2 = NAN;
}

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
  char *new_string =
      reinterpret_cast<char *>(malloc(valuable_size + 1));  // TODO use calloc,
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
    printf("Wrong symbols in flag arguments\n");
    return ErrorCodes::Ok;
  }

  const int kSizeOfToken = eq_sign - mi_sign - 1;
  char *token = CreateString(kSizeOfToken);
  CopyFirstCharsString(token, mi_sign + 1, kSizeOfToken);

  static const int kBase = 10;
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

ErrorCodes ScanCoeffs(CoeffsAndRoots *equation) {
  AssertError(equation != nullptr, ErrorCodes::NullPointer);
  scanf("%lf %lf %lf", &(equation->a_coef), &(equation->b_coef),
        &(equation->c_coef));

  return ErrorCodes::Ok;
}

ErrorCodes ScanData(FILE *data_file, CoeffsAndRoots *test, int *num_of_roots,
                    double *ans_1, double *ans_2) {
  AssertError(test, ErrorCodes::NullPointer);
  AssertError(ans_1 && ans_2, ErrorCodes::NullPointer);
  AssertError(ans_1 != ans_2, ErrorCodes::SamePointers);

  fscanf(data_file, "%lf %lf %lf %d %lf %lf", &(test->a_coef), &(test->b_coef),
         &(test->c_coef), num_of_roots, ans_1, ans_2);

  return ErrorCodes::Ok;
}

void PrintRoots(CoeffsAndRoots *equation) {
  switch (equation->num_of_roots) {
    case One:
      printf("one root exist: %3.3lg \n", equation->root_1);
      break;

    case Two:
      printf("two roots exist: %3.3lg and %3.3lg \n", equation->root_1,
             equation->root_2);
      break;

    case Inf:
      printf("infinite roots exist\n");
      break;

    case Zero:
      printf("no roots exist\n");
      break;

    case NotARoot:
    default:
      printf("error\n");
      break;
  }
}

ErrorCodes SolveEquation(CoeffsAndRoots *equation) {
  AssertError(equation != nullptr, ErrorCodes::NullPointer);
  AssertError(!(isinf(equation->a_coef) || isinf(equation->b_coef) ||
                isinf(equation->c_coef)),
              ErrorCodes::InfiniteFloat);

  if (CompareDoubles(equation->a_coef, 0)) {
    return FindRootOfLinearEquation(equation);
  }
  return FindRootsOfSquareEquation(equation);
}

ErrorCodes FindRootOfLinearEquation(CoeffsAndRoots *equation) {
  AssertError(equation != nullptr, ErrorCodes::NullPointer);
  AssertError(!(isinf(equation->b_coef) || isinf(equation->c_coef)),
              ErrorCodes::InfiniteFloat);

  if (CompareDoubles(equation->b_coef, 0)) {
    equation->root_1 = NAN;
    if (CompareDoubles(equation->c_coef, 0)) {
      equation->num_of_roots = Inf;
      return ErrorCodes::Ok;
    }
    equation->num_of_roots = Zero;
    return ErrorCodes::Ok;
  }
  equation->root_1 = -equation->c_coef / equation->b_coef;

  equation->num_of_roots = One;

  return ErrorCodes::Ok;
}

ErrorCodes FindRootsOfSquareEquation(CoeffsAndRoots *equation) {
  AssertError(equation != nullptr, ErrorCodes::NullPointer);
  AssertError(!CompareDoubles(equation->a_coef, 0), ErrorCodes::ZeroDivision);
  AssertError(!(isinf(equation->a_coef) || isinf(equation->b_coef) ||
                isinf(equation->c_coef)),
              ErrorCodes::InfiniteFloat);

  double discr = equation->b_coef * equation->b_coef -
                 4 * equation->a_coef * equation->c_coef;

  if (CompareDoubles(discr, 0)) {
    equation->root_1 = -equation->b_coef / (2 * equation->a_coef);
    equation->num_of_roots = One;
    return ErrorCodes::Ok;
  }

  if (discr < 0) {
    equation->root_1 = equation->root_2 = NAN;
    equation->num_of_roots = Zero;
    return ErrorCodes::Ok;
  }

  double sqrt_discr = sqrt(discr);
  equation->root_1 = (-equation->b_coef + sqrt_discr) / (2 * equation->a_coef);
  equation->root_2 = (-equation->b_coef - sqrt_discr) / (2 * equation->a_coef);
  equation->num_of_roots = Two;

  return ErrorCodes::Ok;
}

bool CompareOneRoot(CoeffsAndRoots *test, double ans_1) {
  if (!CompareDoubles(ans_1, test->root_1)) {
    printf(
        "the only root does not match: correct ans is %lf, but programm "
        "returned %lf\n",
        ans_1, test->root_1);
    return false;
  }
  printf("test OK: correct ans is %lf, program returned %lf\n", ans_1,
         test->root_1);
  return true;
}

bool CompareTwoRoots(CoeffsAndRoots *test, double ans_1, double ans_2) {
  bool const kCorrect = ((CompareDoubles(ans_1, test->root_1) &&
                          CompareDoubles(ans_2, test->root_2)) ||
                         (CompareDoubles(ans_2, test->root_1) &&
                          CompareDoubles(ans_1, test->root_2)));
  if (!kCorrect) {
    printf(
        "roots does not match: ans is %.3lf %.3lf, but program returned %.3lf "
        "%.3lf\n",
        ans_1, ans_2, test->root_1, test->root_2);
    return false;
  }
  printf(
      "test OK: roots are %.3lf and %.3lf, program returned %.3lf and %.3lf\n",
      ans_1, ans_2, test->root_1, test->root_2);
  return true;
}

bool CompareRoots(CoeffsAndRoots *test, double ans_1, double ans_2) {
  bool correct = false;
  switch (test->num_of_roots) {
    case One:
      correct = CompareOneRoot(test, ans_1);
      break;
    case Two:
      correct = CompareTwoRoots(test, ans_1, ans_2);
      break;
    case Inf:
      fprintf(stderr, "test Ok: infinite roots exist\n");
      correct = true;
      break;
    case Zero:
      fprintf(stderr, "test Ok: no roots exist\n");
      correct = true;
      break;
    case NotARoot:
    default:
      fprintf(stderr, "test OK\n");
      return true;
  }
  return correct;
}

void PrintErrorCode(ErrorCodes err_code) {
  switch (err_code) {
    case NullPointer:
      fprintf(stderr, "User called function with null pointer\n");
      break;

    case SamePointers:
      fprintf(stderr,
              "User called function with two equal pointers as pointers to "
              "different variables\n");
      break;

    case InfiniteFloat:
      fprintf(stderr, "Function call with infinite float number\n");
      break;

    case ZeroDivision:
      fprintf(stderr, "Function call with zero as divider.\n");
      break;  // TODO more spaces!
    case Ok:
    default:
      fprintf(stderr, "lol cringe\n");
      break;
  }
}

void UserMode(int argc, char **argv) {
  CoeffsAndRoots equation{};

  ErrorCodes code = ErrorCodes::Ok;

  Initialize(&equation);

  if (argc == 1) {
    code = ScanCoeffs(&equation);
  } else {
    code = ParseCommandLine(&equation, argc, argv);
  }

  if (code != ErrorCodes::Ok) {
    PrintErrorCode(code);
  }

  code = SolveEquation(&equation);

  if (code != ErrorCodes::Ok) {
    PrintErrorCode(code);
  }

  PrintRoots(&equation);

  Destroy(&equation);
}

void TestMode() {
  double ans_1 = NAN;
  double ans_2 = NAN;
  int num_of_roots = 0;

  FILE *data_file = fopen("data.txt", "re");

  int num_of_tests = 0;
  int correct_tests = 0;

  fscanf(data_file, "%d", &num_of_tests);

  CoeffsAndRoots test{};

  ErrorCodes code = ErrorCodes::Ok;

  for (int i = 0; i < num_of_tests; ++i) {
    code = ScanData(data_file, &test, &num_of_roots, &ans_1, &ans_2);
    if (code != ErrorCodes::Ok) {
      PrintErrorCode(code);
    }
    code = SolveEquation(&test);
    if (code != ErrorCodes::Ok) {
      PrintErrorCode(code);
    }
    if (num_of_roots != test.num_of_roots) {
      fprintf(stderr, "number of roots does not match!\n");
      continue;
    }
    correct_tests += static_cast<int>(CompareRoots(&test, ans_1, ans_2));
  }
  fprintf(stderr, "tests correct %d / %d\n", correct_tests, num_of_tests);
  fclose(data_file);

  Destroy(&test);
}
