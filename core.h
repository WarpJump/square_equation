/*!
\file
\brief Header file with function and enum description
*/

#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

/*!
\brief Excepption controlling block.
\param statement - boolian expression. If not true throws an error
*/

#ifndef NDEBUG
#define AssertError(statement, error_code)                           \
  do {                                                               \
    if (!(statement)) {                                              \
      fprintf(stderr, "Error in function %s in line %d\n", __func__, \
              __LINE__);                                             \
      return error_code;                                             \
    }                                                                \
  } while (0)
#else
#define AssertError(...) do{} while(0)
#endif

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
\brief Enum needed to store error codes
*/

enum ErrorCodes {
  NullPointer = 1,    ///< if pointer is null
  SamePointers = 2,   ///< if two different values have same pointer
  InfiniteFloat = 3,  ///< if value if inf
  ZeroDivision = 4,   ///< if divider is zero
  Ok = 0              ///< if everything is normal

};

/*!
 \brief struct that stores coefficien of square equation, number of roots and
 values of roots
*/

struct CoeffsAndRoots {
  double a_coef = NAN;  ///< coefficient near x^2 in square equation.
  double b_coef = NAN;  ///< coefficient near x in square equation.
  double c_coef = NAN;  ///< constant in square equation.
  NumOfRoots num_of_roots = NotARoot;  ///< number of roots
  double root_1 = NAN;  ///< first root. Assigned to NAN if does not exist
  double root_2 = NAN;  ///< second root. Assigned to NAN if does not exist
};

/*!
 \brief assignes default fields of struct.
 \param structure - pointer to structure to be assigned
*/

void Initialize(CoeffsAndRoots* structure);

/*!
 \brief assignes poison to fields of struct.
 \param structure - pointer to structure to be assigned
*/

void Destroy(CoeffsAndRoots* structure);

/*!
 \brief Function that compares two variables of type double
 \param one, two - comparable doubles
 \return 1 - if doubles are equal, 0 otherwise
*/

inline bool CompareDoubles(double one, double two) {
  static const double kEpsilonLocality =
      0.005;  //< constant determining permissible error for double comparison
  return fabs(one - two) < kEpsilonLocality;
}

/*! function that scans command line and interprets flags as coefficients
*/


ErrorCodes ParseCommandLine(CoeffsAndRoots &equation, int argc, char** argv);

/*! function that scans coefficients, number of roots and roots from file with
 tests
*/

ErrorCodes ScanData(FILE* data_file, CoeffsAndRoots* test, int* num_of_roots,
                    double* ans_1, double* ans_2);

/*!
  \brief Function that takes a string and two characters, and founds pointers to last match of them in string
  \param [in] str - pointer to string where to search
  \param [in] first_symbol_to_find - first symbol will be searched in string
  \param [in] second_symbol_to_find - second symbol will be searched in string
  \param [out] first_char - pointer of last match of first_symbol_to_find in the string
  \param [out] second_char - pointer of last match of second_symbol_to_find in the string

*/

ErrorCodes ParseString(char *str, char first_symbol_to_find, char second_symbol_to_find, char **first_char,
                       char **second_char);


/*!
  \brief Function for creating string of given size in dynamic memory
  \param [in] valuable_size - size of a string without terminating character

  Actially creates a string size valuable_size + 1 to store terminating char
*/
char *CreateString(size_t valuable_size);

/*!
  \brief function that calls free on string
  \param [in] old_string - pointer to string to be destroyed
*/

void DestroyString(char *old_string);

/*!
  \brief Copy one string to anoter 
  \param [out] target - where to store string
  \param [in] source - where to get original string
  \param [in] number - how many chars to copy
  a memcpy syntax sugar for better unerstanding of copying strings
*/

void CopyFirstCharsString(char *target, char *source, size_t number);

/*!
\brief Function that parses one argument which was entered via command line
\param [in] flag - string with one argument
\param [out] equation - pointer to struct where to store value from argument
*/
ErrorCodes ParseOneFlag(CoeffsAndRoots *equation, char *flag);


/*!
\brief Function that parses arguments from command line
\param [in] argc - number of arguments given in command line
\param [in] argv - array of strings interpreted as arguments
\param [out] equation - pointer to a structure where to store values given in command line
*/

ErrorCodes ParseCommandLine(CoeffsAndRoots *equation, int argc, char **argv);


/*!
  function that scans coefficients of square equation from standart input
  and refer them to fields of struct "equation"

  \param equation - struct with fields of coefficients
  Does not return anything, because side effect is modifiying struct
*/

ErrorCodes ScanCoeffs(CoeffsAndRoots* equation);

/*!
 \brief Function that compares root from struct "test" as function result and
 answer from file.
 \param test - struct with computed root.
 \param ans_1 - correct ans from file.
 \return 1 - if root is correct, 0 otherwise

*/

bool CompareOneRoot(CoeffsAndRoots* test, double ans_1);

/*!
 \brief Function that compares two roots from struct "test" as function result
 and answer from file.
 \param test - struct with computed roots.
 \param ans_1 - first correct answer from the file.
 \param ans_2 - second correct answers from file.
 \return 1 - if roots are correct, 0 otherwise.

*/

bool CompareTwoRoots(CoeffsAndRoots* test, double ans_1, double ans_2);

/*!
 \brief Function that desides to call comparison functions
 \param test - struct with computed roots.
 \param ans_1 - correct first answer from file.
 \param ans_2 - correct second answer from file.
 \return 1 or 0 if roots are correct.

  If there are no roots or infinite roots, return 1; Otherwise calls two root
 comparison functions or one root comparison functions, and returns their result
*/

bool CompareRoots(CoeffsAndRoots* test, double ans_1, double ans_2);

/*!
 \brief function for printing error messages
 \param [in] code - error message
*/

void PrintErrorCode(ErrorCodes code);

/*!
 \brief Manager function for square equation
 \param equation - struct with all needed fields
 Does not return anything, stores computed roots in "equation" as side
 effect

 Manager function that desides to call linear or square equation solver
*/

ErrorCodes SolveEquation(CoeffsAndRoots* equation);

/*!
 \brief Function that solves linear equation
 \param equation - struct with all needed fields
 Does not return anything, stores computed root in "equation" as side
 effect
*/

ErrorCodes FindRootOfLinearEquation(CoeffsAndRoots* equation);

/*!
 \brief Function that solves square equation
 \param equation - struct with all needed fields
 Does not return anything, stores number of computed roots ans roots
 itself in "equation" as side effect
*/

ErrorCodes FindRootsOfSquareEquation(CoeffsAndRoots* equation);

/*!
 \brief Function that prints roots
 \param equation - struct with all needed fields
 Does not return anything, prints roots as side effect
*/

void PrintRoots(CoeffsAndRoots* equation);

/*!
 \brief Primary function for square equation solving
*/

void UserMode(int argc, char** argv);

/*!
 \brief Primary function for computing test mode
*/

void TestMode();
