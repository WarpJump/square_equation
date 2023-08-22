/*!
\file
\brief Main program
*/

#include "core.cpp"

/*! if macros TEST set to true, program run in test mode. If TEST set to false,
 program runs in real mode: takes three floating-point numbers and solves square
 equation assuming them as coefficients
*/
/*! Main program. Decides in compile-time in which mode to run.
 */

int main() {
#ifdef TEST
  TestMode();
#else
  UserMode();
#endif

  return 0;
}
