/**
 *	@file	unit_test_iterator_concepts_indirectly_readable.cpp
 *
 *	@brief	indirectly_readable のテスト
 */

#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/config.hpp>
#include <memory>
#include <vector>
#include <iterator>
#include "iterator_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_INDIRECTLY_READABLE_TEST(B, ...)	\
	static_assert(B == hamon::indirectly_readable<__VA_ARGS__>, "");	\
	static_assert(B == hamon::indirectly_readable_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_INDIRECTLY_READABLE_TEST(B, ...)	\
	static_assert(B == hamon::indirectly_readable<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::indirectly_readable_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace indirectly_readable_test
{

HAMON_INDIRECTLY_READABLE_TEST(true,  int               *);
HAMON_INDIRECTLY_READABLE_TEST(true,  int const         *);
//HAMON_INDIRECTLY_READABLE_TEST(true,  int       volatile*);
//HAMON_INDIRECTLY_READABLE_TEST(true,  int const volatile*);
HAMON_INDIRECTLY_READABLE_TEST(true,  int               * const);
HAMON_INDIRECTLY_READABLE_TEST(true,  int const         * const);
//HAMON_INDIRECTLY_READABLE_TEST(true,  int       volatile* const);
//HAMON_INDIRECTLY_READABLE_TEST(true,  int const volatile* const);

HAMON_INDIRECTLY_READABLE_TEST(false, void               *);
HAMON_INDIRECTLY_READABLE_TEST(false, void const         *);
HAMON_INDIRECTLY_READABLE_TEST(false, void       volatile*);
HAMON_INDIRECTLY_READABLE_TEST(false, void const volatile*);
HAMON_INDIRECTLY_READABLE_TEST(false, void               * const);
HAMON_INDIRECTLY_READABLE_TEST(false, void const         * const);
HAMON_INDIRECTLY_READABLE_TEST(false, void       volatile* const);
HAMON_INDIRECTLY_READABLE_TEST(false, void const volatile* const);

HAMON_INDIRECTLY_READABLE_TEST(true,  void               **);
HAMON_INDIRECTLY_READABLE_TEST(true,  void const         **);
HAMON_INDIRECTLY_READABLE_TEST(true,  void       volatile**);
HAMON_INDIRECTLY_READABLE_TEST(true,  void const volatile**);
HAMON_INDIRECTLY_READABLE_TEST(true,  void               ** const);
HAMON_INDIRECTLY_READABLE_TEST(true,  void const         ** const);
HAMON_INDIRECTLY_READABLE_TEST(true,  void       volatile** const);
HAMON_INDIRECTLY_READABLE_TEST(true,  void const volatile** const);

HAMON_INDIRECTLY_READABLE_TEST(true,  std::unique_ptr<int>);
HAMON_INDIRECTLY_READABLE_TEST(true,  std::shared_ptr<int>);
HAMON_INDIRECTLY_READABLE_TEST(false, std::vector<int>);
HAMON_INDIRECTLY_READABLE_TEST(true,  std::vector<int>::iterator);
HAMON_INDIRECTLY_READABLE_TEST(true,  std::vector<int>::const_iterator);
HAMON_INDIRECTLY_READABLE_TEST(true,  std::istream_iterator<int>);
HAMON_INDIRECTLY_READABLE_TEST(false, std::ostream_iterator<int>);
//HAMON_INDIRECTLY_READABLE_TEST(true,  std::istreambuf_iterator<int>);
//HAMON_INDIRECTLY_READABLE_TEST(false, std::ostreambuf_iterator<int>);

HAMON_INDIRECTLY_READABLE_TEST(false, int[]);
HAMON_INDIRECTLY_READABLE_TEST(false, int[2]);
HAMON_INDIRECTLY_READABLE_TEST(false, int&);
HAMON_INDIRECTLY_READABLE_TEST(false, int&&);

struct X
{
	using value_type = char*;
};
struct Y
{
	char* const& operator*() const;
};
struct Z
{
	using value_type = char*;
	char* const& operator*() const;
};

HAMON_INDIRECTLY_READABLE_TEST(false, X);
HAMON_INDIRECTLY_READABLE_TEST(false, X&);
HAMON_INDIRECTLY_READABLE_TEST(false, X const);
HAMON_INDIRECTLY_READABLE_TEST(false, X const&);
HAMON_INDIRECTLY_READABLE_TEST(false, Y);
HAMON_INDIRECTLY_READABLE_TEST(false, Y&);
HAMON_INDIRECTLY_READABLE_TEST(false, Y const);
HAMON_INDIRECTLY_READABLE_TEST(false, Y const&);
HAMON_INDIRECTLY_READABLE_TEST(true,  Z);
HAMON_INDIRECTLY_READABLE_TEST(true,  Z&);
HAMON_INDIRECTLY_READABLE_TEST(true,  Z const);
HAMON_INDIRECTLY_READABLE_TEST(true,  Z const&);

HAMON_INDIRECTLY_READABLE_TEST(false, weakly_incrementable_wrapper<int>);
HAMON_INDIRECTLY_READABLE_TEST(false, incrementable_wrapper<int>);
HAMON_INDIRECTLY_READABLE_TEST(true,  indirectly_readable_wrapper<int>);
HAMON_INDIRECTLY_READABLE_TEST(false, indirectly_writable_wrapper<int>);
HAMON_INDIRECTLY_READABLE_TEST(false, input_or_output_iterator_wrapper<int>);
HAMON_INDIRECTLY_READABLE_TEST(true,  input_iterator_wrapper<int>);
HAMON_INDIRECTLY_READABLE_TEST(false, output_iterator_wrapper<int>);
HAMON_INDIRECTLY_READABLE_TEST(true,  forward_iterator_wrapper<int>);
HAMON_INDIRECTLY_READABLE_TEST(true,  bidirectional_iterator_wrapper<int>);
HAMON_INDIRECTLY_READABLE_TEST(true,  random_access_iterator_wrapper<int>);
HAMON_INDIRECTLY_READABLE_TEST(true,  contiguous_iterator_wrapper<int>);

}	// namespace indirectly_readable_test

}	// namespace hamon_iterator_test

#undef HAMON_INDIRECTLY_READABLE_TEST
