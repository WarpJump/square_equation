/*!
\file
\brief File with functions definition
*/

#include "core.h"

void Initialize(CoeffsAndRoots* structure) {
  structure->a_coef = NAN;
  structure->b_coef = NAN;
  structure->c_coef = NAN;
  structure->num_of_roots = NotARoot;
  structure->root_1 = NAN;
  structure->root_2 = NAN;
}

void Destroy(CoeffsAndRoots* structure) {
  structure->a_coef = NAN;
  structure->b_coef = NAN;
  structure->c_coef = NAN;
  structure->num_of_roots = NotARoot;
  structure->root_1 = NAN;
  structure->root_2 = NAN;
}

void ScanCoeffs(CoeffsAndRoots* equation) {
  exception(equation != nullptr);
  scanf("%lf", &(equation->a_coef));
  scanf("%lf", &(equation->b_coef));
  scanf("%lf", &(equation->c_coef));
}

void ScanData(FILE* data_file, CoeffsAndRoots* test, int* num_of_roots,
              double* ans_1, double* ans_2) {
  exception(test != nullptr);
  exception(ans_1 != ans_2);
  exception((ans_1 != nullptr) && (ans_2 != nullptr));

  fscanf(data_file, "%lf%lf%lf", &(test->a_coef), &(test->b_coef),
         &(test->c_coef));
  fscanf(data_file, "%d%lf%lf", num_of_roots, ans_1, ans_2);
}

void PrintRoots(CoeffsAndRoots* equation) {
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

void SolveEquation(CoeffsAndRoots* equation) {
  exception(equation != nullptr);
  exception(!isnan(equation->a_coef) && !isnan(equation->b_coef) &&
            !isnan(equation->c_coef));
  exception(!isinf(equation->a_coef) && !isinf(equation->b_coef) &&
            !isinf(equation->c_coef));

  if (CompareDoubles(equation->a_coef, 0)) {
    FindRootOfLinearEquation(equation);
    return;
  }
  FindRootsOfSquareEquation(equation);
}

void FindRootOfLinearEquation(CoeffsAndRoots* equation) {
  exception(equation != nullptr);
  exception(!isnan(equation->b_coef) && !isnan(equation->c_coef));
  exception(!isinf(equation->b_coef) && !isinf(equation->c_coef));

  if (CompareDoubles(equation->b_coef, 0)) {
    equation->root_1 = NAN;
    if (CompareDoubles(equation->c_coef, 0)) {
      equation->num_of_roots = Inf;
      return;
    }
    equation->num_of_roots = Zero;
    return;
  }
  equation->root_1 = -equation->c_coef / equation->b_coef;
  equation->num_of_roots = One;
}

void FindRootsOfSquareEquation(CoeffsAndRoots* equation) {
  exception(equation != nullptr);
  exception(!CompareDoubles(equation->a_coef, 0));
  exception(!isnan(equation->a_coef) && !isnan(equation->b_coef) &&
            !isnan(equation->c_coef));
  exception(!isinf(equation->a_coef) && !isinf(equation->b_coef) &&
            !isinf(equation->c_coef));

  double const disc = equation->b_coef * equation->b_coef -
                      4 * equation->a_coef * equation->c_coef;
  if (CompareDoubles(disc, 0)) {
    equation->root_1 = -equation->b_coef / (2 * equation->a_coef);
    equation->num_of_roots = One;
    return;
  }
  if (disc < 0) {
    equation->root_1 = equation->root_2 = NAN;
    equation->num_of_roots = Zero;
    return;
  }
  double const sqrt_disc = sqrt(disc);
  equation->root_1 = (-equation->b_coef + sqrt_disc) / (2 * equation->a_coef);
  equation->root_2 = (-equation->b_coef - sqrt_disc) / (2 * equation->a_coef);
  equation->num_of_roots = Two;
}

auto CompareOneRoot(CoeffsAndRoots* test, double ans_1) -> bool {
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

auto CompareTwoRoots(CoeffsAndRoots* test, double ans_1, double ans_2) -> bool {
  bool const correct = ((CompareDoubles(ans_1, test->root_1) &&
                         CompareDoubles(ans_2, test->root_2)) ||
                        (CompareDoubles(ans_2, test->root_1) &&
                         CompareDoubles(ans_1, test->root_2)));
  if (!correct) {
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

auto CompareRoots(CoeffsAndRoots* test, double ans_1, double ans_2) -> bool {
  bool correct = false;
  switch (test->num_of_roots) {
    case One:
      correct = CompareOneRoot(test, ans_1);
      break;
    case Two:
      correct = CompareTwoRoots(test, ans_1, ans_2);
      break;
    case Inf:
      printf("test Ok: infinite roots exist\n");
      correct = true;
      break;
    case Zero:
      printf("test Ok: no roots exist\n");
      correct = true;
      break;
    case NotARoot:
    default:
      printf("test OK\n");
      return true;
  }
  return correct;
}

void UserMode() {
  CoeffsAndRoots equation{};

  Initialize(&equation);

  ScanCoeffs(&equation);

  SolveEquation(&equation);

  PrintRoots(&equation);

  Destroy(&equation);
}

void TestMode() {
  double ans_1 = NAN;
  double ans_2 = NAN;
  int num_of_roots = 0;

  FILE* data_file = fopen("data.txt", "re");

  int num_of_tests = 0;
  int correct_tests = 0;

  fscanf(data_file, "%d", &num_of_tests);

  CoeffsAndRoots test{};

  for (int i = 0; i < num_of_tests; ++i) {
    ScanData(data_file, &test, &num_of_roots, &ans_1, &ans_2);
    SolveEquation(&test);

    if (num_of_roots != test.num_of_roots) {
      printf("number of roots does not match!\n");
      continue;
    }
    correct_tests += static_cast<int>(CompareRoots(&test, ans_1, ans_2));
  }
  printf("tests correct %d / %d\n", correct_tests, num_of_tests);
  fclose(data_file);

  Destroy(&test);
}
