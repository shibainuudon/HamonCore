/**
 *	@file	unit_test_flat_multiset_max_size.cpp
 *
 *	@brief	max_size のテスト
 *
 *	constexpr size_type max_size() const noexcept;
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace max_size_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_multiset<Key, hamon::less<Key>, KeyContainer>;
	using SizeType  = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&      >().max_size()), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().max_size()), SizeType>::value, "");
	static_assert(noexcept(hamon::declval<Set&      >().max_size()), "");
	static_assert(noexcept(hamon::declval<Set const&>().max_size()), "");

	{
		Set v;
		VERIFY(v.max_size() > 0);
	}
	{
		Set const v;
		VERIFY(v.max_size() > 0);
	}
	{
		Set v
		{
			Key{2},
			Key{3},
			Key{1},
			Key{1},
			Key{2},
		};
		VERIFY(v.max_size() > 5);
	}
	{
		Set const v
		{
			Key{2},
			Key{3},
			Key{1},
			Key{4},
			Key{5},
			Key{3},
		};
		VERIFY(v.max_size() > 6);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultisetTest, MaxSizeTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>>()));
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace max_size_test

}	// namespace hamon_flat_multiset_test
