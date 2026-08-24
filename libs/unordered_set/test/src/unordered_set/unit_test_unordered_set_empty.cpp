/**
 *	@file	unit_test_unordered_set_empty.cpp
 *
 *	@brief	empty のテスト
 *
 *	constexpr bool empty() const noexcept;
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace empty_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_set<Key>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().empty()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().empty()), bool>::value, "");
	static_assert(noexcept(hamon::declval<Set&>().empty()), "");
	static_assert(noexcept(hamon::declval<Set const&>().empty()), "");

	{
		Set const v;
		VERIFY(v.empty() == true);
	}
	{
		Set const v(3);
		VERIFY(v.empty() == true);
	}
	{
		Set const v{3};
		VERIFY(v.empty() == false);
	}
	{
		Set const v{Key{3}, Key{1}, Key{4}};
		VERIFY(v.empty() == false);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, EmptyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace empty_test

}	// namespace hamon_unordered_set_test
