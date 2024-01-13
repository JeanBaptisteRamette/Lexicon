/*!
 * @file Tests.hpp
 * @brief Définition de macro aidant à définir des tests et logging basique
 */

#ifndef LEXICON_TESTS_TESTS_HPP
#define LEXICON_TESTS_TESTS_HPP


#include <iostream>
#include <cstdlib>


#ifdef __FILE__
#define TEST_COMPONENT_ENTER() std::cout << "TESTING COMPONENT " << __FILE__ << std::endl
#define TEST_COMPONENT_LEAVE() std::cout << "COMPONENT " << __FILE__ << " TESTED" << std::endl
#else
#define TEST_COMPONENT_ENTER() ((void)0)
#define TEST_COMPONENT_LEAVE() ((void)0)
#endif

#if __cplusplus >= 201103L
#define CURRENT_FUNCTION_NAME __func__
#elif defined(__FUNCTION__)
#define CURRENT_FUNCTION_NAME __FUNCTION__
#endif

#ifdef CURRENT_FUNCTION_NAME
#define TEST_FUNCTION_ENTER() std::cout << std::endl << "----- " << CURRENT_FUNCTION_NAME << "..." << std::endl
#define TEST_FUNCTION_LEAVE() std::cout << "----- " << CURRENT_FUNCTION_NAME << " done" << std::endl
#else
#define TEST_FUNCTION_ENTER() ((void)0)
#define TEST_FUNCTION_LEAVE() ((void)0)
#endif

#define TEST_CASE_DEFINE(name) std::cout << "***** TEST CASE " << name << std::endl;
#define TEST_CASE_SUCCESS(str_expr) std::cout << "***** Success " << str_expr << std::endl

#ifdef CURRENT_FUNCTION_NAME
#define TEST_CASE_ERROR(str_expr) std::cerr << "***** Failed " << str_expr << ' ' << CURRENT_FUNCTION_NAME << std::endl; exit(EXIT_FAILURE)
#else
#define TEST_CASE_ERROR(str_expr) std::cerr << "***** Failed " << str_expr << ' ' << std::endl; exit(EXIT_FAILURE)
#endif


#define TEST_CASE_ASSERT_TRUE(expr) \
do {                                \
  if ((expr)) {                     \
      TEST_CASE_SUCCESS(#expr);     \
  } else {                          \
      TEST_CASE_ERROR(#expr);       \
  }                                 \
} while (0)


#define TEST_CASE_ASSERT_FALSE(expr) \
do {                                 \
  if (!(expr)) {                     \
      TEST_CASE_SUCCESS(#expr);      \
  } else {                           \
      TEST_CASE_ERROR(#expr);        \
  }                                  \
} while (0)


#define TEST_CASE_ASSERT_EQUAL(lhs, rhs) TEST_CASE_ASSERT_TRUE((lhs) == (rhs))
#define TEST_CASE_ASSERT_UNEQUAL(lhs, rhs) TEST_CASE_ASSERT_FALSE((lhs) == (rhs))


#endif //LEXICON_TESTS_TESTS_HPP
