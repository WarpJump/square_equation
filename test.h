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
