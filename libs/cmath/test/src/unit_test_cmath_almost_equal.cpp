/**
 *	@file	unit_test_cmath_almost_equal.cpp
 *
 *	@brief	almost_equal のテスト
 */

#include <hamon/cmath/almost_equal.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <limits>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace almost_equal_test
{

static_assert(hamon::is_same<bool, decltype(hamon::almost_equal(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::almost_equal(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::almost_equal(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::almost_equal(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::almost_equal(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::almost_equal(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::almost_equal(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::almost_equal(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::almost_equal(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::almost_equal(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::almost_equal(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::almost_equal(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::almost_equal(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::almost_equal(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::almost_equal(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::almost_equal(0   , 0   ))>::value, "");

template <typename T>
void AlmostEqualTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();
	HAMON_CXX11_CONSTEXPR auto eps    = std::numeric_limits<T>::epsilon();

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(0.0) + (eps * T(0)), T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(0.0) + (eps * T(1)), T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(0.0) + (eps * T(2)), T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(0.0) - (eps * T(0)), T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(0.0) - (eps * T(1)), T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(0.0) - (eps * T(2)), T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(0.0),                T(0.0) + (eps * T(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(0.0),                T(0.0) + (eps * T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(0.0),                T(0.0) + (eps * T(2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(0.0),                T(0.0) - (eps * T(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(0.0),                T(0.0) - (eps * T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(0.0),                T(0.0) - (eps * T(2))));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(1.0) + (eps * T(0)), T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(1.0) + (eps * T(1)), T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(1.0) + (eps * T(2)), T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(1.0) - (eps * T(0)), T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(1.0) - (eps * T(1)), T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(1.0) - (eps * T(2)), T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(1.0),                T(1.0) + (eps * T(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(1.0),                T(1.0) + (eps * T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(1.0),                T(1.0) + (eps * T(2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(1.0),                T(1.0) - (eps * T(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(1.0),                T(1.0) - (eps * T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(1.0),                T(1.0) - (eps * T(2))));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-1.0) + (eps * T(0)), T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-1.0) + (eps * T(1)), T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(-1.0) + (eps * T(2)), T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-1.0) - (eps * T(0)), T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-1.0) - (eps * T(1)), T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(-1.0) - (eps * T(2)), T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-1.0),                T(-1.0) + (eps * T(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-1.0),                T(-1.0) + (eps * T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(-1.0),                T(-1.0) + (eps * T(2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-1.0),                T(-1.0) - (eps * T(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-1.0),                T(-1.0) - (eps * T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(-1.0),                T(-1.0) - (eps * T(2))));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(2.0) + (eps * T(0)), T(2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(2.0) + (eps * T(1)), T(2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(2.0) + (eps * T(2)), T(2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(2.0) + (eps * T(3)), T(2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(2.0) - (eps * T(0)), T(2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(2.0) - (eps * T(1)), T(2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(2.0) - (eps * T(2)), T(2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(2.0) - (eps * T(3)), T(2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(2.0),                T(2.0) + (eps * T(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(2.0),                T(2.0) + (eps * T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(2.0),                T(2.0) + (eps * T(2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(2.0),                T(2.0) + (eps * T(3))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(2.0),                T(2.0) - (eps * T(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(2.0),                T(2.0) - (eps * T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(2.0),                T(2.0) - (eps * T(2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(2.0),                T(2.0) - (eps * T(3))));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-2.0) + (eps * T(0)), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-2.0) + (eps * T(1)), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-2.0) + (eps * T(2)), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(-2.0) + (eps * T(3)), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-2.0) - (eps * T(0)), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-2.0) - (eps * T(1)), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-2.0) - (eps * T(2)), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(-2.0) - (eps * T(3)), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-2.0),                T(-2.0) + (eps * T(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-2.0),                T(-2.0) + (eps * T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-2.0),                T(-2.0) + (eps * T(2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(-2.0),                T(-2.0) + (eps * T(3))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-2.0),                T(-2.0) - (eps * T(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-2.0),                T(-2.0) - (eps * T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-2.0),                T(-2.0) - (eps * T(2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(-2.0),                T(-2.0) - (eps * T(3))));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(10.0) + (eps * T(11)), T(10.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(10.0) + (eps * T(12)), T(10.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(10.0) - (eps * T(11)), T(10.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(10.0) - (eps * T(12)), T(10.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(10.0),                 T(10.0) + (eps * T(11))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(10.0),                 T(10.0) + (eps * T(12))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(10.0),                 T(10.0) - (eps * T(11))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(10.0),                 T(10.0) - (eps * T(12))));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(nan, T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(nan, T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(nan, max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(nan, min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(nan, lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(nan,  nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(nan, -nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(nan,  inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(nan, -inf));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-nan, T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-nan, T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-nan, max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-nan, min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-nan, lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-nan,  nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-nan, -nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-nan,  inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-nan, -inf));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(inf, T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(inf, T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(inf, max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(inf, min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(inf, lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(inf,  nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(inf, -nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(inf,  inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(inf, -inf));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-inf, T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-inf, T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-inf, max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-inf, min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-inf, lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-inf,  nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-inf, -nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(-inf,  inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(-inf, -inf));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(max, T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(max, T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(max, max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(max, min));
	                      EXPECT_FALSE(hamon::almost_equal(max, lowest));		// TODO 計算途中でinfが発生しないようにして、constexprにする
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(max,  nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(max, -nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(max,  inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(max, -inf));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(min, T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(min, T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(min, max));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(min, min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(min, lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(min,  nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(min, -nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(min,  inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(min, -inf));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(lowest, T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(lowest, T(1.0)));
	                      EXPECT_FALSE(hamon::almost_equal(lowest, max));		// TODO 計算途中でinfが発生しないようにして、constexprにする
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(lowest, min));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(lowest, lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(lowest,  nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(lowest, -nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(lowest,  inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(lowest, -inf));
}

template <typename T>
void AlmostEqualTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR auto max = std::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min = std::numeric_limits<T>::min();

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(0), T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(0), T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(0), T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(0), max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(0), min));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(1), T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(1), T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(1), T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(1), max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(1), min));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(-1), T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(-1), T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(-1), T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(-1), max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(-1), min));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(max, T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(max, T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(max, T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(max, max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(max, min));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(min, T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(min, T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(min, T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(min, max));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(min, min));
}

template <typename T>
void AlmostEqualTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR auto max = std::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min = std::numeric_limits<T>::min();

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(0), T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(0), T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(0), max));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(0), min));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(1), T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(T(1), T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(1), max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(T(1), min));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(max, T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(max, T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(max, max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(max, min));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(min, T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(min, T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::almost_equal(min, max));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::almost_equal(min, min));
}

GTEST_TEST(CMathTest, AlmostEqualTest)
{
	AlmostEqualTestFloat<float>();
	AlmostEqualTestFloat<double>();
	AlmostEqualTestFloat<long double>();

	AlmostEqualTestSignedInt<int>();
	AlmostEqualTestSignedInt<signed char>();
//	AlmostEqualTestSignedInt<short>();
	AlmostEqualTestSignedInt<long>();
//	AlmostEqualTestSignedInt<long long>();

	AlmostEqualTestUnsignedInt<unsigned int>();
//	AlmostEqualTestUnsignedInt<unsigned char>();
	AlmostEqualTestUnsignedInt<unsigned short>();
//	AlmostEqualTestUnsignedInt<unsigned long>();
	AlmostEqualTestUnsignedInt<unsigned long long>();
}

}	// namespace almost_equal_test

}	// namespace hamon_cmath_test
