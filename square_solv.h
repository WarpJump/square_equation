enum NumOfRoots { Zero = 0, One = 1, Two = 2, Inf = 3, NotARoot = -1 };

static const double kEpsilonLocality = 0.0001;

inline int IsZero(double value) { return fabs(value) < kEpsilonLocality; }

NumOfRoots RootOfLinearEquation(double b_coef, double c_coef, double* root);

NumOfRoots RootsOfSquareEquation(double a_coef, double b_coef, double c_coef,
                                 double* root_1, double* root_2);

void ScanCoeffs(double* a_coef, double* b_coef, double* c_coef);

void PrintRoots(NumOfRoots num_of_roots, double root_1, double root_2);

void ScanCoeffs(double* a_coef, double* b_coef, double* c_coef) {
  assert(a_coef != b_coef && b_coef != c_coef && a_coef != b_coef);
  assert(a_coef != nullptr);
  assert(b_coef != nullptr);
  assert(c_coef != nullptr);

  scanf("%lf", a_coef);
  scanf("%lf", b_coef);
  scanf("%lf", c_coef);
}

void PrintRoots(NumOfRoots num_of_roots, double root_1, double root_2) {
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

    case NotARoot:
    default:
      printf("error\n");
      break;
  }
}

NumOfRoots RootOfLinearEquation(double b_coef, double c_coef, double* root) {
  assert(!isnan(b_coef) && !isnan(c_coef));
  assert(!isinf(b_coef) && !isinf(c_coef));
  assert(root != nullptr);

  if (IsZero(b_coef)) {
    *root = NAN;
    if (IsZero(c_coef)) {
      return Inf;
    }
    return Zero;
  }
  *root = -c_coef / b_coef;
  return One;
}

NumOfRoots RootsOfSquareEquation(double a_coef, double b_coef, double c_coef,
                                 double* root_1, double* root_2) {
  assert(!isnan(a_coef) && !isnan(b_coef) && !isnan(c_coef));
  assert(!isinf(a_coef) && !isinf(b_coef) && !isinf(c_coef));

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
    *root_1 = *root_2 = NAN;
    return Zero;
  }
  double sqrt_disc = sqrt(disc);
  *root_1 = (-b_coef + sqrt_disc) / (2 * a_coef);
  *root_2 = (-b_coef - sqrt_disc) / (2 * a_coef);
  return Two;
}
