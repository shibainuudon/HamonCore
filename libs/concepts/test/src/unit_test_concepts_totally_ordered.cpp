/**
 *	@file	unit_test_concepts_totally_ordered.cpp
 *
 *	@brief	totally_ordered のテスト
 */

#include <hamon/concepts/totally_ordered.hpp>
#include <hamon/config.hpp>

#if HAMON_HAS_INCLUDE(<compare>) && (HAMON_CXX_STANDARD >= 20)
#include <compare>
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_TOTALLY_ORDERED_TEST(B, T)	\
	static_assert(B == hamon::totally_ordered<T>, "");	\
	static_assert(B == hamon::totally_ordered_t<T>::value, "")
#else
#  define HAMON_TOTALLY_ORDERED_TEST(B, T)	\
	static_assert(B == hamon::totally_ordered<T>::value, "");	\
	static_assert(B == hamon::totally_ordered_t<T>::value, "")
#endif

namespace hamon_concepts_test
{

namespace totally_ordered_test
{

HAMON_TOTALLY_ORDERED_TEST(false, void);
HAMON_TOTALLY_ORDERED_TEST(true,  void*);
HAMON_TOTALLY_ORDERED_TEST(true,  float);
HAMON_TOTALLY_ORDERED_TEST(true,  char);
HAMON_TOTALLY_ORDERED_TEST(true,  int);
HAMON_TOTALLY_ORDERED_TEST(true,  int*);
HAMON_TOTALLY_ORDERED_TEST(true,  int&);
HAMON_TOTALLY_ORDERED_TEST(true,  int&&);
HAMON_TOTALLY_ORDERED_TEST(true,  int const);
HAMON_TOTALLY_ORDERED_TEST(true,  int const*);
HAMON_TOTALLY_ORDERED_TEST(true,  int const&);
HAMON_TOTALLY_ORDERED_TEST(true,  int const&&);
HAMON_TOTALLY_ORDERED_TEST(true,  int[]);
HAMON_TOTALLY_ORDERED_TEST(true,  int[2]);
HAMON_TOTALLY_ORDERED_TEST(true,  int());
HAMON_TOTALLY_ORDERED_TEST(true,  int(*)());
HAMON_TOTALLY_ORDERED_TEST(true,  int(&)());

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON) && HAMON_HAS_INCLUDE(<compare>)

struct ordered
{
	friend auto operator<=>(const ordered&, const ordered&) = default;
};

HAMON_TOTALLY_ORDERED_TEST(true,  ordered);

#endif

struct A
{
	bool operator==(const A&) const;
	bool operator!=(const A&) const;
	bool operator< (const A&) const;
	bool operator> (const A&) const;
	bool operator<=(const A&) const;
	bool operator>=(const A&) const;
};
struct B
{
	bool operator==(const B&) const;
	bool operator!=(const B&) const = delete;
	bool operator< (const B&) const;
	bool operator> (const B&) const;
	bool operator<=(const B&) const;
	bool operator>=(const B&) const;
};
struct C
{
	bool operator==(const C&) const;
	bool operator!=(const C&) const;
	void operator< (const C&) const;
	bool operator> (const C&) const;
	bool operator<=(const C&) const;
	bool operator>=(const C&) const;
};
struct D
{
	bool operator==(const D&) const;
	bool operator!=(const D&) const;
	bool operator< (const D&) const;
	bool operator> (const D&) const = delete;
	bool operator<=(const D&) const;
	bool operator>=(const D&) const;
};
struct E
{
	bool operator==(const E&) const;
	bool operator!=(const E&) const;
	bool operator< (const E&) const;
	bool operator> (const E&) const;
	bool operator<=(const E&) const = delete;
	bool operator>=(const E&) const;
};
struct F
{
	bool operator==(const F&) const;
	bool operator!=(const F&) const;
	bool operator< (const F&) const;
	bool operator> (const F&) const;
	bool operator<=(const F&) const;
	void operator>=(const F&) const;
};

HAMON_TOTALLY_ORDERED_TEST(true,  A);
HAMON_TOTALLY_ORDERED_TEST(false, B);
HAMON_TOTALLY_ORDERED_TEST(false, C);
HAMON_TOTALLY_ORDERED_TEST(false, D);
HAMON_TOTALLY_ORDERED_TEST(false, E);
HAMON_TOTALLY_ORDERED_TEST(false, F);

}	// namespace totally_ordered_test

}	// namespace hamon_concepts_test

#undef HAMON_TOTALLY_ORDERED_TEST
