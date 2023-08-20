/*!
\file
\brief Main program
*/

#include "core.cpp"

/*! if macros TEST set to true, program run in test mode. If TEST set to false,
 program runs in real mode: takes three floating-point numbers and solves square
 equation assuming them as coefficients
*/
#define TEST true

/*! Main program. Decides in compile-time in which mode to run.
 */

int main() {
#if TEST
  TestMode();
#else
  RealMode();
#endif

  return 0;
}
