/**
 *	@file	unit_test_units_quantity.cpp
 *
 *	@brief	quantity のテスト
 */

#include <hamon/units/quantity.hpp>
#include <hamon/units/base_dimensions/length.hpp>
#include <hamon/units/base_dimensions/mass.hpp>
#include <hamon/units/base_dimensions/time.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_implicitly_copy_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include <ratio>
#include <sstream>
#include "constexpr_test.hpp"

namespace units_quantity_test
{

template <typename T>
class QuantityTest : public ::testing::Test {};

using QuantityTestTypes = ::testing::Types<float, double, long double>;

TYPED_TEST_SUITE(QuantityTest, QuantityTestTypes);

TYPED_TEST(QuantityTest, DefaultConstructTest)
{
	using T = TypeParam;
	{
		using D = hamon::units::length_dimension;
		using Q = hamon::units::quantity<T, D>;
		static_assert(hamon::is_default_constructible<Q>::value, "");
		static_assert(hamon::is_nothrow_default_constructible<Q>::value, "");
		static_assert(hamon::is_implicitly_default_constructible<Q>::value, "");
		HAMON_CONSTEXPR Q q;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q.value());
	}
	{
		using D = hamon::units::mass_dimension;
		using Q = hamon::units::quantity<T, D>;
		static_assert(hamon::is_default_constructible<Q>::value, "");
		static_assert(hamon::is_nothrow_default_constructible<Q>::value, "");
		static_assert(hamon::is_implicitly_default_constructible<Q>::value, "");
		HAMON_CONSTEXPR Q q{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q.value());
	}
	{
		using D = hamon::units::length_dimension;
		using S = std::ratio<1000, 1>;
		using Q = hamon::units::quantity<T, D, S>;
		static_assert(hamon::is_default_constructible<Q>::value, "");
		static_assert(hamon::is_nothrow_default_constructible<Q>::value, "");
		static_assert(hamon::is_implicitly_default_constructible<Q>::value, "");
		HAMON_CONSTEXPR Q q = {};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q.value());
	}
	{
		using D = hamon::units::mass_dimension;
		using S = std::ratio<1, 1000>;
		using Q = hamon::units::quantity<T, D, S>;
		static_assert(hamon::is_default_constructible<Q>::value, "");
		static_assert(hamon::is_nothrow_default_constructible<Q>::value, "");
		static_assert(hamon::is_implicitly_default_constructible<Q>::value, "");
		HAMON_CONSTEXPR Q q;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q.value());
	}
	{
		using D = hamon::units::length_dimension;
		using S = std::ratio<1000, 1>;
		using O = std::ratio<100, 3>;
		using Q = hamon::units::quantity<T, D, S, O>;
		static_assert(hamon::is_default_constructible<Q>::value, "");
		static_assert(hamon::is_nothrow_default_constructible<Q>::value, "");
		static_assert(hamon::is_implicitly_default_constructible<Q>::value, "");
		HAMON_CONSTEXPR Q q;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q.value());
	}
}

