enum NumOfRoots { Zero = 0, One = 1, Two = 2, Inf = 3, NotARoot = -1 };

struct CoeffsAndRoots {
  double a_coef = NAN;
  double b_coef = NAN;
  double c_coef = NAN;
  NumOfRoots num_of_roots = NotARoot;
  double root_1 = NAN;
  double root_2 = NAN;
};

static const double kEpsilonLocality = 0.005;

inline int CompareDoubles(double one, double two) {
  return static_cast<int>(fabs(one - two) < kEpsilonLocality);
}

void ScanData(FILE* data_file, CoeffsAndRoots* test, int* num_of_roots,
              double* ans_1, double* ans_2);

void ScanCoeffs(CoeffsAndRoots* equation);

int CompareOneRoot(CoeffsAndRoots* test, double ans_1);

int CompareTwoRoots(CoeffsAndRoots* test, double ans_1, double ans_2);

int RootComparison(CoeffsAndRoots* test, double ans_1, double ans_2);

void SolveEquation(CoeffsAndRoots* equation);

void RootOfLinearEquation(CoeffsAndRoots* equation);

void RootsOfSquareEquation(CoeffsAndRoots* equation);

void PrintRoots(CoeffsAndRoots* equation);

void RealMode();

void TestMode();
