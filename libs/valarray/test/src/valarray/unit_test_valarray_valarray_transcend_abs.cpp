/**
 *	@file	unit_test_valarray_valarray_transcend_abs.cpp
 *
 *	@brief	abs のテスト
 *
 *	template<class T> valarray<T> abs(const valarray<T>&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_transcend_abs_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	T a1[] = { 1.5,  -2.5,  3.4,  -4.5,  -5.0 };
	T a3[] = { 1.5,   2.5,  3.4,   4.5,   5.0 };
	const unsigned N = sizeof(a1) / sizeof(a1[0]);
	hamon::valarray<T> v1(a1, N);

#if !defined(HAMON_USE_STD_VALARRAY)
	static_assert(hamon::is_same<decltype(abs(v1)), hamon::valarray<T>>::value, "");
	static_assert(!noexcept(abs(v1)), "");
#endif

	hamon::valarray<T> v3 = abs(v1);
	VERIFY(v3.size() == v1.size());
	for (hamon::size_t i = 0; i < v3.size(); ++i)
	{
		VERIFY(v3[i] == a3[i]);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayTranscendAbsTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<double>()));
}

}	// namespace valarray_transcend_abs_test

}	// namespace hamon_valarray_test
