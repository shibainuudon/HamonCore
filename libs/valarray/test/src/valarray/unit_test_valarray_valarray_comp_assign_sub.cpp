/**
 *	@file	unit_test_valarray_valarray_comp_assign_sub.cpp
 *
 *	@brief	operator-= のテスト
 *
 *	valarray& operator-=(const T&);
 *	valarray& operator-=(const valarray&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_comp_assign_sub_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	hamon::valarray<T> va{10,20,30};

	static_assert(hamon::is_same<decltype(va -= hamon::declval<hamon::valarray<T> const&>()), hamon::valarray<T>&>::value, "");
	static_assert(!noexcept(va -= hamon::declval<hamon::valarray<T> const&>()), "");

	static_assert(hamon::is_same<decltype(va -= hamon::declval<T const&>()), hamon::valarray<T>&>::value, "");
	static_assert(!noexcept(va -= hamon::declval<T const&>()), "");

	{
		auto& t = (va -= hamon::valarray<T>{1,2,3});
		VERIFY(&t == &va);
	}
	VERIFY(va.size() == 3u);
	VERIFY(va[0] == T{9});
	VERIFY(va[1] == T{18});
	VERIFY(va[2] == T{27});

	{
		auto& t = (va -= T{3});
		VERIFY(&t == &va);
	}
	VERIFY(va.size() == 3u);
	VERIFY(va[0] == T{6});
	VERIFY(va[1] == T{15});
	VERIFY(va[2] == T{24});

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayCompAssignSubTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_comp_assign_sub_test

}	// namespace hamon_valarray_test
