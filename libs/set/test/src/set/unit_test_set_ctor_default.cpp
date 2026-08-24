/**
 *	@file	unit_test_set_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	set() : set(Compare()) { }
 */

#include <hamon/set/set.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace ctor_default_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::set<Key>;

	static_assert( hamon::is_default_constructible<Set>::value, "");
	static_assert(!hamon::is_nothrow_default_constructible<Set>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<Set>::value, "");
	static_assert(!hamon::is_trivially_default_constructible<Set>::value, "");

	{
		Set v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
	}
	{
		Set v{};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
	}
	{
		Set v = {};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, CtorDefaultTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace ctor_default_test

}	// namespace hamon_set_test
