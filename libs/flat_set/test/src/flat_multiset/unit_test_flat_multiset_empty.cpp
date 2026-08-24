/**
 *	@file	unit_test_flat_multiset_empty.cpp
 *
 *	@brief	empty のテスト
 *
 *	constexpr bool empty() const noexcept;
 */

#include <hamon/flat_set/flat_multiset.hpp>
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

namespace empty_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_multiset<Key, hamon::less<Key>, KeyContainer>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&      >().empty()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().empty()), bool>::value, "");
	static_assert(noexcept(hamon::declval<Set&      >().empty()), "");
	static_assert(noexcept(hamon::declval<Set const&>().empty()), "");

	{
		Set v;
		VERIFY(v.empty() == true);
		v.insert(Key{42});
		VERIFY(v.empty() == false);
	}
	{
		Set const v;
		VERIFY(v.empty() == true);
	}
	{
		Set v
		{
			Key{2},
			Key{3},
			Key{1},
			Key{1},
			Key{2},
			Key{3},
		};
		VERIFY(v.empty() == false);
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
		VERIFY(v.empty() == false);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultisetTest, EmptyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>>()));

	{
		hamon::flat_multiset<int> fs;

		EXPECT_TRUE(fs.empty());

		fs.insert(42);

		EXPECT_FALSE(fs.empty());
	}
}

}	// namespace empty_test

}	// namespace hamon_flat_multiset_test
