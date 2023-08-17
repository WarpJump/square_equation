#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "square_colv.h"

/* program that takes three floating-point numbers and solves square equation
 * assuming them as coefficients */

int main() {
  NumOfRoots num_of_roots = NotARoot;
  double a_coef = NAN;
  double b_coef = NAN;
  double c_coef = NAN;
  double root_1 = NAN;
  double root_2 = NAN;

  ScanCoeffs(&a_coef, &b_coef, &c_coef);

  num_of_roots =
      RootsOfSquareEquation(a_coef, b_coef, c_coef, &root_1, &root_2);

  PrintRoots(num_of_roots, root_1, root_2);

  return 0;
}
