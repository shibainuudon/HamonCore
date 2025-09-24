/**
 *	@file	unit_test_valarray_valarray_size.cpp
 *
 *	@brief	size のテスト
 *
 *	size_t size() const;
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	hamon::valarray<T> va{1,2,3};

	static_assert(hamon::is_same<decltype(va.size()), hamon::size_t>::value, "");
#if !defined(HAMON_USE_STD_VALARRAY)
	static_assert(noexcept(va.size()), "");
#endif

	VERIFY(va.size() == 3u);

	va = {6,5,7,4};
	VERIFY(va.size() == 4u);

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarraySizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_size_test

}	// namespace hamon_valarray_test
