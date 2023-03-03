/**
 *	@file	unit_test_units_user_defined.cpp
 *
 *	@brief	ユーザー定義の単位のテスト
 */

#include <hamon/units/metre.hpp>
#include <hamon/units/second.hpp>
#include <hamon/units/acceleration.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <ratio>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace units_test
{

namespace user_defined_test
{

// (1)既存の単位とスケールの組み合わせ
// 尺(10/33 m)
template <typename T>
using shaku = decltype(hamon::units::metre<T>() * std::ratio<10, 33>());

// (2)既存の単位の乗算で新たな次元の単位を作る
// 躍度(jerk) - メートル毎秒毎秒毎秒
template <typename T>
using meter_per_cubic_second =
	decltype(hamon::units::metre<T>() / hamon::units::second<T>() / hamon::units::second<T>() / hamon::units::second<T>());

// (3)新たな次元の単位を作る
// 通貨
struct currency_dimension_tag;
using currency_dimension =
	hamon::units::derived_dimension<
		hamon::units::dimension_holder<currency_dimension_tag>
	>;
// ドル
template <typename T>
using dollar = hamon::units::quantity<T, currency_dimension>;
// 円
#if 1
template <typename T>
using yen = decltype(dollar<T>() * std::ratio<1, 134>());
#else
// こう書いても同じ
template <typename T>
using yen = hamon::units::quantity<T, currency_dimension, std::ratio<1, 134>>;
#endif

GTEST_TEST(UnitsTest, UserDefinedTest)
{
	using T = double;
	HAMON_CXX11_CONSTEXPR double error = 0.000000000000001;

	// (1)
	{
		HAMON_CXX11_CONSTEXPR hamon::units::metre<T> m{1};
		HAMON_CXX11_CONSTEXPR shaku<T> s{m};
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.3, s.value(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR shaku<T> s{1};
		HAMON_CXX11_CONSTEXPR hamon::units::metre<T> m{s};
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.3030303030303030303, m.value(), error);
	}

	// (2)
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::units::metres_per_second_squared<T>(10) / hamon::units::seconds<T>(2);
		static_assert(hamon::is_same<decltype(x), const meter_per_cubic_second<T>>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, x.value());
	}
	{
		HAMON_CXX11_CONSTEXPR auto s = hamon::units::seconds<T>(10);
		HAMON_CXX11_CONSTEXPR auto x = hamon::units::metres<T>(20000) / s / s / s;
		static_assert(hamon::is_same<decltype(x), const meter_per_cubic_second<T>>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, x.value());
	}

	// (3)
	{
		HAMON_CXX11_CONSTEXPR dollar<T> d{42};
		HAMON_CXX11_CONSTEXPR yen<T> y{d};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5628, y.value());
	}
	{
		HAMON_CXX11_CONSTEXPR yen<T> y{17000};
		HAMON_CXX11_CONSTEXPR dollar<T> d{y};
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(126.86567164179104, d.value(), error);
	}
}

}	// namespace user_defined_test

}	// namespace units_test
