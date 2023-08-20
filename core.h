/*!
\file
\brief Header file with function and enum description
*/

/*!
\brief Enum needed to store number of roots
*/
enum NumOfRoots {
  Zero = 0,      ///< if there are no possible roots
  One = 1,       ///< if exist only one root: disc is zero or equation is linear
  Two = 2,       ///< if two roots exist
  Inf = 3,       ///< if exuation has infinite roots
  NotARoot = -1  ///< if something goes wrong during calculating
};

/*!
\brief struct that stores coefficien of square equation, number of roots and
values of roots
*/

struct CoeffsAndRoots {
  double a_coef = NAN;
  double b_coef = NAN;
  double c_coef = NAN;
  NumOfRoots num_of_roots = NotARoot;
  double root_1 = NAN;
  double root_2 = NAN;
};

static const double kEpsilonLocality = 0.005;

/*
 \brief Function that compares two variables of type double
 \param one, two - comparable doubles
 \return 1 - if doubles are equal, 0 otherwise

*/

inline int CompareDoubles(double one, double two) {
  return static_cast<int>(fabs(one - two) < kEpsilonLocality);
}

/// function that scans coefficients, number of roots and roots from file with
/// tests

void ScanData(FILE* data_file, CoeffsAndRoots* test, int* num_of_roots,
              double* ans_1, double* ans_2);

/*
  function that scans coefficients of square equation from standart input
  and refer them to fields of struct "equation"

  \param equation - struct with fields of coefficients
  \renurn does not return anything, because side effect is modifiying struct
*/

void ScanCoeffs(CoeffsAndRoots* equation);

/*
 \brief Function that compares root from struct "test" as function result and
 answer from file \param test - struct with computed root \param ans_1 - correct
 ans from file \return 1 - if root is correct, 0 otherwise

*/

int CompareOneRoot(CoeffsAndRoots* test, double ans_1);

/*
 \brief Function that compares two roots from struct "test" as function result
 and answer from file \param test - struct with computed roots \param ans_1
 ans_2 - correct answers from file \return 1 - if roots are correct, 0 otherwise

*/

int CompareTwoRoots(CoeffsAndRoots* test, double ans_1, double ans_2);

/*
 \brief Function that desides to call comparison functions
 \param test - struct with computed roots
 \param ans_1 ans_2 - correct answers from file
 \return 1 or 0 if roots are correct

  If there are no roots or infinite roots, return 1; Otherwise calls two root
 comparison functions or one root comparison functions, and returns their result
*/

int RootComparison(CoeffsAndRoots* test, double ans_1, double ans_2);

/*
 \brief Manager function for square equation
 \param equation - struct with all needed fields
 \return does not return anything, stores computed roots in "equation" as side
 effect

 Manager function that desides to call linear or square equation solver
*/

void SolveEquation(CoeffsAndRoots* equation);

/*
 \brief Function that solves linear equation
 \param equation - struct with all needed fields
 \return does not return anything, stores computed root in "equation" as side
 effect
*/

void RootOfLinearEquation(CoeffsAndRoots* equation);

/*
 \brief Function that solves square equation
 \param equation - struct with all needed fields
 \return does not return anything, stores number of computed roots ans roots
 itself in "equation" as side effect
*/

void RootsOfSquareEquation(CoeffsAndRoots* equation);

/*
 \brief Function that prints roots
 \param equation - struct with all needed fields
 \return does not return anything, prints roots as side effect
*/

void PrintRoots(CoeffsAndRoots* equation);

/*
 \brief Primary function for square equation solving
*/

void RealMode();

/*
 \brief Primary function for computing test mode
*/

void TestMode();
