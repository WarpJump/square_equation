#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "square_colv.h"

/* testing program for square equation solver */

FILE* fp;

static const double kNormalInaccuracy = 0.05;

void ScanData(double* a_coef, double* b_coef, double* c_coef, int* num_of_roots,
              double* ans_1, double* ans_2);

inline int CompareDoubles(double one, double two);

void test_system();

int main() {
  test_system();
  return 0;
}

void test_system() {
  double a_coef = NAN;
  double b_coef = NAN;
  double c_coef = NAN;
  int num_of_roots;
  double ans_1 = NAN;
  double ans_2 = NAN;
  double root_1 = NAN;
  double root_2 = NAN;

  fp = fopen("data.txt", "r");

  int num_of_tests;

  fscanf(fp, "%d", &num_of_tests);

  int correct_tests = 0;
  for (int i = 0; i < num_of_tests; ++i) {
    int correct = 0;
    ScanData(&a_coef, &b_coef, &c_coef, &num_of_roots, &ans_1, &ans_2);
    if (num_of_roots !=
        RootsOfSquareEquation(a_coef, b_coef, c_coef, &root_1, &root_2)) {
      printf("number of roots does not match!\n");
      continue;
    }
    switch (num_of_roots) {
      case One:
        if (CompareDoubles(ans_1, root_1) == 0) {
          printf("the only root does not match\n");
        } else {
          printf("test OK\n");
          ++correct_tests;
        }
        break;
      case Two:
        correct = ((CompareDoubles(ans_1, root_1) != 0) &&
                   (CompareDoubles(ans_2, root_2) != 0)) ||
                  ((CompareDoubles(ans_2, root_1) != 0) &&
                   (CompareDoubles(ans_1, root_2) != 0));
        if (correct == 0) {
          printf("two roots does not match\n");
        } else {
          printf("test OK\n");
          ++correct_tests;
        }
        break;
      case Inf:
      case Zero:
      default:
        printf("test OK\n");
        ++correct_tests;
        break;
    }
  }
  printf("tests correct %d / %d\n", correct_tests, num_of_tests);
}

inline int CompareDoubles(double one, double two) {
  return ((one - two) < kNormalInaccuracy);
}

void ScanData(double* a_coef, double* b_coef, double* c_coef, int* num_of_roots,
              double* ans_1, double* ans_2) {
  fscanf(fp, "%lf", a_coef);
  fscanf(fp, "%lf", b_coef);
  fscanf(fp, "%lf", c_coef);
  fscanf(fp, "%d", num_of_roots);
  fscanf(fp, "%lf", ans_1);
  fscanf(fp, "%lf", ans_2);
}
