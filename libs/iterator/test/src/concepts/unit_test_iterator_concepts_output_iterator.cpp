/**
 *	@file	unit_test_iterator_concepts_output_iterator.cpp
 *
 *	@brief	output_iterator のテスト
 */

#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/array.hpp>
#include <hamon/deque.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/list.hpp>
#include <hamon/set.hpp>
#include <hamon/string_view.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <string>
#include "iterator_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_OUTPUT_ITERATOR_TEST(B, ...)	\
	static_assert(B == hamon::output_iterator<__VA_ARGS__>, "");	\
	static_assert(B == hamon::output_iterator_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_OUTPUT_ITERATOR_TEST(B, ...)	\
	static_assert(B == hamon::output_iterator<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::output_iterator_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace output_iterator_test
{

struct A {};

HAMON_OUTPUT_ITERATOR_TEST(true,  int*, int);
HAMON_OUTPUT_ITERATOR_TEST(true,  int*, const int);
HAMON_OUTPUT_ITERATOR_TEST(true,  int*, long);
HAMON_OUTPUT_ITERATOR_TEST(true,  void**, void*);
HAMON_OUTPUT_ITERATOR_TEST(true,  void**, long*);
HAMON_OUTPUT_ITERATOR_TEST(false, const int*, int);

HAMON_OUTPUT_ITERATOR_TEST(false, int* const, int);
HAMON_OUTPUT_ITERATOR_TEST(false, const int* const, int);
HAMON_OUTPUT_ITERATOR_TEST(false, void** const, void*);

HAMON_OUTPUT_ITERATOR_TEST(false, void*, void);
HAMON_OUTPUT_ITERATOR_TEST(false, const void*, void);
HAMON_OUTPUT_ITERATOR_TEST(false, const void*, void*);
HAMON_OUTPUT_ITERATOR_TEST(false, volatile void*, void);
HAMON_OUTPUT_ITERATOR_TEST(false, volatile void*, void*);

HAMON_OUTPUT_ITERATOR_TEST(false, void(*)(), void(&)());
HAMON_OUTPUT_ITERATOR_TEST(false, void(&)(), void(&)());
HAMON_OUTPUT_ITERATOR_TEST(true,  void(**)(), void(*)());
HAMON_OUTPUT_ITERATOR_TEST(true,  void(**)(), void(&)());

// Avoid gcc 7 internal compiler error
#if !(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 80000))
HAMON_OUTPUT_ITERATOR_TEST(false, void(A::*)(), A*);
HAMON_OUTPUT_ITERATOR_TEST(false, void(A::*)(), void(A::*)());
#endif
HAMON_OUTPUT_ITERATOR_TEST(false, int A::*, int);
HAMON_OUTPUT_ITERATOR_TEST(false, int A::*, int A::*);

HAMON_OUTPUT_ITERATOR_TEST(true,  hamon::array<int, 1>::iterator, int);
HAMON_OUTPUT_ITERATOR_TEST(true,  hamon::array<A, 1>::iterator, A);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::array<int, 1>::const_iterator, int);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::array<A, 1>::const_iterator, A);
HAMON_OUTPUT_ITERATOR_TEST(true,  hamon::deque<int>::iterator, int);
HAMON_OUTPUT_ITERATOR_TEST(true,  hamon::deque<A>::iterator, A);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::deque<int>::const_iterator, int);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::deque<A>::const_iterator, A);
HAMON_OUTPUT_ITERATOR_TEST(true,  hamon::forward_list<int>::iterator, int);
HAMON_OUTPUT_ITERATOR_TEST(true,  hamon::forward_list<A>::iterator, A);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::forward_list<int>::const_iterator, int);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::forward_list<A>::const_iterator, A);
HAMON_OUTPUT_ITERATOR_TEST(true,  hamon::list<int>::iterator, int);
HAMON_OUTPUT_ITERATOR_TEST(true,  hamon::list<A>::iterator, A);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::list<int>::const_iterator, int);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::list<A>::const_iterator, A);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::set<int>::iterator, int);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::set<A>::iterator, A);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::set<int>::const_iterator, int);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::set<A>::const_iterator, A);
HAMON_OUTPUT_ITERATOR_TEST(true,  std::string::iterator, char);
HAMON_OUTPUT_ITERATOR_TEST(true,  std::string::iterator, int);
HAMON_OUTPUT_ITERATOR_TEST(false, std::string::const_iterator, char);
HAMON_OUTPUT_ITERATOR_TEST(false, std::string::const_iterator, int);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::string_view::iterator, char);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::string_view::iterator, int);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::string_view::const_iterator, char);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::string_view::const_iterator, int);
HAMON_OUTPUT_ITERATOR_TEST(true,  hamon::vector<int>::iterator, int);
HAMON_OUTPUT_ITERATOR_TEST(true,  hamon::vector<A>::iterator, A);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::vector<int>::const_iterator, int);
HAMON_OUTPUT_ITERATOR_TEST(false, hamon::vector<A>::const_iterator, A);

HAMON_OUTPUT_ITERATOR_TEST(false, weakly_incrementable_wrapper<int>,     int);
HAMON_OUTPUT_ITERATOR_TEST(false, incrementable_wrapper<int>,            int);
HAMON_OUTPUT_ITERATOR_TEST(false, indirectly_readable_wrapper<int>,      int);
HAMON_OUTPUT_ITERATOR_TEST(false, indirectly_writable_wrapper<int>,      int);
HAMON_OUTPUT_ITERATOR_TEST(false, input_or_output_iterator_wrapper<int>, int);
HAMON_OUTPUT_ITERATOR_TEST(false, input_iterator_wrapper<int>,           int);
HAMON_OUTPUT_ITERATOR_TEST(true,  output_iterator_wrapper<int>,          int);
HAMON_OUTPUT_ITERATOR_TEST(true,  forward_iterator_wrapper<int>,         int);
HAMON_OUTPUT_ITERATOR_TEST(true,  bidirectional_iterator_wrapper<int>,   int);
HAMON_OUTPUT_ITERATOR_TEST(true,  random_access_iterator_wrapper<int>,   int);
HAMON_OUTPUT_ITERATOR_TEST(true,  contiguous_iterator_wrapper<int>,      int);

}	// namespace output_iterator_test

}	// namespace hamon_iterator_test

#undef HAMON_OUTPUT_ITERATOR_TEST
