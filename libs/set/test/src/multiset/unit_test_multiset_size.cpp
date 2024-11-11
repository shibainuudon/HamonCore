/**
 *	@file	unit_test_multiset_size.cpp
 *
 *	@brief	size のテスト
 *
 *	size_type size() const noexcept;
 */

#include <hamon/set/multiset.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace size_test
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
	using SizeType = typename Set::size_type;

	{
		Set v;
		static_assert(hamon::is_same<decltype(v.size()), SizeType>::value, "");
		static_assert(noexcept(v.size()), "");
		VERIFY(v.size() == 0);
	}
	{
		Set v{Key{3}, Key{1}, Key{1}, Key{3}, Key{1}, Key{3}};
		VERIFY(v.size() == 6);
	}
	{
		Set const v;
		static_assert(hamon::is_same<decltype(v.size()), SizeType>::value, "");
		static_assert(noexcept(v.size()), "");
		VERIFY(v.size() == 0);
	}
	{
		Set const v{Key{3}, Key{1}, Key{1}, Key{1}, Key{2}};
		VERIFY(v.size() == 5);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, SizeTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/multiset/size
	{
		hamon::multiset<int> nums {4, 2, 4, 2};
		EXPECT_TRUE(nums.size() == 4);
	}
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace size_test

}	// namespace hamon_multiset_test
