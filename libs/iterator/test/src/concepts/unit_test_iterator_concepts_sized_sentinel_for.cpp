/**
 *	@file	unit_test_iterator_concepts_sized_sentinel_for.cpp
 *
 *	@brief	sized_sentinel_for のテスト
 */

#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/concepts/disable_sized_sentinel_for.hpp>
#include <hamon/config.hpp>
#include <vector>
#include <memory>
#include <iterator>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_SIZED_SENTINEL_FOR_TEST(B, ...)	\
	static_assert(B == hamon::sized_sentinel_for<__VA_ARGS__>, "");	\
	static_assert(B == hamon::sized_sentinel_for_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_SIZED_SENTINEL_FOR_TEST(B, ...)	\
	static_assert(B == hamon::sized_sentinel_for<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::sized_sentinel_for_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace sized_sentinel_for_test
{

HAMON_SIZED_SENTINEL_FOR_TEST(true,  int*,                               int      *);
HAMON_SIZED_SENTINEL_FOR_TEST(true,  int const*,                         int      *);
HAMON_SIZED_SENTINEL_FOR_TEST(true,  int*,                               int const*);
HAMON_SIZED_SENTINEL_FOR_TEST(true,  int const*,                         int const*);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int*,                               int      * const);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int*,                               int const* const);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int*,                               void*);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int*,                               std::unique_ptr<int>);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int*,                               std::shared_ptr<int>);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int*,                               std::vector<int>::iterator);
HAMON_SIZED_SENTINEL_FOR_TEST(true,  std::vector<int>::iterator,         std::vector<int>::iterator);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int*,                               std::vector<int>::const_iterator);
HAMON_SIZED_SENTINEL_FOR_TEST(true,  std::vector<int>::const_iterator,   std::vector<int>::const_iterator);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int*,                               std::istream_iterator<int>);
HAMON_SIZED_SENTINEL_FOR_TEST(false, std::istream_iterator<int>,         std::istream_iterator<int>);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int*,                               std::ostream_iterator<int>);
HAMON_SIZED_SENTINEL_FOR_TEST(false, std::ostream_iterator<int>,         std::ostream_iterator<int>);

HAMON_SIZED_SENTINEL_FOR_TEST(false, int const, int*);
HAMON_SIZED_SENTINEL_FOR_TEST(false, float*,    int*);
HAMON_SIZED_SENTINEL_FOR_TEST(false, bool*,     int*);
HAMON_SIZED_SENTINEL_FOR_TEST(false, void*,     int*);

HAMON_SIZED_SENTINEL_FOR_TEST(false, int*, int[]);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int*, int[2]);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int*, int&);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int*, int const&);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int*, int&&);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int*, int const&&);

HAMON_SIZED_SENTINEL_FOR_TEST(false, int[],       int*);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int[2],      int*);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int&,        int*);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int const&,  int*);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int&&,       int*);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int const&&, int*);

struct Sentinel {};

struct X
{
	friend auto operator++(X&)->X&;
	friend auto operator++(X&, int)->X;
	friend auto operator*(X&) -> int;
	friend bool operator==(const X&, Sentinel);
	friend bool operator!=(const X&, Sentinel);
	friend bool operator==(Sentinel, const X&);
	friend bool operator!=(Sentinel, const X&);
	friend auto operator-(const X&, Sentinel) -> int;
	friend auto operator-(Sentinel, const X&) -> int;
	using difference_type = int;
};
struct Y
{
	friend auto operator++(Y&)->Y&;
	friend auto operator++(Y&, int)->Y;
	friend auto operator*(Y&) -> int;
	friend bool operator==(const Y&, Sentinel);
	friend bool operator!=(const Y&, Sentinel);
	friend bool operator==(Sentinel, const Y&);
	friend bool operator!=(Sentinel, const Y&);
//	friend auto operator-(const Y&, Sentinel) -> int;
	friend auto operator-(Sentinel, const Y&) -> int;
	using difference_type = int;
};
struct Z
{
	friend auto operator++(Z&)->Z&;
	friend auto operator++(Z&, int)->Z;
	friend auto operator*(Z&) -> int;
	friend bool operator==(const Z&, Sentinel);
	friend bool operator!=(const Z&, Sentinel);
	friend bool operator==(Sentinel, const Z&);
	friend bool operator!=(Sentinel, const Z&);
	friend auto operator-(const Z&, Sentinel) -> int;
	friend auto operator-(Sentinel, const Z&) -> int;
	using difference_type = int;
};

}	// namespace sized_sentinel_for_test

}	// namespace hamon_iterator_test

namespace HAMON_DISABLE_SIZED_SENTINEL_FOR_NAMESPACE {

template <>
HAMON_SPECIALIZE_DISABLE_SIZED_SENTINEL_FOR(true,
	hamon_iterator_test::sized_sentinel_for_test::Sentinel,
	hamon_iterator_test::sized_sentinel_for_test::Z);

}

namespace hamon_iterator_test
{

namespace sized_sentinel_for_test
{

HAMON_SIZED_SENTINEL_FOR_TEST(true,  Sentinel, X);
HAMON_SIZED_SENTINEL_FOR_TEST(false, X,        X);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int,      X);
HAMON_SIZED_SENTINEL_FOR_TEST(false, Sentinel, Y);
HAMON_SIZED_SENTINEL_FOR_TEST(false, Y,        Y);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int,      Y);
HAMON_SIZED_SENTINEL_FOR_TEST(false, Sentinel, Z);
HAMON_SIZED_SENTINEL_FOR_TEST(false, Z,        Z);
HAMON_SIZED_SENTINEL_FOR_TEST(false, int,      Z);

}	// namespace sized_sentinel_for_test

}	// namespace hamon_iterator_test

#undef HAMON_SIZED_SENTINEL_FOR_TEST
