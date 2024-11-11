/**
 *	@file	unit_test_multiset_empty.cpp
 *
 *	@brief	empty のテスト
 *
 *	bool empty() const noexcept;
 */

#include <hamon/set/multiset.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace empty_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
MULTISET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::multiset<Key>;

	{
		Set v;
		static_assert(hamon::is_same<decltype(v.empty()), bool>::value, "");
		static_assert(noexcept(v.empty()), "");
		VERIFY(v.empty() == true);
	}
	{
		Set v{Key{3}, Key{1}, Key{1}, Key{3}, Key{1}, Key{3}};
		VERIFY(v.empty() == false);
	}
	{
		Set const v;
		static_assert(hamon::is_same<decltype(v.empty()), bool>::value, "");
		static_assert(noexcept(v.empty()), "");
		VERIFY(v.empty() == true);
	}
	{
		Set const v{Key{3}, Key{1}, Key{1}, Key{1}, Key{2}};
		VERIFY(v.empty() == false);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, EmptyTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/multiset/empty
	{
		hamon::multiset<int> numbers;
		EXPECT_TRUE(numbers.empty());

		numbers.insert(42);
		numbers.insert(19937);
		EXPECT_FALSE(numbers.empty());
	}
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace empty_test

}	// namespace hamon_multiset_test
