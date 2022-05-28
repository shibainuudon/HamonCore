/**
 *	@file	unit_test_iterator_concepts_random_access_iterator.cpp
 *
 *	@brief	random_access_iterator のテスト
 */

#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/config.hpp>
#include <string>
//#include <string_view>
#include <array>
#include <vector>
#include <list>
#include <deque>
#include "iterator_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_RANDOM_ACCESS_ITERATOR_TEST(B, ...)	\
	static_assert(B == hamon::random_access_iterator<__VA_ARGS__>, "");	\
	static_assert(B == hamon::random_access_iterator_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_RANDOM_ACCESS_ITERATOR_TEST(B, ...)	\
	static_assert(B == hamon::random_access_iterator<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::random_access_iterator_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace random_access_iterator_test
{

struct A {};

HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  int               *);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  int const         *);
//HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  int       volatile*);
//HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  int const volatile*);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, int               * const);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, int const         * const);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, int       volatile* const);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, int const volatile* const);

HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, void               *);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, void const         *);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, void       volatile*);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, void const volatile*);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, void               * const);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, void const         * const);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, void       volatile* const);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, void const volatile* const);

HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  void               **);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  void const         **);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  void       volatile**);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  void const volatile**);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, void               ** const);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, void const         ** const);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, void       volatile** const);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, void const volatile** const);

HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, void(*)());
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, void(&)());

// Avoid gcc 7 internal compiler error
#if !(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 80000))
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, void(A::*)());
#endif
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, int A::*);

HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  std::array<int, 1>::iterator);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  std::array<A, 1>::const_iterator);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  std::deque<int>::iterator);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  std::deque<A>::const_iterator);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, std::list<int>::iterator);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, std::list<A>::const_iterator);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  std::string::iterator);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  std::string::const_iterator);
//HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  std::string_view::iterator);
//HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  std::string_view::const_iterator);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  std::vector<int>::iterator);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  std::vector<A>::const_iterator);

HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, weakly_incrementable_wrapper<int>);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, incrementable_wrapper<int>);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, indirectly_readable_wrapper<int>);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, indirectly_writable_wrapper<int>);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, input_or_output_iterator_wrapper<int>);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, input_iterator_wrapper<int>);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, output_iterator_wrapper<int>);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, forward_iterator_wrapper<int>);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(false, bidirectional_iterator_wrapper<int>);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  random_access_iterator_wrapper<int>);
HAMON_RANDOM_ACCESS_ITERATOR_TEST(true,  contiguous_iterator_wrapper<int>);

}	// namespace random_access_iterator_test

}	// namespace hamon_iterator_test

#undef HAMON_RANDOM_ACCESS_ITERATOR_TEST
