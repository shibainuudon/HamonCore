/**
 *	@file	unit_test_valarray_valarray_transcend_atan.cpp
 *
 *	@brief	atan のテスト
 *
 *	template<class T> valarray<T> atan(const valarray<T>&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "valarray_test_helper.hpp"

namespace hamon_valarray_test
{

namespace valarray_transcend_atan_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	T a1[] = { -.9, -.5, 0., .5, .75 };
	T a3[] = { -7.3281510178650666e-01,
			  -4.6364760900080615e-01,
			   0.0000000000000000e+00,
			   4.6364760900080615e-01,
			   6.4350110879328437e-01 };
	const unsigned N = sizeof(a1) / sizeof(a1[0]);
	hamon::valarray<T> v1(a1, N);

#if !defined(HAMON_USE_STD_VALARRAY)
	static_assert(hamon::is_same<decltype(atan(v1)), hamon::valarray<T>>::value, "");
	static_assert(!noexcept(atan(v1)), "");
#endif

	hamon::valarray<T> v3 = atan(v1);
	VERIFY(v3.size() == v1.size());
	for (hamon::size_t i = 0; i < v3.size(); ++i)
	{
		VERIFY(is_about(v3[i], a3[i], 10));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayTranscendAtanTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<double>()));
}

}	// namespace valarray_transcend_atan_test

}	// namespace hamon_valarray_test
