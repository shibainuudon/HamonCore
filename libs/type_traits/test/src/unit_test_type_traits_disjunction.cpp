/**
 *	@file	unit_test_type_traits_disjunction.cpp
 *
 *	@brief	disjunction のテスト
 */

#include <hamon/type_traits/disjunction.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon_type_traits_test
{

namespace disjunction_test
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_DISJUNCTION_TEST(x, ...)	\
	static_assert(hamon::disjunction_v<__VA_ARGS__>      == x, "");	\
	static_assert(hamon::disjunction<__VA_ARGS__>::value == x, "");	\
	static_assert(hamon::disjunction<__VA_ARGS__>()      == x, "")

#else

#define HAMON_DISJUNCTION_TEST(x, ...)	\
	static_assert(hamon::disjunction<__VA_ARGS__>::value == x, "");	\
	static_assert(hamon::disjunction<__VA_ARGS__>()      == x, "")

#endif

using T = std::true_type;
using F = std::false_type;

HAMON_DISJUNCTION_TEST(false, /**/);

HAMON_DISJUNCTION_TEST(true,  T);
HAMON_DISJUNCTION_TEST(false, F);

HAMON_DISJUNCTION_TEST(true,  T, T);
HAMON_DISJUNCTION_TEST(true,  T, F);
HAMON_DISJUNCTION_TEST(true,  F, T);
HAMON_DISJUNCTION_TEST(false, F, F);

HAMON_DISJUNCTION_TEST(true,  T, T, T);
HAMON_DISJUNCTION_TEST(true,  T, T, F);
HAMON_DISJUNCTION_TEST(true,  T, F, T);
HAMON_DISJUNCTION_TEST(true,  T, F, F);
HAMON_DISJUNCTION_TEST(true,  F, T, T);
HAMON_DISJUNCTION_TEST(true,  F, T, F);
HAMON_DISJUNCTION_TEST(true,  F, F, T);
HAMON_DISJUNCTION_TEST(false, F, F, F);

HAMON_DISJUNCTION_TEST(true,  T, T, T, T, T, T, T, T, T, T);
HAMON_DISJUNCTION_TEST(true,  F, T, T, T, T, T, T, T, T, T);
HAMON_DISJUNCTION_TEST(true,  T, F, T, T, T, T, T, T, T, T);
HAMON_DISJUNCTION_TEST(true,  T, T, F, T, T, T, T, T, T, T);
HAMON_DISJUNCTION_TEST(true,  T, T, T, F, T, T, T, T, T, T);
HAMON_DISJUNCTION_TEST(true,  T, T, T, T, F, T, T, T, T, T);
HAMON_DISJUNCTION_TEST(true,  T, T, T, T, T, F, T, T, T, T);
HAMON_DISJUNCTION_TEST(true,  T, T, T, T, T, T, F, T, T, T);
HAMON_DISJUNCTION_TEST(true,  T, T, T, T, T, T, T, F, T, T);
HAMON_DISJUNCTION_TEST(true,  T, T, T, T, T, T, T, T, F, T);
HAMON_DISJUNCTION_TEST(true,  T, T, T, T, T, T, T, T, T, F);
HAMON_DISJUNCTION_TEST(true,  T, F, F, F, F, F, F, F, F, F);
HAMON_DISJUNCTION_TEST(true,  F, T, F, F, F, F, F, F, F, F);
HAMON_DISJUNCTION_TEST(true,  F, F, T, F, F, F, F, F, F, F);
HAMON_DISJUNCTION_TEST(true,  F, F, F, T, F, F, F, F, F, F);
HAMON_DISJUNCTION_TEST(true,  F, F, F, F, T, F, F, F, F, F);
HAMON_DISJUNCTION_TEST(true,  F, F, F, F, F, T, F, F, F, F);
HAMON_DISJUNCTION_TEST(true,  F, F, F, F, F, F, T, F, F, F);
HAMON_DISJUNCTION_TEST(true,  F, F, F, F, F, F, F, T, F, F);
HAMON_DISJUNCTION_TEST(true,  F, F, F, F, F, F, F, F, T, F);
HAMON_DISJUNCTION_TEST(true,  F, F, F, F, F, F, F, F, F, T);
HAMON_DISJUNCTION_TEST(false, F, F, F, F, F, F, F, F, F, F);

static_assert(
	hamon::disjunction<
		// 0
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 100
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
#if 0
		// 200
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 300
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 400
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 500
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 600
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 700
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 800
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 900
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
#endif

		T
	>::value, "");

static_assert(
	!hamon::disjunction<
		// 0
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 100
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
#if 0
		// 200
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 300
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 400
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 500
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 600
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 700
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 800
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 900
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
#endif

		F
	>::value, "");

#undef HAMON_DISJUNCTION_TEST

}	// namespace disjunction_test

}	// namespace hamon_type_traits_test
