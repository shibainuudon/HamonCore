/**
 *	@file	unit_test_iterator_concepts_sentinel_for.cpp
 *
 *	@brief	sentinel_for のテスト
 */

#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/memory.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <memory>
#include <iterator>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_SENTINEL_FOR_TEST(B, ...)	\
	static_assert(B == hamon::sentinel_for<__VA_ARGS__>, "");	\
	static_assert(B == hamon::sentinel_for_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_SENTINEL_FOR_TEST(B, ...)	\
	static_assert(B == hamon::sentinel_for<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::sentinel_for_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace sentinel_for_test
{

HAMON_SENTINEL_FOR_TEST(true,  int*,                               int      *);
HAMON_SENTINEL_FOR_TEST(true,  int const*,                         int      *);
HAMON_SENTINEL_FOR_TEST(true,  int*,                               int const*);
HAMON_SENTINEL_FOR_TEST(true,  int const*,                         int const*);
HAMON_SENTINEL_FOR_TEST(false, int*,                               int      * const);
HAMON_SENTINEL_FOR_TEST(false, int*,                               int const* const);
HAMON_SENTINEL_FOR_TEST(false, int*,                               void*);
HAMON_SENTINEL_FOR_TEST(false, int*,                               hamon::unique_ptr<int>);
HAMON_SENTINEL_FOR_TEST(false, int*,                               std::shared_ptr<int>);
HAMON_SENTINEL_FOR_TEST(false, int*,                               hamon::vector<int>::iterator);
HAMON_SENTINEL_FOR_TEST(true,  hamon::vector<int>::iterator,       hamon::vector<int>::iterator);
HAMON_SENTINEL_FOR_TEST(false, int*,                               hamon::vector<int>::const_iterator);
HAMON_SENTINEL_FOR_TEST(true,  hamon::vector<int>::const_iterator, hamon::vector<int>::const_iterator);
HAMON_SENTINEL_FOR_TEST(false, int*,                               std::istream_iterator<int>);
HAMON_SENTINEL_FOR_TEST(true,  std::istream_iterator<int>,         std::istream_iterator<int>);
HAMON_SENTINEL_FOR_TEST(false, int*,                               std::ostream_iterator<int>);
HAMON_SENTINEL_FOR_TEST(false, std::ostream_iterator<int>,         std::ostream_iterator<int>);

HAMON_SENTINEL_FOR_TEST(false, int const, int*);
HAMON_SENTINEL_FOR_TEST(false, float*,    int*);
HAMON_SENTINEL_FOR_TEST(false, bool*,     int*);
HAMON_SENTINEL_FOR_TEST(true,  void*,     int*);

HAMON_SENTINEL_FOR_TEST(false, int*, int[]);
HAMON_SENTINEL_FOR_TEST(false, int*, int[2]);
HAMON_SENTINEL_FOR_TEST(false, int*, int&);
HAMON_SENTINEL_FOR_TEST(false, int*, int const&);
HAMON_SENTINEL_FOR_TEST(false, int*, int&&);
HAMON_SENTINEL_FOR_TEST(false, int*, int const&&);

HAMON_SENTINEL_FOR_TEST(false, int[],       int*);
HAMON_SENTINEL_FOR_TEST(false, int[2],      int*);
HAMON_SENTINEL_FOR_TEST(false, int&,        int*);
HAMON_SENTINEL_FOR_TEST(false, int const&,  int*);
HAMON_SENTINEL_FOR_TEST(false, int&&,       int*);
HAMON_SENTINEL_FOR_TEST(false, int const&&, int*);

struct Sentinel {};

struct X
{
	friend auto operator++(X&) -> X&;
	friend auto operator++(X&, int) -> X;
	friend auto operator*(X&) -> int;
	friend bool operator==(const X&, Sentinel);
	friend bool operator!=(const X&, Sentinel);
	friend bool operator==(Sentinel, const X&);
	friend bool operator!=(Sentinel, const X&);
	using difference_type = int;
};
struct Y
{
	friend auto operator++(Y&) -> Y&;
	friend auto operator++(Y&, int) -> Y;
	friend auto operator*(Y&) -> int;
//	friend bool operator==(const Y&, Sentinel);
	using difference_type = int;
};

HAMON_SENTINEL_FOR_TEST(true,  Sentinel, X);
HAMON_SENTINEL_FOR_TEST(false, X,        X);
HAMON_SENTINEL_FOR_TEST(false, int,      X);
HAMON_SENTINEL_FOR_TEST(false, Sentinel, Y);
HAMON_SENTINEL_FOR_TEST(false, Y,        Y);
HAMON_SENTINEL_FOR_TEST(false, int,      Y);

}	// namespace sentinel_for_test

}	// namespace hamon_iterator_test

#undef HAMON_SENTINEL_FOR_TEST
