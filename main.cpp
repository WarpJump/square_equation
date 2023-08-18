#include "core.cpp"

#define TEST false

/* program that takes three floating-point numbers and solves square equation
 * assuming them as coefficients */

int main() {
#if TEST
  TestMode();
#else
  RealMode();
#endif

  return 0;
}
