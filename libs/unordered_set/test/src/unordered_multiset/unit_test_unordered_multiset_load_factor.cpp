/**
 *	@file	unit_test_unordered_multiset_load_factor.cpp
 *
 *	@brief	load_factor のテスト
 *
 *	constexpr float load_factor() const noexcept;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "get_random_value.hpp"

namespace hamon_unordered_multiset_test
{

namespace load_factor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().load_factor()), float>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().load_factor()), float>::value, "");
	static_assert(noexcept(hamon::declval<Set&>().load_factor()), "");
	static_assert(noexcept(hamon::declval<Set const&>().load_factor()), "");

	Set v;
	VERIFY(v.load_factor() == 0);
	for (int i = 0; i < 100; ++i)
	{
		v.emplace(static_cast<Key>(i));
		VERIFY(v.load_factor() <= v.max_load_factor());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, LoadFactorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));

	{
		using Key = int;
		hamon::unordered_multiset<Key> v;
		EXPECT_TRUE(v.load_factor() == 0);
		for (int i = 0; i < 1000; ++i)
		{
			v.emplace(get_random_value<Key>());
			EXPECT_TRUE(v.load_factor() <= v.max_load_factor());
		}
	}
}

}	// namespace load_factor_test

}	// namespace hamon_unordered_multiset_test
