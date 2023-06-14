/**
 *	@file	unit_test_cmath_ranges_almost_equal.cpp
 *
 *	@brief	ranges::almost_equal のテスト
 */

#include <hamon/cmath/ranges/almost_equal.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_almost_equal_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR bool almost_equal(Real<T> const& x, Real<T> const& y)
{
	return hamon::almost_equal(x.value, y.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<bool>
	almost_equal(Vector3<T> const& v1, Vector3<T> const& v2)
	{
		return Vector3<bool>
		{
			hamon::almost_equal(v1.x, v2.x),
			hamon::almost_equal(v1.y, v2.y),
			hamon::almost_equal(v1.z, v2.z),
		};
	}
};

template <typename T>
struct almost_equal_eps
{
	HAMON_CXX11_STATIC_CONSTEXPR T value = std::numeric_limits<T>::epsilon();
};

template <typename T>
struct almost_equal_eps<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR T value = almost_equal_eps<T>::value;
};


template <typename T>
void RangesAlmostEqualTest(void)
{
	HAMON_CXX11_CONSTEXPR auto eps = almost_equal_eps<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::almost_equal(T{0.0 + (eps * 0)}, T{0.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::almost_equal(T{0.0 + (eps * 1)}, T{0.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::almost_equal(T{0.0 + (eps * 2)}, T{0.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::almost_equal(T{0.0 - (eps * 0)}, T{0.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::almost_equal(T{0.0 - (eps * 1)}, T{0.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::almost_equal(T{0.0 - (eps * 2)}, T{0.0}));
}

template <typename T>
void RangesAlmostEqualTest2(void)
{
	HAMON_CXX11_CONSTEXPR auto eps = almost_equal_eps<T>::value;
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1
		{
			T{1 + eps},
			T{1 + eps * 2},
			T{1 - eps},
		};
		HAMON_CXX11_CONSTEXPR Vector3<T> v2
		{
			T{1},
			T{1},
			T{1},
		};
		HAMON_CXX11_CONSTEXPR Vector3<bool> v3 = hamon::ranges::almost_equal(v1, v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v3.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v3.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v3.z);
	}
}

GTEST_TEST(CMathTest, RangesAlmostEqualTest)
{
	RangesAlmostEqualTest<float>();
	RangesAlmostEqualTest<double>();
	RangesAlmostEqualTest<long double>();

	RangesAlmostEqualTest<Real<float>>();
	RangesAlmostEqualTest<Real<double>>();
	RangesAlmostEqualTest<Real<long double>>();

	RangesAlmostEqualTest2<float>();
	RangesAlmostEqualTest2<double>();
	RangesAlmostEqualTest2<long double>();
}

}	// namespace ranges_almost_equal_test

}	// namespace hamon_cmath_test
