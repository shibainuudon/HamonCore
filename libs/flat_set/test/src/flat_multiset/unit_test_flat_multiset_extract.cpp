/**
 *	@file	unit_test_flat_multiset_extract.cpp
 *
 *	@brief	extract のテスト
 *
 *	constexpr container_type extract() &&;
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace extract_test
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

	{
		using Set = hamon::flat_multiset<Key, hamon::less<Key>, KeyContainer>;
		using ContainerType = typename Set::container_type;

		static_assert(hamon::is_same<decltype(hamon::declval<Set&&>().extract()), ContainerType>::value, "");
		static_assert(!noexcept(hamon::declval<Set&&>().extract()), "");

		Set v
		{
			Key{3},
			Key{1},
			Key{4},
		};

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(!v.empty());

		auto c = hamon::move(v).extract();

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 0);
		VERIFY(v.empty());

		VERIFY(c.size() == 3);

		Key const keys_expected[] = {Key{1}, Key{3}, Key{4}};
		VERIFY(hamon::ranges::equal(c, keys_expected));
	}
	{
		using Set = hamon::flat_multiset<Key, hamon::greater<Key>, KeyContainer>;
		using ContainerType = typename Set::container_type;

		static_assert(hamon::is_same<decltype(hamon::declval<Set&&>().extract()), ContainerType>::value, "");
		static_assert(!noexcept(hamon::declval<Set&&>().extract()), "");

		Set v
		{
			Key{3},
			Key{1},
			Key{4},
		};

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(!v.empty());

		auto c = hamon::move(v).extract();

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 0);
		VERIFY(v.empty());

		VERIFY(c.size() == 3);

		Key const keys_expected[] = {Key{4}, Key{3}, Key{1}};
		VERIFY(hamon::ranges::equal(c, keys_expected));
	}

	return true;
}

#undef VERIFY

void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	using Key = int;
	using Comp = hamon::less<Key>;
	{
		using KeyContainer = ThrowOnMoveContainer<Key>;
		using Set = hamon::flat_multiset<Key, Comp, KeyContainer>;

		Set v;
		v.emplace(1);
		v.emplace(2);
		EXPECT_THROW(hamon::move(v).extract(), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMultisetTest, ExtractTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<float>>()));

	test_exceptions();

	{
		hamon::flat_multiset<int> fs = {3, 1, 4, 1};

		EXPECT_EQ(4u, fs.size());

		decltype(fs)::container_type c = hamon::move(fs).extract();

		EXPECT_EQ(0u, fs.size());

		std::stringstream ss;
		for (int i : c)
		{
			ss << i << ", ";
		}
		EXPECT_EQ("1, 1, 3, 4, ", ss.str());
	}
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace extract_test

}	// namespace hamon_flat_multiset_test
