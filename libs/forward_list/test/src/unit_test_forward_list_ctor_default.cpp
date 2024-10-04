/**
 *	@file	unit_test_forward_list_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	forward_list();
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace ctor_default_test
{

struct S1
{
	S1() = delete;
};

struct S2
{
	S2() {}
};

struct S3
{
	int x;
	float y;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using ForwardList = hamon::forward_list<T>;

	static_assert( hamon::is_default_constructible<ForwardList>::value, "");
#if !defined(HAMON_USE_STD_FORWARD_LIST)
	// TODO
	//static_assert( hamon::is_nothrow_default_constructible<ForwardList>::value, "");
#endif
	static_assert( hamon::is_implicitly_default_constructible<ForwardList>::value, "");
	static_assert(!hamon::is_trivially_default_constructible<ForwardList>::value, "");

	{
		ForwardList v;
		VERIFY(v.empty());
	}
	{
		ForwardList v{};
		VERIFY(v.empty());
	}
	{
		ForwardList v = {};
		VERIFY(v.empty());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, CtorDefaultTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S3>());
}

}	// namespace ctor_default_test

}	// namespace hamon_forward_list_test