TYPED_TEST(QuantityTest, ValueConstructTest)
{
	using T = TypeParam;
	{
		using D = hamon::units::length_dimension;
		using Q = hamon::units::quantity<T, D>;
		static_assert(hamon::is_constructible<Q, T>::value, "");
		static_assert(hamon::is_nothrow_constructible<Q, T>::value, "");
		static_assert(!hamon::is_implicitly_constructible<Q, T>::value, "");
		HAMON_CONSTEXPR Q q(1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, q.value());
	}
	{
		using D = hamon::units::mass_dimension;
		using Q = hamon::units::quantity<T, D>;
		static_assert(hamon::is_constructible<Q, T>::value, "");
		static_assert(hamon::is_nothrow_constructible<Q, T>::value, "");
		static_assert(!hamon::is_implicitly_constructible<Q, T>::value, "");
		HAMON_CONSTEXPR Q q{2};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, q.value());
	}
	{
		using D = hamon::units::length_dimension;
		using S = std::ratio<1000, 1>;
		using Q = hamon::units::quantity<T, D, S>;
		static_assert(hamon::is_constructible<Q, T>::value, "");
		static_assert(hamon::is_nothrow_constructible<Q, T>::value, "");
		static_assert(!hamon::is_implicitly_constructible<Q, T>::value, "");
		HAMON_CONSTEXPR Q q{3};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, q.value());
	}
	{
		using D = hamon::units::mass_dimension;
		using S = std::ratio<1, 1000>;
		using Q = hamon::units::quantity<T, D, S>;
		static_assert(hamon::is_constructible<Q, T>::value, "");
		static_assert(hamon::is_nothrow_constructible<Q, T>::value, "");
		static_assert(!hamon::is_implicitly_constructible<Q, T>::value, "");
		HAMON_CONSTEXPR Q q(4);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, q.value());
	}
	{
		using D = hamon::units::length_dimension;
		using S = std::ratio<1000, 1>;
		using O = std::ratio<100, 3>;
		using Q = hamon::units::quantity<T, D, S, O>;
		static_assert(hamon::is_constructible<Q, T>::value, "");
		static_assert(hamon::is_nothrow_constructible<Q, T>::value, "");
		static_assert(!hamon::is_implicitly_constructible<Q, T>::value, "");
		HAMON_CONSTEXPR Q q{5};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, q.value());
	}
}

TYPED_TEST(QuantityTest, CopyConstructTest)
{
	using T = TypeParam;
	{
		using D = hamon::units::length_dimension;
		using Q = hamon::units::quantity<T, D>;
		static_assert(hamon::is_copy_constructible<Q>::value, "");
		static_assert(hamon::is_nothrow_copy_constructible<Q>::value, "");
		static_assert(hamon::is_implicitly_copy_constructible<Q>::value, "");
		HAMON_CONSTEXPR Q q1(1);
		HAMON_CONSTEXPR Q q2{q1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, q2.value());
	}
	{
		using D = hamon::units::mass_dimension;
		using Q = hamon::units::quantity<T, D>;
		static_assert(hamon::is_copy_constructible<Q>::value, "");
		static_assert(hamon::is_nothrow_copy_constructible<Q>::value, "");
		static_assert(hamon::is_implicitly_copy_constructible<Q>::value, "");
		HAMON_CONSTEXPR Q q1{2};
		HAMON_CONSTEXPR Q q2(q1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, q2.value());
	}
	{
		using D = hamon::units::length_dimension;
		using S = std::ratio<1000, 1>;
		using Q = hamon::units::quantity<T, D, S>;
		static_assert(hamon::is_copy_constructible<Q>::value, "");
		static_assert(hamon::is_nothrow_copy_constructible<Q>::value, "");
		static_assert(hamon::is_implicitly_copy_constructible<Q>::value, "");
		HAMON_CONSTEXPR Q q1(3);
		HAMON_CONSTEXPR Q q2(q1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, q2.value());
	}
	{
		using D = hamon::units::mass_dimension;
		using S = std::ratio<1, 1000>;
		using Q = hamon::units::quantity<T, D, S>;
		static_assert(hamon::is_copy_constructible<Q>::value, "");
		static_assert(hamon::is_nothrow_copy_constructible<Q>::value, "");
		static_assert(hamon::is_implicitly_copy_constructible<Q>::value, "");
		HAMON_CONSTEXPR Q q1{4};
		HAMON_CONSTEXPR Q q2{q1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, q2.value());
	}
	{
		using D = hamon::units::length_dimension;
		using S = std::ratio<1000, 1>;
		using O = std::ratio<100, 3>;
		using Q = hamon::units::quantity<T, D, S, O>;
		static_assert(hamon::is_copy_constructible<Q>::value, "");
		static_assert(hamon::is_nothrow_copy_constructible<Q>::value, "");
		static_assert(hamon::is_implicitly_copy_constructible<Q>::value, "");
		HAMON_CONSTEXPR Q q1(5);
		HAMON_CONSTEXPR Q q2(q1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, q2.value());
	}
}

