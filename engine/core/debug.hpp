#pragma once

#ifdef PR_DEBUG
  #include <stdexcept>
  #define PR_ASSERT(expr, msg) \
    do { if (!(expr)) throw std::runtime_error(msg); } while (0)
#else
  #define PR_ASSERT(expr, msg) ((void)0)
#endif

#ifdef PR_DEBUG
  #define PR_ASSERT_NODE(expr, msg) \
    do { if (!(expr)) throw NodeError(msg); } while (0)
#else
  #define PR_ASSERT_NODE(expr, msg) ((void)0)
#endif
