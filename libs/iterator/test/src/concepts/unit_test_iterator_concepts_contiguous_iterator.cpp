/**
 *	@file	unit_test_iterator_concepts_contiguous_iterator.cpp
 *
 *	@brief	contiguous_iterator のテスト
 */

#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/array.hpp>
#include <hamon/config.hpp>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include "iterator_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_CONTIGUOUS_ITERATOR_TEST(B, ...)	\
	static_assert(B == hamon::contiguous_iterator<__VA_ARGS__>, "");	\
	static_assert(B == hamon::contiguous_iterator_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_CONTIGUOUS_ITERATOR_TEST(B, ...)	\
	static_assert(B == hamon::contiguous_iterator<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::contiguous_iterator_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace contiguous_iterator_test
{

struct A {};

HAMON_CONTIGUOUS_ITERATOR_TEST(true,  int               *);
HAMON_CONTIGUOUS_ITERATOR_TEST(true,  int const         *);
//HAMON_CONTIGUOUS_ITERATOR_TEST(true,  int       volatile*);
//HAMON_CONTIGUOUS_ITERATOR_TEST(true,  int const volatile*);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, int               * const);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, int const         * const);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, int       volatile* const);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, int const volatile* const);

HAMON_CONTIGUOUS_ITERATOR_TEST(false, void               *);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, void const         *);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, void       volatile*);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, void const volatile*);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, void               * const);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, void const         * const);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, void       volatile* const);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, void const volatile* const);

HAMON_CONTIGUOUS_ITERATOR_TEST(true,  void               **);
HAMON_CONTIGUOUS_ITERATOR_TEST(true,  void const         **);
HAMON_CONTIGUOUS_ITERATOR_TEST(true,  void       volatile**);
HAMON_CONTIGUOUS_ITERATOR_TEST(true,  void const volatile**);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, void               ** const);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, void const         ** const);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, void       volatile** const);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, void const volatile** const);

HAMON_CONTIGUOUS_ITERATOR_TEST(false, void(*)());
HAMON_CONTIGUOUS_ITERATOR_TEST(false, void(&)());
HAMON_CONTIGUOUS_ITERATOR_TEST(true,  void(**)());

// Avoid gcc 7 internal compiler error
#if !(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 80000))
HAMON_CONTIGUOUS_ITERATOR_TEST(false, void(A::*)());
#endif
HAMON_CONTIGUOUS_ITERATOR_TEST(false, int A::*);

#if defined(HAMON_USE_STD_RANGES_ITERATOR)
HAMON_CONTIGUOUS_ITERATOR_TEST(true,  hamon::array<int, 1>::iterator);
HAMON_CONTIGUOUS_ITERATOR_TEST(true,  hamon::array<A, 1>::const_iterator);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, std::deque<int>::iterator);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, std::deque<A>::const_iterator);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, std::list<int>::iterator);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, std::list<A>::const_iterator);
HAMON_CONTIGUOUS_ITERATOR_TEST(true,  std::string::iterator);
HAMON_CONTIGUOUS_ITERATOR_TEST(true,  std::string::const_iterator);
HAMON_CONTIGUOUS_ITERATOR_TEST(true,  std::vector<int>::iterator);
HAMON_CONTIGUOUS_ITERATOR_TEST(true,  std::vector<A>::const_iterator);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, std::vector<bool>::iterator);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, std::vector<bool>::const_iterator);
#endif

HAMON_CONTIGUOUS_ITERATOR_TEST(false, weakly_incrementable_wrapper<int>);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, incrementable_wrapper<int>);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, indirectly_readable_wrapper<int>);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, indirectly_writable_wrapper<int>);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, input_or_output_iterator_wrapper<int>);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, input_iterator_wrapper<int>);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, output_iterator_wrapper<int>);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, forward_iterator_wrapper<int>);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, bidirectional_iterator_wrapper<int>);
HAMON_CONTIGUOUS_ITERATOR_TEST(false, random_access_iterator_wrapper<int>);
HAMON_CONTIGUOUS_ITERATOR_TEST(true,  contiguous_iterator_wrapper<int>);

}	// namespace contiguous_iterator_test

}	// namespace hamon_iterator_test

#undef HAMON_CONTIGUOUS_ITERATOR_TEST