TYPED_TEST(QuantityTest, ConvertConstructTest)
{
	using T = TypeParam;
	{
		using D = hamon::units::length_dimension;
		using S1 = std::ratio<   1, 1>;
		using S2 = std::ratio<1000, 1>;
		using Q1 = hamon::units::quantity<T, D, S1>;
		using Q2 = hamon::units::quantity<T, D, S2>;
		static_assert(hamon::is_constructible<Q2, Q1>::value, "");
		static_assert(hamon::is_nothrow_constructible<Q2, Q1>::value, "");
		static_assert(hamon::is_implicitly_constructible<Q2, Q1>::value, "");
		HAMON_CONSTEXPR Q1 q1(1);
		HAMON_CONSTEXPR Q2 q2(q1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1) / T(1000), q2.value());
	}
	{
		using D = hamon::units::mass_dimension;
		using S1 = std::ratio<100, 1>;
		using S2 = std::ratio<1, 1>;
		using Q1 = hamon::units::quantity<T, D, S1>;
		using Q2 = hamon::units::quantity<T, D, S2>;
		static_assert(hamon::is_constructible<Q2, Q1>::value, "");
		static_assert(hamon::is_nothrow_constructible<Q2, Q1>::value, "");
		static_assert(hamon::is_implicitly_constructible<Q2, Q1>::value, "");
		HAMON_CONSTEXPR Q1 q1(2);
		HAMON_CONSTEXPR Q2 q2{q1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(2) * T(100), q2.value());
	}
	{
		using D = hamon::units::time_dimension;
		using S1 = std::ratio<2, 3>;
		using S2 = std::ratio<5, 7>;
		using Q1 = hamon::units::quantity<T, D, S1>;
		using Q2 = hamon::units::quantity<T, D, S2>;
		static_assert(hamon::is_constructible<Q2, Q1>::value, "");
		static_assert(hamon::is_nothrow_constructible<Q2, Q1>::value, "");
		static_assert(hamon::is_implicitly_constructible<Q2, Q1>::value, "");
		HAMON_CONSTEXPR Q1 q1{3};
		HAMON_CONSTEXPR Q2 q2{q1};
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.0 * (2.0 / 3.0) / (5.0 / 7.0), (double)q2.value(), 0.0000001);
	}
	{
		using D = hamon::units::length_dimension;
		using S = std::ratio<1, 1>;
		using O1 = std::ratio<100, 1>;
		using O2 = std::ratio<0, 1>;
		using Q1 = hamon::units::quantity<T, D, S, O1>;
		using Q2 = hamon::units::quantity<T, D, S, O2>;
		static_assert(hamon::is_constructible<Q2, Q1>::value, "");
		static_assert(hamon::is_nothrow_constructible<Q2, Q1>::value, "");
		static_assert(hamon::is_implicitly_constructible<Q2, Q1>::value, "");
		HAMON_CONSTEXPR Q1 q1(4);
		HAMON_CONSTEXPR Q2 q2(q1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(104, q2.value());
	}
	{
		using D = hamon::units::mass_dimension;
		using S1 = std::ratio<314, 100>;
		using S2 = std::ratio<11, 1000>;
		using O1 = std::ratio<25, 13>;
		using O2 = std::ratio<10, 17>;
		using Q1 = hamon::units::quantity<T, D, S1, O1>;
		using Q2 = hamon::units::quantity<T, D, S2, O2>;
		static_assert(hamon::is_constructible<Q2, Q1>::value, "");
		static_assert(hamon::is_nothrow_constructible<Q2, Q1>::value, "");
		static_assert(hamon::is_implicitly_constructible<Q2, Q1>::value, "");
		HAMON_CONSTEXPR Q1 q1{5};
		HAMON_CONSTEXPR Q2 q2{q1};
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((5.0 + (25.0 / 13.0)) * (314.0 / 100.0) / (11.0 / 1000.0) - (10.0 / 17.0), (double)q2.value(), 0.0001);
	}
}

HAMON_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
HAMON_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

