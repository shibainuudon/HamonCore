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
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace clear_test

}	// namespace hamon_unordered_multiset_test
