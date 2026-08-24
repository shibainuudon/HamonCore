/**
 *	@file	unit_test_unordered_multiset_clear.cpp
 *
 *	@brief	clear のテスト
 *
 *	constexpr void clear() noexcept;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace clear_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().clear()), void>::value, "");
	static_assert(noexcept(hamon::declval<Set&>().clear()), "");

	Set v{Key{3}, Key{1}, Key{4}, Key{1}};
	VERIFY(!v.empty());
	v.clear();
	VERIFY(v.empty());
	v.clear();
	VERIFY(v.empty());

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, ClearTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace clear_test

}	// namespace hamon_unordered_multiset_test
