/**
 *	@file	unit_test_valarray_valarray_transcend_atan2.cpp
 *
 *	@brief	atan2 のテスト
 *
 *	template<class T> valarray<T> atan2(const valarray<T>&, const valarray<T>&);
 *	template<class T> valarray<T> atan2(const valarray<T>&, const typename valarray<T>::value_type&);
 *	template<class T> valarray<T> atan2(const typename valarray<T>::value_type&, const valarray<T>&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "valarray_test_helper.hpp"

namespace hamon_valarray_test
{

namespace valarray_transcend_atan2_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	// template<class T> valarray<T> atan2(const valarray<T>&, const valarray<T>&);
	{
		T a1[] = { -.9, -.5, 0., .5, .75 };
		T a2[] = { -.8,  .25, 0.375, -.5, .75 };
		T a3[] = { -2.2974386674766221e+00,
				  -1.1071487177940904e+00,
				   0.0000000000000000e+00,
				   2.3561944901923448e+00,
				   7.8539816339744828e-01 };
		const unsigned N = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N);
		hamon::valarray<T> v2(a2, N);

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(atan2(v1, v2)), hamon::valarray<T>>::value, "");
		static_assert(!noexcept(atan2(v1, v2)), "");
#endif

		hamon::valarray<T> v3 = atan2(v1, v2);
		VERIFY(v3.size() == v1.size());
		for (hamon::size_t i = 0; i < v3.size(); ++i)
		{
			VERIFY(is_about(v3[i], a3[i], 10));
		}
	}

	// template<class T> valarray<T> atan2(const valarray<T>&, const typename valarray<T>::value_type&);
	{
		T a1[] = { -.9, -.5, 0., .5, .75 };
		T a3[] = { -8.7605805059819342e-01,
				  -5.8800260354756750e-01,
				   0.0000000000000000e+00,
				   5.8800260354756750e-01,
				   7.8539816339744828e-01 };
		const unsigned N = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N);

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(atan2(v1, T{})), hamon::valarray<T>>::value, "");
		static_assert(!noexcept(atan2(v1, T{})), "");
#endif

		hamon::valarray<T> v3 = atan2(v1, .75);
		VERIFY(v3.size() == v1.size());
		for (hamon::size_t i = 0; i < v3.size(); ++i)
		{
			VERIFY(is_about(v3[i], a3[i], 10));
		}
	}

	// template<class T> valarray<T> atan2(const typename valarray<T>::value_type&, const valarray<T>&);
	{
		T a1[] = { -.9, -.5, 0., .5, .75 };
		T a3[] = { 2.4468543773930902e+00,
				  2.1587989303424640e+00,
				  1.5707963267948966e+00,
				  9.8279372324732905e-01,
				  7.8539816339744828e-01 };
		const unsigned N = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N);

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(atan2(T{}, v1)), hamon::valarray<T>>::value, "");
		static_assert(!noexcept(atan2(T{}, v1)), "");
#endif

		hamon::valarray<T> v3 = atan2(.75, v1);
		VERIFY(v3.size() == v1.size());
		for (hamon::size_t i = 0; i < v3.size(); ++i)
		{
			VERIFY(is_about(v3[i], a3[i], 10));
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayTranscendAtan2Test)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<double>()));
}

}	// namespace valarray_transcend_atan2_test

}	// namespace hamon_valarray_test
