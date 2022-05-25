/**
 *	@file	unit_test_concepts_swappable.cpp
 *
 *	@brief	swappable のテスト
 */

#include <hamon/concepts/swappable.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_SWAPPABLE_TEST(B, T)	\
	static_assert(B == hamon::swappable<T>, "");	\
	static_assert(B == hamon::swappable_t<T>::value, "")
#else
#  define HAMON_SWAPPABLE_TEST(B, T)	\
	static_assert(B == hamon::swappable<T>::value, "");	\
	static_assert(B == hamon::swappable_t<T>::value, "")
#endif

namespace hamon_concepts_test
{

namespace swappable_test
{

struct S { bool swapped = false; };
HAMON_CXX14_CONSTEXPR void swap(S&, S&) { }

struct T { int i; };

union U { char c; int i; };
HAMON_CXX14_CONSTEXPR void swap(U&, U&) { }

HAMON_SWAPPABLE_TEST(true,  S);
HAMON_SWAPPABLE_TEST(false, S const);
HAMON_SWAPPABLE_TEST(true,  T);
HAMON_SWAPPABLE_TEST(false, T const);
HAMON_SWAPPABLE_TEST(true,  U);
HAMON_SWAPPABLE_TEST(false, U const);

}	// namespace swappable_test

}	// namespace hamon_concepts_test

#undef HAMON_SWAPPABLE_TEST
