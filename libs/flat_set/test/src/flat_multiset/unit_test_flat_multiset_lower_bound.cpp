/**
 *	@file	unit_test_flat_multiset_lower_bound.cpp
 *
 *	@brief	lower_bound のテスト
 *
 *	constexpr iterator lower_bound(const key_type& x);
 *	constexpr const_iterator lower_bound(const key_type& x) const;
 */

#include <hamon/flat_set/flat_multiset.hpp>
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
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace lower_bound_test
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

		static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().lower_bound(hamon::declval<Key const&>())), typename Set::const_iterator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().lower_bound(hamon::declval<Key const&>())), typename Set::iterator>::value, "");
		static_assert(!noexcept(hamon::declval<Set const&>().lower_bound(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set&>().lower_bound(hamon::declval<Key const&>())), "");

		Set v
		{
			Key{3},
			Key{1},
			Key{2},
			Key{2},
			Key{3},
			Key{2},
		};
		// 1, 2, 2, 2, 3, 3

		VERIFY(v.lower_bound(Key{0}) == (v.begin() + 0));
		VERIFY(v.lower_bound(Key{1}) == (v.begin() + 0));
		VERIFY(v.lower_bound(Key{2}) == (v.begin() + 1));
		VERIFY(v.lower_bound(Key{3}) == (v.begin() + 4));
		VERIFY(v.lower_bound(Key{4}) == v.end());

		auto const& cv = v;
		VERIFY(cv.lower_bound(Key{0}) == (cv.begin() + 0));
		VERIFY(cv.lower_bound(Key{1}) == (cv.begin() + 0));
		VERIFY(cv.lower_bound(Key{2}) == (cv.begin() + 1));
		VERIFY(cv.lower_bound(Key{3}) == (cv.begin() + 4));
		VERIFY(cv.lower_bound(Key{4}) == cv.end());
	}
	{
		using Set = hamon::flat_multiset<Key, hamon::greater<Key>, KeyContainer>;

		static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().lower_bound(hamon::declval<Key const&>())), typename Set::const_iterator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().lower_bound(hamon::declval<Key const&>())), typename Set::iterator>::value, "");
		static_assert(!noexcept(hamon::declval<Set const&>().lower_bound(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set&>().lower_bound(hamon::declval<Key const&>())), "");

		Set v
		{
			Key{3},
			Key{1},
			Key{4},
			Key{1},
			Key{5},
			Key{3},
		};
		// 5, 4, 3, 3, 1, 1

		VERIFY(v.lower_bound(Key{0}) == v.end());
		VERIFY(v.lower_bound(Key{1}) == (v.begin() + 4));
		VERIFY(v.lower_bound(Key{2}) == (v.begin() + 4));
		VERIFY(v.lower_bound(Key{3}) == (v.begin() + 2));
		VERIFY(v.lower_bound(Key{4}) == (v.begin() + 1));
		VERIFY(v.lower_bound(Key{5}) == (v.begin() + 0));
		VERIFY(v.lower_bound(Key{6}) == (v.begin() + 0));

		auto const& cv = v;
		VERIFY(cv.lower_bound(Key{0}) == cv.end());
		VERIFY(cv.lower_bound(Key{1}) == (cv.begin() + 4));
		VERIFY(cv.lower_bound(Key{2}) == (cv.begin() + 4));
		VERIFY(cv.lower_bound(Key{3}) == (cv.begin() + 2));
		VERIFY(cv.lower_bound(Key{4}) == (cv.begin() + 1));
		VERIFY(cv.lower_bound(Key{5}) == (cv.begin() + 0));
		VERIFY(cv.lower_bound(Key{6}) == (cv.begin() + 0));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultisetTest, LowerBoundTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>>()));

	{
		hamon::flat_multiset<hamon::string> fs = {
			"Alice", "Bob", "Carol", "David"
		};

		// Bob以上David以下の範囲を取得
		decltype(fs)::iterator it = fs.lower_bound("Bob");
		decltype(fs)::iterator last = fs.upper_bound("David");

		std::stringstream ss;
		while (it != last)
		{
			ss << *it << ", ";
			++it;
		}
		EXPECT_EQ("Bob, Carol, David, ", ss.str());
	}
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace lower_bound_test

}	// namespace hamon_flat_multiset_test
