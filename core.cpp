/*!
\file
\brief File with functions definition
*/

#include "core.h"

#include "colors.h"

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
      printf(RedText("Error!"));
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
    printf(RedText("Error: "));

    printf(
        "the only root does not match: correct ans is %lf, but programm "
        "returned %lf\n",
        ans_1, test->root_1);
    return false;
  }
  printf(GreenText("test OK:") " correct ans is %lf, program returned %lf\n", ans_1,
         test->root_1);
  return true;
}

bool CompareTwoRoots(CoeffsAndRoots *test, double ans_1, double ans_2) {
  bool const kCorrect = ((CompareDoubles(ans_1, test->root_1) &&
                          CompareDoubles(ans_2, test->root_2)) ||
                         (CompareDoubles(ans_2, test->root_1) &&
                          CompareDoubles(ans_1, test->root_2)));
  if (!kCorrect) {
    printf(RedText("Error: "));
    printf(
        "roots does not match: ans is %.3lf %.3lf, but program returned %.3lf "
        "%.3lf\n",
        ans_1, ans_2, test->root_1, test->root_2);
    return false;
  }
  printf(
      GreenText("test OK:") " roots are %.3lf and %.3lf, program returned %.3lf and %.3lf\n",
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
      fprintf(stderr, GreenText("test OK:") " infinite roots exist\n");
      correct = true;
      break;

    case Zero:
      fprintf(stderr, GreenText("test OK:") " no roots exist\n");
      correct = true;
      break;

    case NotARoot:
    default:
      fprintf(stderr, GreenText("test OK:")"\n");
      return true;
  }
  return correct;
}

void PrintErrorCode(ErrorCodes err_code) {
  if (err_code == ErrorCodes::Ok) {
    return;
  }

  fprintf(stderr, RedText("Error! Function call incorrect:\n \033[0m"));
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
      break;

    case BadInput:
      fprintf(stderr, "Sorry but you entered not a decimal or float number.\n");
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

  FILE *data_file = fopen("test/data.txt", "re");

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
