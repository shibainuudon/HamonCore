/**
 *	@file	unit_test_valarray_valarray_transcend_acos.cpp
 *
 *	@brief	acos のテスト
 *
 *	template<class T> valarray<T> acos(const valarray<T>&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "valarray_test_helper.hpp"

namespace hamon_valarray_test
{

namespace valarray_transcend_acos_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	T a1[] = { -.9, -.5, 0., .5, .75 };
	T a3[] = { 2.6905658417935308e+00,
			  2.0943951023931957e+00,
			  1.5707963267948966e+00,
			  1.0471975511965976e+00,
			  7.2273424781341566e-01 };
	const unsigned N = sizeof(a1) / sizeof(a1[0]);
	hamon::valarray<T> v1(a1, N);

#if !defined(HAMON_USE_STD_VALARRAY)
	static_assert(hamon::is_same<decltype(acos(v1)), hamon::valarray<T>>::value, "");
	static_assert(!noexcept(acos(v1)), "");
#endif

	hamon::valarray<T> v3 = acos(v1);
	VERIFY(v3.size() == v1.size());
	for (hamon::size_t i = 0; i < v3.size(); ++i)
	{
		VERIFY(is_about(v3[i], a3[i], 10));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayTranscendAcosTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<double>()));
}

}	// namespace valarray_transcend_acos_test

}	// namespace hamon_valarray_test