TYPED_TEST(QuantityTest, AssignTest)
{
	using T = TypeParam;
	using D = hamon::units::length_dimension;

	hamon::units::quantity<T, D> x;
	EXPECT_EQ(0, x.value());

	// コピー代入
	x = hamon::units::quantity<T, D>(3);
	EXPECT_EQ(3, x.value());

	// 変換代入
	x = hamon::units::quantity<T, D, std::ratio<100>>(4);
	EXPECT_EQ(400, x.value());

	x = hamon::units::quantity<T, D, std::ratio<100>, std::ratio<30>>(4);
	EXPECT_EQ(3400, x.value());

	// 自己代入
	x = x;
	EXPECT_EQ(3400, x.value());

	// 多重代入
	hamon::units::quantity<T, D, std::ratio<1, 1000>> y;
	x = y = hamon::units::quantity<T, D>(5);
	EXPECT_EQ(5, x.value());
	EXPECT_EQ(5000, y.value());
}

HAMON_WARNING_POP()

TYPED_TEST(QuantityTest, SwapTest)
{
	using T = TypeParam;
	using D = hamon::units::length_dimension;
	using Q = hamon::units::quantity<T, D>;

	Q x1(12);
	Q x2(34);

	x1.swap(x2);

	EXPECT_EQ(34, x1.value());
	EXPECT_EQ(12, x2.value());

	swap(x1, x2);

	EXPECT_EQ(12, x1.value());
	EXPECT_EQ(34, x2.value());
}

TYPED_TEST(QuantityTest, PlusMinusTest)
{
	using T = TypeParam;
	using D = hamon::units::length_dimension;
	using Q1 = hamon::units::quantity<T, D>;
	using Q2 = hamon::units::quantity<T, D, std::ratio<1, 10>>;

	HAMON_CONSTEXPR Q1 x(5);

	HAMON_CONSTEXPR Q1 x1 = +x;
	HAMON_CONSTEXPR Q1 x2 = -x;
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, x1.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-5, x2.value());

	HAMON_CONSTEXPR Q2 y1 = +x;
	HAMON_CONSTEXPR Q2 y2 = -x;
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 50, y1.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-50, y2.value());
}

TYPED_TEST(QuantityTest, AddTest)
{
	using T = TypeParam;
	using D = hamon::units::length_dimension;
	using Q1 = hamon::units::quantity<T, D>;
	using Q2 = hamon::units::quantity<T, D, std::ratio<1000>>;

	// quantity += quantity
	{
		Q1 x;

		x += Q1(3);
		EXPECT_EQ(3, x.value());

		x += Q2(4);
		EXPECT_EQ(4003, x.value());
	}
	// quantity + quantity
	{
		HAMON_CONSTEXPR Q1 x = Q1(2) + Q1(3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, x.value());
	}
	{
		HAMON_CONSTEXPR Q1 x = Q1(4) + Q2(5);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5004, x.value());
	}
	{
		HAMON_CONSTEXPR Q1 x = Q2(6) + Q1(7);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6007, x.value());
	}
	{
		HAMON_CONSTEXPR Q1 x = Q2(4) + Q2(5);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(9000, x.value());
	}
}

TYPED_TEST(QuantityTest, SubTest)
{
	using T = TypeParam;
	using D = hamon::units::length_dimension;
	using Q1 = hamon::units::quantity<T, D>;
	using Q2 = hamon::units::quantity<T, D, std::ratio<1000>>;

	// quantity -= quantity
	{
		Q1 x(20);

		x -= Q1(3);
		EXPECT_EQ(17, x.value());

		x -= Q2(4);
		EXPECT_EQ(-3983, x.value());
	}
	// quantity - quantity
	{
		HAMON_CONSTEXPR Q1 x = Q1(5) - Q1(3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, x.value());
	}
	{
		HAMON_CONSTEXPR Q1 x = Q1(4) - Q2(5);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4996, x.value());
	}
	{
		HAMON_CONSTEXPR Q1 x = Q2(6) - Q1(7);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5993, x.value());
	}
	{
		HAMON_CONSTEXPR Q1 x = Q2(4) - Q2(5);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1000, x.value());
	}
}

