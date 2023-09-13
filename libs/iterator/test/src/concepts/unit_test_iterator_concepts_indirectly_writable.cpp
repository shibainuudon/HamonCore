/**
 *	@file	unit_test_iterator_concepts_indirectly_writable.cpp
 *
 *	@brief	indirectly_writable のテスト
 */

#include <hamon/iterator/concepts/indirectly_writable.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <memory>
#include <iterator>
#include "iterator_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_INDIRECTLY_WRITABLE_TEST(B, ...)	\
	static_assert(B == hamon::indirectly_writable<__VA_ARGS__>, "");	\
	static_assert(B == hamon::indirectly_writable_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_INDIRECTLY_WRITABLE_TEST(B, ...)	\
	static_assert(B == hamon::indirectly_writable<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::indirectly_writable_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace indirectly_writable_test
{

HAMON_INDIRECTLY_WRITABLE_TEST(true,  int      *,                       int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, int const*,                       int);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  int      * const,                 int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, int const* const,                 int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, void*,                            int);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  std::unique_ptr<int>,             int);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  std::shared_ptr<int>,             int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, hamon::vector<int>,                 int);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  hamon::vector<int>::iterator,       int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, hamon::vector<int>::const_iterator, int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, std::istream_iterator<int>,       int);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  std::ostream_iterator<int>,       int);

HAMON_INDIRECTLY_WRITABLE_TEST(true,  int*, int const);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  int*, float);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  int*, bool);
HAMON_INDIRECTLY_WRITABLE_TEST(false, int*, void);
HAMON_INDIRECTLY_WRITABLE_TEST(false, int*, int*);
HAMON_INDIRECTLY_WRITABLE_TEST(false, int*, int[]);
HAMON_INDIRECTLY_WRITABLE_TEST(false, int*, int[2]);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  int*, int&);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  int*, int const&);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  int*, int&&);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  int*, int const&&);

HAMON_INDIRECTLY_WRITABLE_TEST(true,  int[],  int);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  int[2], int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, int&,   int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, int&&,  int);

struct X
{
	int& operator*();
};
struct Y
{
	int operator*();
};

HAMON_INDIRECTLY_WRITABLE_TEST(true,  X,        int);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  X&,       int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, X const,  int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, X const&, int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, Y,        int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, Y&,       int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, Y const,  int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, Y const&, int);

HAMON_INDIRECTLY_WRITABLE_TEST(false, weakly_incrementable_wrapper<int>,     int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, incrementable_wrapper<int>,            int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, indirectly_readable_wrapper<int>,      int);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  indirectly_writable_wrapper<int>,      int);
HAMON_INDIRECTLY_WRITABLE_TEST(false, input_or_output_iterator_wrapper<int>, int);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  input_iterator_wrapper<int>,           int);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  output_iterator_wrapper<int>,          int);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  forward_iterator_wrapper<int>,         int);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  bidirectional_iterator_wrapper<int>,   int);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  random_access_iterator_wrapper<int>,   int);
HAMON_INDIRECTLY_WRITABLE_TEST(true,  contiguous_iterator_wrapper<int>,      int);

}	// namespace indirectly_writable_test

}	// namespace hamon_iterator_test

#undef HAMON_INDIRECTLY_WRITABLE_TEST
