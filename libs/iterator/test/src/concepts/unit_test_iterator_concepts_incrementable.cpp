/**
 *	@file	unit_test_iterator_concepts_incrementable.cpp
 *
 *	@brief	incrementable のテスト
 */

#include <hamon/iterator/concepts/incrementable.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <memory>
#include <iterator>
#include "iterator_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_INCREMENTABLE_TEST(B, ...)	\
	static_assert(B == hamon::incrementable<__VA_ARGS__>, "");	\
	static_assert(B == hamon::incrementable_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_INCREMENTABLE_TEST(B, ...)	\
	static_assert(B == hamon::incrementable<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::incrementable_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace incrementable_test
{

HAMON_INCREMENTABLE_TEST(true,  int               *);
HAMON_INCREMENTABLE_TEST(true,  int const         *);
HAMON_INCREMENTABLE_TEST(true,  int       volatile*);
HAMON_INCREMENTABLE_TEST(true,  int const volatile*);
HAMON_INCREMENTABLE_TEST(false, int               * const);
HAMON_INCREMENTABLE_TEST(false, int const         * const);
HAMON_INCREMENTABLE_TEST(false, int       volatile* const);
HAMON_INCREMENTABLE_TEST(false, int const volatile* const);

HAMON_INCREMENTABLE_TEST(false, void               *);
HAMON_INCREMENTABLE_TEST(false, void const         *);
HAMON_INCREMENTABLE_TEST(false, void       volatile*);
HAMON_INCREMENTABLE_TEST(false, void const volatile*);
HAMON_INCREMENTABLE_TEST(false, void               * const);
HAMON_INCREMENTABLE_TEST(false, void const         * const);
HAMON_INCREMENTABLE_TEST(false, void       volatile* const);
HAMON_INCREMENTABLE_TEST(false, void const volatile* const);

HAMON_INCREMENTABLE_TEST(false, std::unique_ptr<int>);
HAMON_INCREMENTABLE_TEST(false, std::shared_ptr<int>);
HAMON_INCREMENTABLE_TEST(false, hamon::vector<int>);
HAMON_INCREMENTABLE_TEST(true,  hamon::vector<int>::iterator);
HAMON_INCREMENTABLE_TEST(true,  hamon::vector<int>::const_iterator);
HAMON_INCREMENTABLE_TEST(true,  std::istream_iterator<int>);
HAMON_INCREMENTABLE_TEST(false, std::ostream_iterator<int>);

HAMON_INCREMENTABLE_TEST(false, int[]);
HAMON_INCREMENTABLE_TEST(false, int[2]);
HAMON_INCREMENTABLE_TEST(false, int&);
HAMON_INCREMENTABLE_TEST(false, int&&);

struct X
{
	friend auto operator++(X&)->X&;
	friend auto operator++(X&, int)->X&;
	using difference_type = int;
};

struct Y
{
	friend auto operator++(Y&)->Y&;
	friend auto operator++(Y&, int)->Y; // prvalueを返す必要がある
	friend bool operator==(const Y&, const Y&);
	friend bool operator!=(const Y&, const Y&);
	using difference_type = int;
};

HAMON_INCREMENTABLE_TEST(false, X);
HAMON_INCREMENTABLE_TEST(false, X&);
HAMON_INCREMENTABLE_TEST(false, X const);
HAMON_INCREMENTABLE_TEST(false, X const&);
HAMON_INCREMENTABLE_TEST(true,  Y);
HAMON_INCREMENTABLE_TEST(false, Y&);
HAMON_INCREMENTABLE_TEST(false, Y const);
HAMON_INCREMENTABLE_TEST(false, Y const&);

HAMON_INCREMENTABLE_TEST(false, weakly_incrementable_wrapper<int>);
HAMON_INCREMENTABLE_TEST(true,  incrementable_wrapper<int>);
HAMON_INCREMENTABLE_TEST(false, indirectly_readable_wrapper<int>);
HAMON_INCREMENTABLE_TEST(false, indirectly_writable_wrapper<int>);
HAMON_INCREMENTABLE_TEST(false, input_or_output_iterator_wrapper<int>);
HAMON_INCREMENTABLE_TEST(false, input_iterator_wrapper<int>);
HAMON_INCREMENTABLE_TEST(false, output_iterator_wrapper<int>);
HAMON_INCREMENTABLE_TEST(true,  forward_iterator_wrapper<int>);
HAMON_INCREMENTABLE_TEST(true,  bidirectional_iterator_wrapper<int>);
HAMON_INCREMENTABLE_TEST(true,  random_access_iterator_wrapper<int>);
HAMON_INCREMENTABLE_TEST(true,  contiguous_iterator_wrapper<int>);

}	// namespace incrementable_test

}	// namespace hamon_iterator_test

#undef HAMON_INCREMENTABLE_TEST
