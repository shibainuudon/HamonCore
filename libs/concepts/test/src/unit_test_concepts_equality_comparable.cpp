/**
 *	@file	unit_test_concepts_equality_comparable.cpp
 *
 *	@brief	equality_comparable のテスト
 */

#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_EQUALITY_COMPARABLE_TEST(B, T)	\
	static_assert(B == hamon::equality_comparable<T>, "");	\
	static_assert(B == hamon::equality_comparable_t<T>::value, "")
#else
#  define HAMON_EQUALITY_COMPARABLE_TEST(B, T)	\
	static_assert(B == hamon::equality_comparable<T>::value, "");	\
	static_assert(B == hamon::equality_comparable_t<T>::value, "")
#endif

namespace hamon_concepts_test
{

namespace equality_comparable_test
{

HAMON_EQUALITY_COMPARABLE_TEST(false, void);
HAMON_EQUALITY_COMPARABLE_TEST(true,  void*);
HAMON_EQUALITY_COMPARABLE_TEST(true,  float);
HAMON_EQUALITY_COMPARABLE_TEST(true,  char);
HAMON_EQUALITY_COMPARABLE_TEST(true,  int);
HAMON_EQUALITY_COMPARABLE_TEST(true,  int*);
HAMON_EQUALITY_COMPARABLE_TEST(true,  int&);
HAMON_EQUALITY_COMPARABLE_TEST(true,  int&&);
HAMON_EQUALITY_COMPARABLE_TEST(true,  int const);
HAMON_EQUALITY_COMPARABLE_TEST(true,  int const*);
HAMON_EQUALITY_COMPARABLE_TEST(true,  int const&);
HAMON_EQUALITY_COMPARABLE_TEST(true,  int const&&);
HAMON_EQUALITY_COMPARABLE_TEST(true,  int[]);
HAMON_EQUALITY_COMPARABLE_TEST(true,  int[2]);
HAMON_EQUALITY_COMPARABLE_TEST(true,  int());
HAMON_EQUALITY_COMPARABLE_TEST(true,  int(*)());
HAMON_EQUALITY_COMPARABLE_TEST(true,  int(&)());

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

struct eq_comp
{
	friend bool operator==(const eq_comp&, const eq_comp&) = default;
};
HAMON_EQUALITY_COMPARABLE_TEST(true,  eq_comp);

#endif

struct not_eq_comp
{
	friend bool operator==(const not_eq_comp&, const not_eq_comp&) = delete;
};
HAMON_EQUALITY_COMPARABLE_TEST(false, not_eq_comp);

struct A
{
	friend bool operator==(const A&, const A&);
	friend bool operator!=(const A&, const A&);
};
struct B
{
	friend bool operator==(const B&, const B&) = delete;
	friend bool operator!=(const B&, const B&);
};
struct C
{
	friend bool operator==(const C&, const C&);
	friend bool operator!=(const C&, const C&) = delete;
};
HAMON_EQUALITY_COMPARABLE_TEST(true,  A);
HAMON_EQUALITY_COMPARABLE_TEST(false, B);
HAMON_EQUALITY_COMPARABLE_TEST(false, C);

}	// namespace equality_comparable_test

}	// namespace hamon_concepts_test

#undef HAMON_EQUALITY_COMPARABLE_TEST
