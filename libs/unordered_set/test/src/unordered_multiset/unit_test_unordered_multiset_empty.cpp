/**
 *	@file	unit_test_unordered_multiset_empty.cpp
 *
 *	@brief	empty のテスト
 *
 *	constexpr bool empty() const noexcept;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace empty_test
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

GTEST_TEST(UnorderedMultisetTest, EmptyTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace empty_test

}	// namespace hamon_unordered_multiset_test
