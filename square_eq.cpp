#include <math.h>
#include <stdio.h>

/* program that takes three floating-point numbers and solves square equation
 * assuming them as coefficients */

static const double kEpsilonLocality = 0.0001;

static const int kInfiniteRoots = 10;

inline int IsZero(double value) {
  return (int)(fabs(value) < kEpsilonLocality);
}

int RootOfLinearEquation(double b_coef, double c_coef, double* root) {
  if (IsZero(b_coef)) {
    if (IsZero(c_coef)) {
      return kInfiniteRoots;
    }
    *root = 0;
    return 0;
  }
  *root = -c_coef / b_coef;
  return 1;
}

int RootsOfSquareEquation(double a_coef, double b_coef, double c_coef,
                          double* root_1, double* root_2) {
  if (IsZero(a_coef)) {
    return RootOfLinearEquation(b_coef, c_coef, root_1);
  }

  double disc = b_coef * b_coef - 4 * a_coef * c_coef;
  if (IsZero(disc)) {
    *root_1 = -b_coef / (2 * a_coef);
    return 1;
  }
  if (disc < 0) {
    return 0;
  }
  *root_1 = (-b_coef + sqrt(disc)) / (2 * a_coef);
  *root_2 = (-b_coef - sqrt(disc)) / (2 * a_coef);
  return 2;
}

int main() {
  int num_of_roots;
  double a_coef;
  double b_coef;
  double c_coef;
  double root_1;
  double root_2;
  scanf("%lf", &a_coef);
  scanf("%lf", &b_coef);
  scanf("%lf", &c_coef);

  num_of_roots =
      RootsOfSquareEquation(a_coef, b_coef, c_coef, &root_1, &root_2);

  if (num_of_roots == kInfiniteRoots) {
    printf("infinite roots exist\n");
    return 0;
  }

  if (num_of_roots == 2) {
    printf("two roots exist: %3.3lg and %3.3lg \n", root_1, root_2);
    return 0;
  }

  if (num_of_roots == 1) {
    printf("one root exist: %3.3lg \n", root_1);
    return 0;
  }
  printf("no roots exist\n");
  return 0;
}
