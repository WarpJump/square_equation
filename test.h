
#define printerror(error)                                        \
  fprintf(stderr, RedText(error) " in function %s in line %d\n", \
          __PRETTY_FUNCTION__, __LINE__)

/*!
\brief Exception controlling block.
\param statement - boolian expression. If not true throws an error
*/

#ifndef NDEBUG
#define AssertError(statement, error_code)                 \
  do {                                                     \
    if (!(statement)) {                                    \
      fprintf(stderr, "Error in function %s in line %d\n", \
              __PRETTY_FUNCTION__, __LINE__);              \
      return error_code;                                   \
    }                                                      \
  } while (0)
#else
#define AssertError(...) \
  do {                   \
  } while (0)
#endif

/*!
\brief primary functions where statements can be used, stores number of corrrect
test \param test_case_name - group of test name \param test_name - name of test
*/

#define TEST(test_case_name, test_name)       \
  int true_test = 0;                          \
  int* test_param_name = &true_test;          \
  for (int abracadabra = 0; abracadabra != 1; \
       ++abracadabra, printf(GreenText("CORRECT TESTS") " %d\n", true_test))

#define ASSERT_EQ(first, second)               \
  do {                                         \
    if (first != second) {                     \
      printerror("EQUATION ASSERTION FAILED"); \
      break;                                   \
    }                                          \
    (*test_param_name)++;                      \
  } while (0)

#define ASSERT_TRUE(statement)                \
  do {                                        \
    if (!(statement)) {                       \
      printerror("BOOLIAN ASSERTION FAILED"); \
      break;                                  \
    }                                         \
    (*test_param_name)++;                     \
  } while (0)

#define ASSERT_DOUBLE_EQ(double_1, double_2)          \
  do {                                                \
    if (!CompareDoubles(double_1, double_2)) {        \
      printerror("DOUBLE EQUATION ASSERTION FAILED"); \
      break;                                          \
    }                                                 \
    (*test_case_name##_##correct_tests)++;            \
  } while (0)
