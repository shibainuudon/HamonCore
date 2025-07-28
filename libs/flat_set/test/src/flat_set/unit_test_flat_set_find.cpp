/**
 *	@file	unit_test_flat_set_find.cpp
 *
 *	@brief	find のテスト
 *
 *	constexpr iterator find(const key_type& x);
 *	constexpr const_iterator find(const key_type& x) const;
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace find_test
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
		using Set = hamon::flat_set<Key, hamon::less<Key>, KeyContainer>;

		static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), typename Set::const_iterator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().find(hamon::declval<Key const&>())), typename Set::iterator>::value, "");
		static_assert(!noexcept(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set&>().find(hamon::declval<Key const&>())), "");

		Set v
		{
			Key{3},
			Key{6},
			Key{1},
			Key{4},
		};

		VERIFY(v.find(Key{0}) == v.end());
		VERIFY(v.find(Key{1}) == (v.begin() + 0));
		VERIFY(v.find(Key{2}) == v.end());
		VERIFY(v.find(Key{3}) == (v.begin() + 1));
		VERIFY(v.find(Key{4}) == (v.begin() + 2));
		VERIFY(v.find(Key{5}) == v.end());
		VERIFY(v.find(Key{6}) == (v.begin() + 3));
		VERIFY(v.find(Key{7}) == v.end());

		auto const& cv = v;
		VERIFY(cv.find(Key{0}) == cv.end());
		VERIFY(cv.find(Key{1}) == (cv.begin() + 0));
		VERIFY(cv.find(Key{2}) == cv.end());
		VERIFY(cv.find(Key{3}) == (cv.begin() + 1));
		VERIFY(cv.find(Key{4}) == (cv.begin() + 2));
		VERIFY(cv.find(Key{5}) == cv.end());
		VERIFY(cv.find(Key{6}) == (cv.begin() + 3));
		VERIFY(cv.find(Key{7}) == cv.end());
	}
	{
		using Set = hamon::flat_set<Key, hamon::greater<Key>, KeyContainer>;

		static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), typename Set::const_iterator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().find(hamon::declval<Key const&>())), typename Set::iterator>::value, "");
		static_assert(!noexcept(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set&>().find(hamon::declval<Key const&>())), "");

		Set v
		{
			Key{3},
			Key{6},
			Key{1},
			Key{4},
		};

		VERIFY(v.find(Key{0}) == v.end());
		VERIFY(v.find(Key{1}) == (v.begin() + 3));
		VERIFY(v.find(Key{2}) == v.end());
		VERIFY(v.find(Key{3}) == (v.begin() + 2));
		VERIFY(v.find(Key{4}) == (v.begin() + 1));
		VERIFY(v.find(Key{5}) == v.end());
		VERIFY(v.find(Key{6}) == (v.begin() + 0));
		VERIFY(v.find(Key{7}) == v.end());

		auto const& cv = v;
		VERIFY(cv.find(Key{0}) == cv.end());
		VERIFY(cv.find(Key{1}) == (cv.begin() + 3));
		VERIFY(cv.find(Key{2}) == cv.end());
		VERIFY(cv.find(Key{3}) == (cv.begin() + 2));
		VERIFY(cv.find(Key{4}) == (cv.begin() + 1));
		VERIFY(cv.find(Key{5}) == cv.end());
		VERIFY(cv.find(Key{6}) == (cv.begin() + 0));
		VERIFY(cv.find(Key{7}) == cv.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatSetTest, FindTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<char>>()));

	{
		hamon::flat_set<hamon::string> fs = {"Alice", "Bob", "Carol"};

		decltype(fs)::iterator it = fs.find("Bob");
		EXPECT_TRUE(it != fs.end());
		EXPECT_EQ("Bob", *it);
	}
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace find_test

}	// namespace hamon_flat_set_test