TYPED_TEST(QuantityTest, MulScalarTest)
{
	using T = TypeParam;
	using D = hamon::units::length_dimension;
	using Q = hamon::units::quantity<T, D>;

	// quantity *= Scalar
	{
		Q x(2);
		EXPECT_EQ(2, x.value());

		x *= 3;
		EXPECT_EQ(6, x.value());

		x *= 1.5f;
		EXPECT_EQ(9.0, x.value());
	}
	// quantity * Scalar
	{
		HAMON_CONSTEXPR Q x = Q(21) * 2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, x.value());
	}
	{
		HAMON_CONSTEXPR Q x = Q(22) * 0.5f;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, x.value());
	}
	// Scalar * quantity
	{
		HAMON_CONSTEXPR Q x = 3 * Q(11);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(33, x.value());
	}
	{
		HAMON_CONSTEXPR Q x = 1.5 * Q(12);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, x.value());
	}
}

TYPED_TEST(QuantityTest, MulRatioTest)
{
	using T = TypeParam;
	using D = hamon::units::length_dimension;

	// quantity * ratio
	{
		HAMON_CONSTEXPR_OR_CONST auto x =
			hamon::units::quantity<T, D>(2) * std::ratio<100>();
		static_assert(hamon::is_same<
			const hamon::units::quantity<T, D, std::ratio<100>>,
			decltype(x)>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, x.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto x =
			hamon::units::quantity<T, D, std::ratio<2, 5>>(3) * std::ratio<7, 3>();
		static_assert(hamon::is_same<
			const hamon::units::quantity<T, D, std::ratio<14, 15>>,
			decltype(x)>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, x.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto x =
			hamon::units::quantity<T, D, std::ratio<3, 100>>(4) * std::ratio<5>();
		static_assert(hamon::is_same<
			const hamon::units::quantity<T, D, std::ratio<3, 20>>,
			decltype(x)>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, x.value());
	}
}

TYPED_TEST(QuantityTest, MulQuantityTest)
{
	using T = TypeParam;

	// quantity * quantity
	{
		using D1 = hamon::units::length_dimension;
		using D2 = hamon::units::make_derived_dimension_t<
			hamon::units::dimension_holder<
				hamon::units::length_dimension_tag, 2
			>
		>;

		HAMON_CONSTEXPR_OR_CONST auto x =
			hamon::units::quantity<T, D1>(2) *
			hamon::units::quantity<T, D1>(3);
		static_assert(hamon::is_same<
			const hamon::units::quantity<T, D2>,
			decltype(x)>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, x.value());
	}
	{
		using D1 = hamon::units::length_dimension;
		using D2 = hamon::units::mass_dimension;
		using D3 = hamon::units::make_derived_dimension_t<
			hamon::units::dimension_holder<
				hamon::units::length_dimension_tag
			>,
			hamon::units::dimension_holder<
				hamon::units::mass_dimension_tag
			>
		>;

		HAMON_CONSTEXPR_OR_CONST auto x =
			hamon::units::quantity<T, D1>(2) *
			hamon::units::quantity<T, D2>(3);
		static_assert(hamon::is_same<
			const hamon::units::quantity<T, D3>,
			decltype(x)>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, x.value());
	}
	{
		using D1 = hamon::units::length_dimension;
		using D2 = hamon::units::make_derived_dimension_t<
			hamon::units::dimension_holder<
				hamon::units::length_dimension_tag, 2
			>
		>;
		using Q1 = hamon::units::quantity<T, D1>;
		using Q2 = hamon::units::quantity<T, D1, std::ratio<1000>>;
		using Q3 = hamon::units::quantity<T, D2, std::ratio<1000>>;
		HAMON_CONSTEXPR_OR_CONST auto x = Q1(4) * Q2(5);
		static_assert(hamon::is_same<const Q3, decltype(x)>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, x.value());
	}
}

TYPED_TEST(QuantityTest, DivScalarTest)
{
	using T = TypeParam;
	using D = hamon::units::length_dimension;
	using Q = hamon::units::quantity<T, D>;

	// quantity /= Scalar
	{
		Q x(10);
		EXPECT_EQ(10, x.value());

		x /= 2;
		EXPECT_EQ(5, x.value());

		x /= 0.5f;
		EXPECT_EQ(10, x.value());
	}
	// quantity / Scalar
	{
		HAMON_CONSTEXPR_OR_CONST Q x = Q(8) / 2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, x.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST Q x = Q(10) / 0.5;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, x.value());
	}
	// Scalar / quantity
	{
		HAMON_CONSTEXPR_OR_CONST auto x = T(10) / Q(2);
		using D2 = hamon::units::make_derived_dimension_t<
			hamon::units::dimension_holder<
				hamon::units::length_dimension_tag, -1
			>
		>;
		using Q2 = hamon::units::quantity<T, D2>;
		static_assert(hamon::is_same<const Q2, decltype(x)>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, x.value());
	}
}

TYPED_TEST(QuantityTest, DivQuantityTest)
{
	using T = TypeParam;

	// quantity / quantity
	{
		using D1 = hamon::units::length_dimension;

		HAMON_CONSTEXPR_OR_CONST auto x =
			hamon::units::quantity<T, D1>(9) /
			hamon::units::quantity<T, D1>(3);
		static_assert(hamon::is_same<
			const hamon::units::dimensionless<T>,
			decltype(x)>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, x.value());
	}
	{
		using D1 = hamon::units::length_dimension;
		using D2 = hamon::units::mass_dimension;
		using D3 = hamon::units::make_derived_dimension_t<
			hamon::units::dimension_holder<
				hamon::units::length_dimension_tag
			>,
			hamon::units::dimension_holder<
				hamon::units::mass_dimension_tag, -1
			>
		>;

		HAMON_CONSTEXPR_OR_CONST auto x =
			hamon::units::quantity<T, D1>(10) /
			hamon::units::quantity<T, D2>(2);
		static_assert(hamon::is_same<
			const hamon::units::quantity<T, D3>,
			decltype(x)>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, x.value());
	}
	{
		using D1 = hamon::units::length_dimension;
		using Q1 = hamon::units::quantity<T, D1>;
		using Q2 = hamon::units::quantity<T, D1, std::ratio<1000>>;
		using Q3 = hamon::units::dimensionless<T, std::ratio<1, 1000>>;
		HAMON_CONSTEXPR_OR_CONST auto x = Q1(12) / Q2(3);
		static_assert(hamon::is_same<const Q3, decltype(x)>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4, (double)x.value(), 0.0000000001);
	}
}

TYPED_TEST(QuantityTest, CompareTest)
{
	using T = TypeParam;
	using D = hamon::units::length_dimension;
	using Q1 = hamon::units::quantity<T, D>;
	using Q2 = hamon::units::quantity<T, D, std::ratio<1, 1000>>;

	HAMON_CONSTEXPR Q1 x1(4);
	HAMON_CONSTEXPR Q1 x2(4);
	HAMON_CONSTEXPR Q1 x3(-4);
	HAMON_CONSTEXPR Q1 x4(5);
	HAMON_CONSTEXPR Q2 x5(4);
	HAMON_CONSTEXPR Q2 x6(4000);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 == x1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 == x2);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 == x3);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 == x4);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 == x5);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 == x6);

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 != x1);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 != x2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 != x3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 != x4);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 != x5);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 != x6);

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 < x1);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 < x2);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 < x3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 < x4);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 < x5);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 < x6);

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 > x1);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 > x2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 > x3);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 > x4);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 > x5);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 > x6);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 <= x1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 <= x2);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 <= x3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 <= x4);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 <= x5);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 <= x6);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 >= x1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 >= x2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 >= x3);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x1 >= x4);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 >= x5);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x1 >= x6);
}

TYPED_TEST(QuantityTest, OutputStreamTest)
{
	using T = TypeParam;
	using D = hamon::units::length_dimension;
	using Q1 = hamon::units::quantity<T, D>;
	using Q2 = hamon::units::quantity<T, D, std::ratio<1, 1000>>;

	{
		const Q1 x(321);
		std::stringstream ss;
		ss << x;
		EXPECT_EQ("321", ss.str());
	}
	{
		const Q2 x(54321);
		std::wstringstream ss;
		ss << x;
		EXPECT_EQ(L"54321", ss.str());
	}
}

}	// namespace units_quantity_test
