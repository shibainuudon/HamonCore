/**
 *	@file	unit_test_iterator_concepts_input_iterator.cpp
 *
 *	@brief	input_iterator のテスト
 */

#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/array.hpp>
#include <hamon/deque.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/list.hpp>
#include <hamon/string_view.hpp>
#include <hamon/string.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <iterator>
#include "iterator_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_INPUT_ITERATOR_TEST(B, ...)	\
	static_assert(B == hamon::input_iterator<__VA_ARGS__>, "");	\
	static_assert(B == hamon::input_iterator_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_INPUT_ITERATOR_TEST(B, ...)	\
	static_assert(B == hamon::input_iterator<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::input_iterator_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace input_iterator_test
{

struct A {};

HAMON_INPUT_ITERATOR_TEST(true,  int               *);
HAMON_INPUT_ITERATOR_TEST(true,  int const         *);
//HAMON_INPUT_ITERATOR_TEST(true,  int       volatile*);
//HAMON_INPUT_ITERATOR_TEST(true,  int const volatile*);
HAMON_INPUT_ITERATOR_TEST(false, int               * const);
HAMON_INPUT_ITERATOR_TEST(false, int const         * const);
HAMON_INPUT_ITERATOR_TEST(false, int       volatile* const);
HAMON_INPUT_ITERATOR_TEST(false, int const volatile* const);

HAMON_INPUT_ITERATOR_TEST(true,  int               **);
HAMON_INPUT_ITERATOR_TEST(true,  int const         **);
HAMON_INPUT_ITERATOR_TEST(true,  int       volatile**);
HAMON_INPUT_ITERATOR_TEST(true,  int const volatile**);
HAMON_INPUT_ITERATOR_TEST(false, int               ** const);
HAMON_INPUT_ITERATOR_TEST(false, int const         ** const);
HAMON_INPUT_ITERATOR_TEST(false, int       volatile** const);
HAMON_INPUT_ITERATOR_TEST(false, int const volatile** const);

HAMON_INPUT_ITERATOR_TEST(false, void               *);
HAMON_INPUT_ITERATOR_TEST(false, void const         *);
HAMON_INPUT_ITERATOR_TEST(false, void       volatile*);
HAMON_INPUT_ITERATOR_TEST(false, void const volatile*);
HAMON_INPUT_ITERATOR_TEST(false, void               * const);
HAMON_INPUT_ITERATOR_TEST(false, void const         * const);
HAMON_INPUT_ITERATOR_TEST(false, void       volatile* const);
HAMON_INPUT_ITERATOR_TEST(false, void const volatile* const);

HAMON_INPUT_ITERATOR_TEST(true,  void               **);
HAMON_INPUT_ITERATOR_TEST(true,  void const         **);
HAMON_INPUT_ITERATOR_TEST(true,  void       volatile**);
HAMON_INPUT_ITERATOR_TEST(true,  void const volatile**);
HAMON_INPUT_ITERATOR_TEST(false, void               ** const);
HAMON_INPUT_ITERATOR_TEST(false, void const         ** const);
HAMON_INPUT_ITERATOR_TEST(false, void       volatile** const);
HAMON_INPUT_ITERATOR_TEST(false, void const volatile** const);

HAMON_INPUT_ITERATOR_TEST(false, void(*)());
HAMON_INPUT_ITERATOR_TEST(false, void(&)());

// Avoid gcc 7 internal compiler error
#if !(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 80000))
HAMON_INPUT_ITERATOR_TEST(false, void(A::*)());
#endif
HAMON_INPUT_ITERATOR_TEST(false, int A::*);

HAMON_INPUT_ITERATOR_TEST(true,  hamon::array<int, 1>::iterator);
HAMON_INPUT_ITERATOR_TEST(true,  hamon::array<A, 1>::const_iterator);
HAMON_INPUT_ITERATOR_TEST(true,  hamon::deque<int>::iterator);
HAMON_INPUT_ITERATOR_TEST(true,  hamon::deque<A>::const_iterator);
HAMON_INPUT_ITERATOR_TEST(true,  hamon::forward_list<int>::iterator);
HAMON_INPUT_ITERATOR_TEST(true,  hamon::forward_list<A>::const_iterator);
HAMON_INPUT_ITERATOR_TEST(true,  hamon::list<int>::iterator);
HAMON_INPUT_ITERATOR_TEST(true,  hamon::list<A>::const_iterator);
HAMON_INPUT_ITERATOR_TEST(true,  hamon::string::iterator);
HAMON_INPUT_ITERATOR_TEST(true,  hamon::string::const_iterator);
HAMON_INPUT_ITERATOR_TEST(true,  hamon::string_view::iterator);
HAMON_INPUT_ITERATOR_TEST(true,  hamon::string_view::const_iterator);
HAMON_INPUT_ITERATOR_TEST(true,  hamon::vector<int>::iterator);
HAMON_INPUT_ITERATOR_TEST(true,  hamon::vector<A>::const_iterator);
//HAMON_INPUT_ITERATOR_TEST(true,  std::istreambuf_iterator<char>);
//HAMON_INPUT_ITERATOR_TEST(false, std::ostreambuf_iterator<char>);

HAMON_INPUT_ITERATOR_TEST(false, weakly_incrementable_wrapper<int>);
HAMON_INPUT_ITERATOR_TEST(false, incrementable_wrapper<int>);
HAMON_INPUT_ITERATOR_TEST(false, indirectly_readable_wrapper<int>);
HAMON_INPUT_ITERATOR_TEST(false, indirectly_writable_wrapper<int>);
HAMON_INPUT_ITERATOR_TEST(false, input_or_output_iterator_wrapper<int>);
HAMON_INPUT_ITERATOR_TEST(true,  input_iterator_wrapper<int>);
HAMON_INPUT_ITERATOR_TEST(false, output_iterator_wrapper<int>);
HAMON_INPUT_ITERATOR_TEST(true,  forward_iterator_wrapper<int>);
HAMON_INPUT_ITERATOR_TEST(true,  bidirectional_iterator_wrapper<int>);
HAMON_INPUT_ITERATOR_TEST(true,  random_access_iterator_wrapper<int>);
HAMON_INPUT_ITERATOR_TEST(true,  contiguous_iterator_wrapper<int>);

}	// namespace input_iterator_test

}	// namespace hamon_iterator_test

#undef HAMON_INPUT_ITERATOR_TEST
