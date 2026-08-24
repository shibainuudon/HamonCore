/**
 *	@file	unit_test_unordered_set_max_load_factor.cpp
 *
 *	@brief	max_load_factor のテスト
 *
 *	constexpr float max_load_factor() const noexcept;
 *	constexpr void max_load_factor(float z);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "get_random_value.hpp"

namespace hamon_unordered_set_test
{

namespace max_load_factor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_set<Key>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().max_load_factor()), float>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().max_load_factor()), float>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().max_load_factor(hamon::declval<float>())), void>::value, "");
	static_assert( noexcept(hamon::declval<Set&>().max_load_factor()), "");
	static_assert( noexcept(hamon::declval<Set const&>().max_load_factor()), "");
	static_assert( noexcept(hamon::declval<Set&>().max_load_factor(hamon::declval<float>())), "");

	{
		Set v;
		VERIFY(v.max_load_factor() == 1.0f);

		v.max_load_factor(2.0f);
		for (int i = 0; i < 100; ++i)
		{
			v.emplace(static_cast<Key>(i));
			VERIFY(v.load_factor() <= v.max_load_factor());
		}
	}
	{
		Set v;
		VERIFY(v.max_load_factor() == 1.0f);

		v.max_load_factor(0.5f);
		for (int i = 0; i < 100; ++i)
		{
			v.emplace(static_cast<Key>(i));
			VERIFY(v.load_factor() <= v.max_load_factor());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, MaxLoadFactorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));

	{
		using Key = int;
		hamon::unordered_set<Key> v;
		EXPECT_TRUE(v.max_load_factor() == 1.0f);

		v.max_load_factor(2.0f);
		for (int i = 0; i < 1000; ++i)
		{
			v.emplace(get_random_value<Key>());
			EXPECT_TRUE(v.load_factor() <= v.max_load_factor());
		}
	}
	{
		using Key = int;
		hamon::unordered_set<Key> v;
		EXPECT_TRUE(v.max_load_factor() == 1.0f);

		v.max_load_factor(0.5f);
		for (int i = 0; i < 1000; ++i)
		{
			v.emplace(get_random_value<Key>());
			EXPECT_TRUE(v.load_factor() <= v.max_load_factor());
		}
	}
}

}	// namespace max_load_factor_test

}	// namespace hamon_unordered_set_test
