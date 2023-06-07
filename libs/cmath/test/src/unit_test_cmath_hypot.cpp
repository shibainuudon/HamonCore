/**
 *	@file	unit_test_cmath_hypot.cpp
 *
 *	@brief	hypot のテスト
 */

#include <hamon/cmath/hypot.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace hypot_test
{

static_assert(hamon::is_same<float,       decltype(hamon::hypot(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::hypotf(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypotl(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0   , 0   ))>::value, "");

static_assert(hamon::is_same<float,       decltype(hamon::hypot(0.0f, 0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0f, 0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0f, 0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0f, 0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0f, 0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0f, 0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0f, 0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0f, 0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0f, 0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0f, 0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0f, 0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0f, 0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0f, 0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0f, 0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0f, 0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0f, 0   , 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0 , 0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0 , 0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0 , 0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0 , 0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0 , 0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0 , 0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0 , 0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0 , 0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0 , 0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0 , 0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0 , 0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0 , 0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0 , 0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0 , 0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0 , 0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0.0 , 0   , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0   , 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0   , 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0.0l, 0   , 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0   , 0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0   , 0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0   , 0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0   , 0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0   , 0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0   , 0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0   , 0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0   , 0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0   , 0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0   , 0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0   , 0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0   , 0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0   , 0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0   , 0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::hypot(0   , 0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::hypot(0   , 0   , 0   ))>::value, "");

template <typename T>
double get_error();

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<float>()
{
	return 1e-6;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<double>()
{
	return 1e-12;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 1e-12;
}

template <typename T>
void HypotTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0000000000000000000000000000000, (double)hamon::hypot(T( 0.0), T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.5000000000000000000000000000000, (double)hamon::hypot(T( 0.0), T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.5000000000000000000000000000000, (double)hamon::hypot(T( 0.0), T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.5000000000000000000000000000000, (double)hamon::hypot(T( 0.0), T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.5000000000000000000000000000000, (double)hamon::hypot(T( 0.0), T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.5000000000000000000000000000000, (double)hamon::hypot(T( 0.5), T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.7071067811865475244008443621048, (double)hamon::hypot(T( 0.5), T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.7071067811865475244008443621048, (double)hamon::hypot(T( 0.5), T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.5811388300841896659994467722164, (double)hamon::hypot(T( 0.5), T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.5811388300841896659994467722164, (double)hamon::hypot(T( 0.5), T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.5000000000000000000000000000000, (double)hamon::hypot(T(-0.5), T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.7071067811865475244008443621048, (double)hamon::hypot(T(-0.5), T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.7071067811865475244008443621048, (double)hamon::hypot(T(-0.5), T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.5811388300841896659994467722164, (double)hamon::hypot(T(-0.5), T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.5811388300841896659994467722164, (double)hamon::hypot(T(-0.5), T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.5000000000000000000000000000000, (double)hamon::hypot(T( 2.5), T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.5495097567963924150141120545114, (double)hamon::hypot(T( 2.5), T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.5495097567963924150141120545114, (double)hamon::hypot(T( 2.5), T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.9154759474226502354370764387728, (double)hamon::hypot(T( 2.5), T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.9154759474226502354370764387728, (double)hamon::hypot(T( 2.5), T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.5000000000000000000000000000000, (double)hamon::hypot(T(-2.5), T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.5495097567963924150141120545114, (double)hamon::hypot(T(-2.5), T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.5495097567963924150141120545114, (double)hamon::hypot(T(-2.5), T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.9154759474226502354370764387728, (double)hamon::hypot(T(-2.5), T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.9154759474226502354370764387728, (double)hamon::hypot(T(-2.5), T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(303700048.86623412, (double)hamon::hypot(T(214748364), T(214748364)), error*1e8);

	// 余計なオーバーフローを起こさない
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(hamon::hypot(max/2, T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(hamon::hypot(T(100), max/2)));

	// if one of the arguments is ±0, hypot(x,y) is equivalent to fabs called with the non-zero argument
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.0, hamon::hypot(T(+0.0), T( 2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3.0, hamon::hypot(T(-0.0), T( 3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4.0, hamon::hypot(T(+0.0), T(-4.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5.0, hamon::hypot(T(-0.0), T(-5.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max, hamon::hypot(T(+0.0), max));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max, hamon::hypot(T(-0.0), max));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max, hamon::hypot(T(+0.0), lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max, hamon::hypot(T(-0.0), lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.0, hamon::hypot(T( 2.0), T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3.0, hamon::hypot(T( 3.0), T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4.0, hamon::hypot(T(-4.0), T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5.0, hamon::hypot(T(-5.0), T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max, hamon::hypot(max,     T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max, hamon::hypot(max,     T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max, hamon::hypot(lowest,  T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max, hamon::hypot(lowest,  T(-0.0)));

	// if one of the arguments is ±∞, hypot(x,y) returns +∞ even if the other argument is NaN
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(+inf,    T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(-inf,    T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(+inf,    max));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(-inf,    max));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(+inf,    lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(-inf,    lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(+inf,    +nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(-inf,    +nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(+inf,    -nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(-inf,    -nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(T(1.0),  +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(T(1.0),  -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(+nan,    +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(+nan,    -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(-nan,    +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(-nan,    -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(max,     +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(max,     -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(lowest,  +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::hypot(lowest,  -inf));

	// otherwise, if any of the arguments is NaN, NaN is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::hypot(+nan,   T(2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::hypot(-nan,   T(3.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::hypot(T(4.0), +nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::hypot(T(5.0), -nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::hypot(+nan,   +nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::hypot(-nan,   +nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::hypot(+nan,   -nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::hypot(-nan,   -nan)));
}

template <typename T>
void HypotTestInteger(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.0000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.00000000000000000000000000000, hamon::hypot(T(  0), T(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  1.00000000000000000000000000000, hamon::hypot(T(  0), T(  1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  1.00000000000000000000000000000, hamon::hypot(T(  0), T( -1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.00000000000000000000000000000, hamon::hypot(T(  0), T(  2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.00000000000000000000000000000, hamon::hypot(T(  0), T( -2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.00000000000000000000000000000, hamon::hypot(T(  0), T( 99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.00000000000000000000000000000, hamon::hypot(T(  0), T(-99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  1.00000000000000000000000000000, hamon::hypot(T(  1), T(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  1.41421356237309504880168872420, hamon::hypot(T(  1), T(  1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  1.41421356237309504880168872420, hamon::hypot(T(  1), T( -1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.23606797749978969640917366873, hamon::hypot(T(  1), T(  2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.23606797749978969640917366873, hamon::hypot(T(  1), T( -2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.00505037623080771359834335305, hamon::hypot(T(  1), T( 99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.00505037623080771359834335305, hamon::hypot(T(  1), T(-99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  1.00000000000000000000000000000, hamon::hypot(T( -1), T(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  1.41421356237309504880168872420, hamon::hypot(T( -1), T(  1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  1.41421356237309504880168872420, hamon::hypot(T( -1), T( -1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.23606797749978969640917366873, hamon::hypot(T( -1), T(  2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.23606797749978969640917366873, hamon::hypot(T( -1), T( -2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.00505037623080771359834335305, hamon::hypot(T( -1), T( 99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.00505037623080771359834335305, hamon::hypot(T( -1), T(-99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.00000000000000000000000000000, hamon::hypot(T(  2), T(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.23606797749978969640917366873, hamon::hypot(T(  2), T(  1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.23606797749978969640917366873, hamon::hypot(T(  2), T( -1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.82842712474619009760337744841, hamon::hypot(T(  2), T(  2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.82842712474619009760337744841, hamon::hypot(T(  2), T( -2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.02019995940222297244309999586, hamon::hypot(T(  2), T( 99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.02019995940222297244309999586, hamon::hypot(T(  2), T(-99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.00000000000000000000000000000, hamon::hypot(T( -2), T(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.23606797749978969640917366873, hamon::hypot(T( -2), T(  1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.23606797749978969640917366873, hamon::hypot(T( -2), T( -1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.82842712474619009760337744841, hamon::hypot(T( -2), T(  2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.82842712474619009760337744841, hamon::hypot(T( -2), T( -2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.02019995940222297244309999586, hamon::hypot(T( -2), T( 99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.02019995940222297244309999586, hamon::hypot(T( -2), T(-99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.00000000000000000000000000000, hamon::hypot(T( 99), T(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.00505037623080771359834335305, hamon::hypot(T( 99), T(  1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.00505037623080771359834335305, hamon::hypot(T( 99), T( -1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.02019995940222297244309999586, hamon::hypot(T( 99), T(  2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.02019995940222297244309999586, hamon::hypot(T( 99), T( -2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(140.00714267493640983136718369676, hamon::hypot(T( 99), T( 99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(140.00714267493640983136718369676, hamon::hypot(T( 99), T(-99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.00000000000000000000000000000, hamon::hypot(T(-99), T(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.00505037623080771359834335305, hamon::hypot(T(-99), T(  1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.00505037623080771359834335305, hamon::hypot(T(-99), T( -1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.02019995940222297244309999586, hamon::hypot(T(-99), T(  2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.02019995940222297244309999586, hamon::hypot(T(-99), T( -2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(140.00714267493640983136718369676, hamon::hypot(T(-99), T( 99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(140.00714267493640983136718369676, hamon::hypot(T(-99), T(-99)), error);
}

template <typename T>
void Hypot3TestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto max = std::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0,                         (double)hamon::hypot(T( 0.0), T( 0.0), T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)hamon::sqrt(T(2.0)), (double)hamon::hypot(T( 0.0), T( 1.0), T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)hamon::sqrt(T(2.0)), (double)hamon::hypot(T( 0.0), T( 1.0), T(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)hamon::sqrt(T(3.0)), (double)hamon::hypot(T( 1.0), T( 1.0), T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)hamon::sqrt(T(3.0)), (double)hamon::hypot(T(-1.0), T(-1.0), T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.0,                         (double)hamon::hypot(T( 1.0), T( 2.0), T( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(7.0,                         (double)hamon::hypot(T( 2.0), T( 3.0), T( 6.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(9.0,                         (double)hamon::hypot(T( 1.0), T( 4.0), T( 8.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(9.0,                         (double)hamon::hypot(T( 4.0), T( 4.0), T( 7.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(9.0,                         (double)hamon::hypot(T(-4.0), T(-4.0), T(-7.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(29.0,                        (double)hamon::hypot(T(12.0), T(16.0), T(21.0)), error*1e1);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1e8,                         (double)hamon::hypot(T(1e8),  T( 1.0), T(1e-8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.01000099995,               (double)hamon::hypot(T(1e-2), T(1e-4), T(1e-4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(371955077.2902952,           (double)hamon::hypot(T(214748364), T(214748364), T(214748364)), error*1e8);

	// 余計なオーバーフローを起こさない
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(hamon::hypot(max/2, T(1), T(2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(hamon::hypot(T(100), max/2, T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(hamon::hypot(T(1), T(100), max/2)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(+inf, +inf, +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(+inf, +inf, -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(+inf, +inf, T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(+inf, +inf, nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(+inf, -inf, +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(+inf, -inf, -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(+inf, -inf, T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(+inf, -inf, nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(+inf, T(1), +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(+inf, T(1), -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(+inf, T(1), T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(+inf, T(1), nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(+inf, nan,  +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(+inf, nan,  -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(+inf, nan,  T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(+inf, nan,  nan));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(-inf, +inf, +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(-inf, +inf, -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(-inf, +inf, T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(-inf, +inf, nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(-inf, -inf, +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(-inf, -inf, -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(-inf, -inf, T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(-inf, -inf, nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(-inf, T(1), +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(-inf, T(1), -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(-inf, T(1), T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(-inf, T(1), nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(-inf, nan,  +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(-inf, nan,  -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(-inf, nan,  T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::hypot(-inf, nan,  nan));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(T(1), +inf, +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(T(1), +inf, -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(T(1), +inf, T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(T(1), +inf, nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(T(1), -inf, +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(T(1), -inf, -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(T(1), -inf, T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(T(1), -inf, nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(T(1), T(1), +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(T(1), T(1), -inf));
//	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(T(1), T(1), T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::hypot(T(1), T(1), nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(T(1), nan,  +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(T(1), nan,  -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::hypot(T(1), nan,  T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::hypot(T(1), nan,  nan)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(nan, +inf, +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(nan, +inf, -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(nan, +inf, T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(nan, +inf, nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(nan, -inf, +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(nan, -inf, -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(nan, -inf, T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(nan, -inf, nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(nan, T(1), +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(nan, T(1), -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::hypot(nan, T(1), T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::hypot(nan, T(1), nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(nan, nan,  +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,          hamon::hypot(nan, nan,  -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::hypot(nan, nan,  T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::hypot(nan, nan,  nan)));
}

template <typename T>
void Hypot3TestInteger(void)
{
	HAMON_CXX11_CONSTEXPR double error = 1e-12;

	HAMON_CXX11_CONSTEXPR auto max = std::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0,              hamon::hypot(T( 0), T( 0), T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(hamon::sqrt(2.0), hamon::hypot(T( 1), T( 0), T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(hamon::sqrt(3.0), hamon::hypot(T(-1), T(-1), T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(7.0,              hamon::hypot(T( 2), T( 3), T( 6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)max,      hamon::hypot(T( 0), T( 0), max),   error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)max,      hamon::hypot(T( 0), max,   T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)max,      hamon::hypot(max,   T( 0), T( 0)), error);
}

GTEST_TEST(CMathTest, HypotTest)
{
	HypotTestFloat<float>();
	HypotTestFloat<double>();
	HypotTestFloat<long double>();

	HypotTestInteger<short>();
	HypotTestInteger<int>();
	HypotTestInteger<long>();
	HypotTestInteger<long long>();

	Hypot3TestFloat<float>();
	Hypot3TestFloat<double>();
	Hypot3TestFloat<long double>();

	Hypot3TestInteger<short>();
	Hypot3TestInteger<int>();
	Hypot3TestInteger<long>();
	Hypot3TestInteger<long long>();
}

}	// namespace hypot_test

}	// namespace hamon_cmath_test
