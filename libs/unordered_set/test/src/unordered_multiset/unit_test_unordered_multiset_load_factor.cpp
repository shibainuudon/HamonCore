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

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test()
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
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));

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

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace load_factor_test

}	// namespace hamon_unordered_multiset_test
