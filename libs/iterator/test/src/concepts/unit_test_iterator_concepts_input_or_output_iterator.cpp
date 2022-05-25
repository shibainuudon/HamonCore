/**
 *	@file	unit_test_iterator_concepts_input_or_output_iterator.cpp
 *
 *	@brief	input_or_output_iterator のテスト
 */

#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/config.hpp>
#include <memory>
#include <vector>
#include "iterator_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(B, ...)	\
	static_assert(B == hamon::input_or_output_iterator<__VA_ARGS__>, "");	\
	static_assert(B == hamon::input_or_output_iterator_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(B, ...)	\
	static_assert(B == hamon::input_or_output_iterator<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::input_or_output_iterator_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace input_or_output_iterator_test
{

HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  int               *);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  int const         *);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  int       volatile*);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  int const volatile*);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int               * const);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int const         * const);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int       volatile* const);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int const volatile* const);

HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void               *);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void const         *);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void       volatile*);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void const volatile*);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void               * const);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void const         * const);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void       volatile* const);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void const volatile* const);

HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  void               **);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  void const         **);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  void       volatile**);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  void const volatile**);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void               ** const);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void const         ** const);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void       volatile** const);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void const volatile** const);

HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, std::unique_ptr<int>);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, std::shared_ptr<int>);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, std::vector<int>);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  std::vector<int>::iterator);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  std::vector<int>::const_iterator);

HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int[]);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int[2]);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int&);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int&&);

struct X
{
	friend auto operator++(X&) -> X&;
	friend auto operator++(X&, int) -> X&;
	using difference_type = int;
};

struct Y
{
	friend auto operator++(Y&) -> Y&;
	friend auto operator++(Y&, int) -> Y;
	friend auto operator*(Y&) -> int;
	using difference_type = int;
};

HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, X);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, X&);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, X const);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, X const&);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  Y);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, Y&);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, Y const);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, Y const&);

HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, weakly_incrementable_wrapper<int>);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, incrementable_wrapper<int>);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, indirectly_readable_wrapper<int>);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(false, indirectly_writable_wrapper<int>);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  input_or_output_iterator_wrapper<int>);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  input_iterator_wrapper<int>);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  output_iterator_wrapper<int>);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  forward_iterator_wrapper<int>);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  bidirectional_iterator_wrapper<int>);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  random_access_iterator_wrapper<int>);
HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  contiguous_iterator_wrapper<int>);

}	// namespace input_or_output_iterator_test

}	// namespace hamon_iterator_test

#undef HAMON_INPUT_OR_OUTPUT_ITERATOR_TEST
