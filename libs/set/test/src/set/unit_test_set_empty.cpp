/**
 *	@file	unit_test_set_empty.cpp
 *
 *	@brief	empty のテスト
 *
 *	bool empty() const noexcept;
 */

#include <hamon/set/set.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace empty_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::set<Key>;

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

GTEST_TEST(SetTest, EmptyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/set/empty
	{
		hamon::set<int> numbers;
		EXPECT_TRUE(numbers.empty());

		numbers.insert(42);
		numbers.insert(19937);
		EXPECT_FALSE(numbers.empty());
	}
}

}	// namespace empty_test

}	// namespace hamon_set_test
