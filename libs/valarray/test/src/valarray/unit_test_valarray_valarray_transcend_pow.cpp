/**
 *	@file	unit_test_valarray_valarray_transcend_pow.cpp
 *
 *	@brief	pow のテスト
 *
 *	template<class T> valarray<T> pow(const valarray<T>&, const valarray<T>&);
 *	template<class T> valarray<T> pow(const valarray<T>&, const typename valarray<T>::value_type&);
 *	template<class T> valarray<T> pow(const typename valarray<T>::value_type&, const valarray<T>&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "valarray_test_helper.hpp"

namespace hamon_valarray_test
{

namespace valarray_transcend_pow_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	// template<class T> valarray<T> pow(const valarray<T>&, const valarray<T>&);
	{
		T a1[] = { .9, .5, 0., .5, .75 };
		T a2[] = { -.8,  .25, 0.375, -.5, .75 };
		T a3[] = { 1.0879426248455297e+00,
				  8.4089641525371450e-01,
				  0.0000000000000000e+00,
				  1.4142135623730949e+00,
				  8.0592744886765644e-01 };
		const unsigned N = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N);
		hamon::valarray<T> v2(a2, N);

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(pow(v1, v2)), hamon::valarray<T>>::value, "");
		static_assert(!noexcept(pow(v1, v2)), "");
#endif

		hamon::valarray<T> v3 = pow(v1, v2);
		VERIFY(v3.size() == v1.size());
		for (hamon::size_t i = 0; i < v3.size(); ++i)
		{
			VERIFY(is_about(v3[i], a3[i], 10));
		}
	}

	// template<class T> valarray<T> pow(const valarray<T>&, const typename valarray<T>::value_type&);
	{
		T a1[] = { .9, .5, 0., .5, .75 };
		T a3[] = { 8.1000000000000005e-01,
				  2.5000000000000000e-01,
				  0.0000000000000000e+00,
				  2.5000000000000000e-01,
				  5.6250000000000000e-01 };
		const unsigned N = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N);

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(pow(v1, T{})), hamon::valarray<T>>::value, "");
		static_assert(!noexcept(pow(v1, T{})), "");
#endif

		hamon::valarray<T> v3 = pow(v1, 2.0);
		VERIFY(v3.size() == v1.size());
		for (hamon::size_t i = 0; i < v3.size(); ++i)
		{
			VERIFY(is_about(v3[i], a3[i], 10));
		}
	}

	// template<class T> valarray<T> pow(const typename valarray<T>::value_type&, const valarray<T>&);
	{
		T a1[] = { .9, .5, 0., .5, .75 };
		T a3[] = { 1.8660659830736148e+00,
				  1.4142135623730951e+00,
				  1.0000000000000000e+00,
				  1.4142135623730951e+00,
				  1.6817928305074290e+00 };
		const unsigned N = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N);

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(pow(T{}, v1)), hamon::valarray<T>>::value, "");
		static_assert(!noexcept(pow(T{}, v1)), "");
#endif

		hamon::valarray<T> v3 = pow(2.0, v1);
		VERIFY(v3.size() == v1.size());
		for (hamon::size_t i = 0; i < v3.size(); ++i)
		{
			VERIFY(is_about(v3[i], a3[i], 10));
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayTranscendPowTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<double>()));
}

}	// namespace valarray_transcend_pow_test

}	// namespace hamon_valarray_test
