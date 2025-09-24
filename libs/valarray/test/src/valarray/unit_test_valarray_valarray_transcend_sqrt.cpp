/**
 *	@file	unit_test_valarray_valarray_transcend_sqrt.cpp
 *
 *	@brief	sqrt のテスト
 *
 *	template<class T> valarray<T> sqrt(const valarray<T>&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "valarray_test_helper.hpp"

namespace hamon_valarray_test
{

namespace valarray_transcend_sqrt_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	T a1[] = { .5, .75, 1, 3, 7 };
	T a3[] = { 7.0710678118654757e-01,
			  8.6602540378443860e-01,
			  1.0000000000000000e+00,
			  1.7320508075688772e+00,
			  2.6457513110645907e+00 };
	const unsigned N = sizeof(a1) / sizeof(a1[0]);
	hamon::valarray<T> v1(a1, N);

#if !defined(HAMON_USE_STD_VALARRAY)
	static_assert(hamon::is_same<decltype(sqrt(v1)), hamon::valarray<T>>::value, "");
	static_assert(!noexcept(sqrt(v1)), "");
#endif

	hamon::valarray<T> v3 = sqrt(v1);
	VERIFY(v3.size() == v1.size());
	for (hamon::size_t i = 0; i < v3.size(); ++i)
	{
		VERIFY(is_about(v3[i], a3[i], 10));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayTranscendSqrtTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<double>()));
}

}	// namespace valarray_transcend_sqrt_test

}	// namespace hamon_valarray_test
