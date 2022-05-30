/**
 *	@file	unit_test_concepts_floating_point.cpp
 *
 *	@brief	floating_point のテスト
 */

#include <hamon/concepts/floating_point.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_FLOATING_POINT_TEST(B, T)	\
	static_assert(B == hamon::floating_point<T>, "");	\
	static_assert(B == hamon::floating_point_t<T>::value, "")
#else
#  define HAMON_FLOATING_POINT_TEST(B, T)	\
	static_assert(B == hamon::floating_point<T>::value, "");	\
	static_assert(B == hamon::floating_point_t<T>::value, "")
#endif

namespace hamon_concepts_test
{

namespace floating_point_test
{

HAMON_FLOATING_POINT_TEST(true,  float);
HAMON_FLOATING_POINT_TEST(true,  double);
HAMON_FLOATING_POINT_TEST(true,  long double);

HAMON_FLOATING_POINT_TEST(false, char);
HAMON_FLOATING_POINT_TEST(false, signed char);
HAMON_FLOATING_POINT_TEST(false, bool);
HAMON_FLOATING_POINT_TEST(false, int);
HAMON_FLOATING_POINT_TEST(false, char32_t);

HAMON_FLOATING_POINT_TEST(false, void);
HAMON_FLOATING_POINT_TEST(false, float*);
HAMON_FLOATING_POINT_TEST(false, float&);
HAMON_FLOATING_POINT_TEST(false, float&&);
HAMON_FLOATING_POINT_TEST(false, const float&);
HAMON_FLOATING_POINT_TEST(false, float[]);
HAMON_FLOATING_POINT_TEST(false, float[2]);
HAMON_FLOATING_POINT_TEST(false, float());
HAMON_FLOATING_POINT_TEST(false, float(*)());
HAMON_FLOATING_POINT_TEST(false, float(&)());

enum E { };
HAMON_FLOATING_POINT_TEST(false, E);
enum class CE { };
HAMON_FLOATING_POINT_TEST(false, CE);
struct A { };
HAMON_FLOATING_POINT_TEST(false, A);
union B { };
HAMON_FLOATING_POINT_TEST(false, B);

}	// namespace floating_point_test

}	// namespace hamon_concepts_test

#undef HAMON_FLOATING_POINT_TEST
