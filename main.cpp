/*!
\file
\brief Main program
*/

#include "colors.h"
#include "core.h"

/*! if macros TEST during compilation set to true, program run in test mode. If
 TEST set to false, program runs in real mode: takes three floating-point
 numbers and solves square equation assuming them as coefficients
*/

/*! Main program. Decides in compile-time in which mode to run.
 */

int main(int argc, char** argv) {
#ifdef TEST
  TestMode(argc, argv);
#else
  UserMode(argc, argv);
#endif
  return 0;
}
