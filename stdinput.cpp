#include "colors.h"
#include "core.h"
#include "test.h"

/*!
  \file
  \brief File with standart input functions
*/

ErrorCodes ScanCoeffs(CoeffsAndRoots *equation) {
  AssertError(equation != nullptr, ErrorCodes::NullPointer);
  int coeffs_inputed = scanf("%lf %lf %lf", &(equation->a_coef),
                             &(equation->b_coef), &(equation->c_coef));

  if (coeffs_inputed != 3) {
    printf("Bad input, try again\n");
    while (getchar() != '\n')
      ;

    return ErrorCodes::BadInput;
  }

  return ErrorCodes::Ok;
}

ErrorCodes ScanData(FILE *data_file, CoeffsAndRoots *test, int *num_of_roots,
                    double *ans_1, double *ans_2, bool *end_of_file) {
  AssertError(test, ErrorCodes::NullPointer);
  AssertError(ans_1 && ans_2, ErrorCodes::NullPointer);
  AssertError(ans_1 != ans_2, ErrorCodes::SamePointers);

  int ArgsInputed =
      fscanf(data_file, "%lf %lf %lf %d %lf %lf", &(test->a_coef),
             &(test->b_coef), &(test->c_coef), num_of_roots, ans_1, ans_2);

  if(ArgsInputed == 6){
    return ErrorCodes::Ok;
  }
  if(ArgsInputed == -1){
    *end_of_file = true;
    return ErrorCodes::Ok;
  }
  return ErrorCodes::BadInput;
}
