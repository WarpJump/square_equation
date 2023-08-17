#include <math.h>
#include <stdio.h>

#include <cassert>

/* program that takes three floating-point numbers and solves square equation
 * assuming them as coefficients */

static const double kEpsilonLocality = 0.0001;

static const int kInfiniteRoots = 10;

enum Roots { Zero, One, Two, Inf, NaR };

inline int IsZero(double value) { return (fabs(value) < kEpsilonLocality); }

void ScanCoeffs(double* a_coef, double* b_coef, double* c_coef);

Roots RootOfLinearEquation(double b_coef, double c_coef, double* root);

Roots RootsOfSquareEquation(double a_coef, double b_coef, double c_coef,
                            double* root_1, double* root_2);

void PrintRoots(Roots num_of_roots, double root_1, double root_2);

int main() {
  Roots num_of_roots = NaR;
  double a_coef = NAN;
  double b_coef = NAN;
  double c_coef = NAN;
  double root_1 = 0;
  double root_2 = 0;

  ScanCoeffs(&a_coef, &b_coef, &c_coef);

  num_of_roots =
      RootsOfSquareEquation(a_coef, b_coef, c_coef, &root_1, &root_2);

  PrintRoots(num_of_roots, root_1, root_2);

  return 0;
}

void ScanCoeffs(double* a_coef, double* b_coef, double* c_coef) {
  assert(a_coef != b_coef && b_coef != c_coef && a_coef != b_coef);
  assert(a_coef != nullptr);
  assert(b_coef != nullptr);
  assert(c_coef != nullptr);

  scanf("%lf", a_coef);
  scanf("%lf", b_coef);
  scanf("%lf", c_coef);
}

Roots RootOfLinearEquation(double b_coef, double c_coef, double* root) {
  assert(root != nullptr);

  if (IsZero(b_coef)) {
    if (IsZero(c_coef)) {
      return Inf;
    }
    return Zero;
  }
  *root = -c_coef / b_coef;
  return One;
}

Roots RootsOfSquareEquation(double a_coef, double b_coef, double c_coef,
                            double* root_1, double* root_2) {
  assert(!isnan(a_coef) && !isnan(b_coef) && !isnan(c_coef));

  assert(root_2 != root_1);
  assert(root_1 != nullptr);
  assert(root_2 != nullptr);

  if (IsZero(a_coef)) {
    return RootOfLinearEquation(b_coef, c_coef, root_1);
  }

  double disc = b_coef * b_coef - 4 * a_coef * c_coef;
  if (IsZero(disc)) {
    *root_1 = -b_coef / (2 * a_coef);
    return One;
  }
  if (disc < 0) {
    return Zero;
  }
  *root_1 = (-b_coef + sqrt(disc)) / (2 * a_coef);
  *root_2 = (-b_coef - sqrt(disc)) / (2 * a_coef);
  return Two;
}

void PrintRoots(Roots num_of_roots, double root_1, double root_2) {
  switch (num_of_roots) {
    case One:
      printf("one root exist: %3.3lg \n", root_1);
      break;

    case Two:
      printf("two roots exist: %3.3lg and %3.3lg \n", root_1, root_2);
      break;

    case Inf:
      printf("infinite roots exist\n");
      break;

    case Zero:
      printf("no roots exist\n");
      break;

    case NaR:
      printf("error\n");
      break;

    default:
      printf("error\n");
  }
}
