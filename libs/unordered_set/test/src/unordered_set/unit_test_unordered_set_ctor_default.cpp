/**
 *	@file	unit_test_unordered_set_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr unordered_set();
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace ctor_default_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_set<Key>;

	static_assert( hamon::is_default_constructible<Set>::value, "");
	static_assert(!hamon::is_nothrow_default_constructible<Set>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<Set>::value, "");
	static_assert(!hamon::is_trivially_default_constructible<Set>::value, "");

	{
		Set v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		Set v{};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		Set v = {};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, CtorDefaultTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace ctor_default_test

}	// namespace hamon_unordered_set_test
