/**
 *	@file	unit_test_valarray_valarray_ctor_size.cpp
 *
 *	@brief	サイズを引数に取るコンストラクタのテスト
 *
 *	explicit valarray(size_t);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_ctor_size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	static_assert( hamon::is_constructible<hamon::valarray<T>, hamon::size_t>::value, "");
	static_assert(!hamon::is_nothrow_constructible<hamon::valarray<T>, hamon::size_t>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::valarray<T>, hamon::size_t>::value, "");

	hamon::valarray<T> va(hamon::size_t(3));
	VERIFY(va.size() == 3u);
	VERIFY(va[0] == T{});
	VERIFY(va[1] == T{});
	VERIFY(va[2] == T{});

	return true;
}

struct S
{
	S() : x(1) {}
	~S() { ++cnt_dtor; }
	int x;
	static hamon::size_t cnt_dtor;
};

size_t S::cnt_dtor = 0;

inline bool test2()
{
	{
		hamon::valarray<S> v(100);
		VERIFY(v.size() == 100);
		for (hamon::size_t i = 0; i < 100; ++i)
		{
			VERIFY(v[i].x == 1);
		}
	}
	VERIFY(S::cnt_dtor == 100);

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayCtorSizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));

	EXPECT_TRUE((test2()));
}

}	// namespace valarray_ctor_size_test

}	// namespace hamon_valarray_test
