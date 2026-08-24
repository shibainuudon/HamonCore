/**
 *	@file	unit_test_flat_set_size.cpp
 *
 *	@brief	size のテスト
 *
 *	constexpr size_type size() const noexcept;
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_set<Key, hamon::less<Key>, KeyContainer>;
	using SizeType  = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&      >().size()), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().size()), SizeType>::value, "");
	static_assert(noexcept(hamon::declval<Set&      >().size()), "");
	static_assert(noexcept(hamon::declval<Set const&>().size()), "");

	{
		Set v;
		VERIFY(v.size() == 0);
		v.insert(Key{1});
		VERIFY(v.size() == 1);
		v.insert(Key{2});
		VERIFY(v.size() == 2);
		v.insert(Key{2});
		VERIFY(v.size() == 2);
	}
	{
		Set const v;
		VERIFY(v.size() == 0);
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
		VERIFY(v.size() == 3);
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
		VERIFY(v.size() == 5);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatSetTest, SizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>>()));

	{
		hamon::flat_set<int> fs;

		EXPECT_EQ(0u, fs.size());

		fs.insert(1);
		fs.insert(2);
		fs.insert(3);
		fs.insert(1);

		EXPECT_EQ(3u, fs.size());
	}
}

}	// namespace size_test

}	// namespace hamon_flat_set_test
