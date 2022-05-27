/**
 *	@file	unit_test_concepts_regular.cpp
 *
 *	@brief	regular のテスト
 */

#include <hamon/concepts/regular.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_REGULAR_TEST(B, T)	\
	static_assert(B == hamon::regular<T>, "");	\
	static_assert(B == hamon::regular_t<T>::value, "")
#else
#  define HAMON_REGULAR_TEST(B, T)	\
	static_assert(B == hamon::regular<T>::value, "");	\
	static_assert(B == hamon::regular_t<T>::value, "")
#endif

namespace hamon_concepts_test
{

namespace regular_test
{

HAMON_REGULAR_TEST(true,  int);
HAMON_REGULAR_TEST(true,  int*);
HAMON_REGULAR_TEST(false, int&);
HAMON_REGULAR_TEST(false, void);
HAMON_REGULAR_TEST(false, void());
HAMON_REGULAR_TEST(false, void() noexcept);
HAMON_REGULAR_TEST(false, void() const);

struct Trivial { };
HAMON_REGULAR_TEST(false, Trivial);

struct NotTrivial
{
	NotTrivial() { }
	~NotTrivial() { }
};
HAMON_REGULAR_TEST(false, NotTrivial);

struct NotDefaultConstructible
{
	NotDefaultConstructible(int) { }
};
HAMON_REGULAR_TEST(false, NotDefaultConstructible);

struct HasReference
{
	int& ref;
};
HAMON_REGULAR_TEST(false, HasReference);

struct HasEq { };
bool operator==(HasEq, HasEq) { return true; }
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
HAMON_REGULAR_TEST(true,  HasEq);
#else
//HAMON_REGULAR_TEST(false, HasEq);
#endif

struct HasEqNeq { };
bool operator==(HasEqNeq, HasEqNeq) { return true; }
bool operator!=(HasEqNeq, HasEqNeq) { return false; }
HAMON_REGULAR_TEST(true,  HasEqNeq);

}	// namespace regular_test

}	// namespace hamon_concepts_test

#undef HAMON_REGULAR_TEST
