/**
 *	@file	unit_test_valarray_valarray_comp_assign_and.cpp
 *
 *	@brief	operator&= のテスト
 *
 *	valarray& operator&=(const T&);
 *	valarray& operator&=(const valarray&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_comp_assign_and_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	hamon::valarray<T> va{1,2,3,4,5};

	static_assert(hamon::is_same<decltype(va &= hamon::declval<hamon::valarray<T> const&>()), hamon::valarray<T>&>::value, "");
	static_assert(!noexcept(va &= hamon::declval<hamon::valarray<T> const&>()), "");

	static_assert(hamon::is_same<decltype(va &= hamon::declval<T const&>()), hamon::valarray<T>&>::value, "");
	static_assert(!noexcept(va &= hamon::declval<T const&>()), "");

	{
		auto& t = (va &= hamon::valarray<T>{6,7,8,7,15});
		VERIFY(&t == &va);
	}
	VERIFY(va.size() == 5u);
	VERIFY(va[0] == T{0});
	VERIFY(va[1] == T{2});
	VERIFY(va[2] == T{0});
	VERIFY(va[3] == T{4});
	VERIFY(va[4] == T{5});

	{
		auto& t = (va &= T{3});
		VERIFY(&t == &va);
	}
	VERIFY(va.size() == 5u);
	VERIFY(va[0] == T{0});
	VERIFY(va[1] == T{2});
	VERIFY(va[2] == T{0});
	VERIFY(va[3] == T{0});
	VERIFY(va[4] == T{1});

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayCompAssignAndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
}

}	// namespace valarray_comp_assign_and_test

}	// namespace hamon_valarray_test
