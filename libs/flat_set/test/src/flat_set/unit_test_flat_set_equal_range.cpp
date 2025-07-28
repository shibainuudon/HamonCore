/**
 *	@file	unit_test_flat_set_equal_range.cpp
 *
 *	@brief	equal_range のテスト
 *
 *	constexpr pair<iterator, iterator> equal_range(const key_type& x);
 *	constexpr pair<const_iterator, const_iterator> equal_range(const key_type& x) const;
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
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace equal_range_test
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
		using Iterator = typename Set::iterator;
		using ConstIterator = typename Set::const_iterator;

#if defined(HAMON_USE_STD_FLAT_SET)
		using Result = std::pair<Iterator, Iterator>;
		using ConstResult = std::pair<ConstIterator, ConstIterator>;
#else
		using Result = hamon::pair<Iterator, Iterator>;
		using ConstResult = hamon::pair<ConstIterator, ConstIterator>;
#endif
		static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().equal_range(hamon::declval<Key const&>())), ConstResult>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().equal_range(hamon::declval<Key const&>())), Result>::value, "");
		static_assert(!noexcept(hamon::declval<Set const&>().equal_range(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set&>().equal_range(hamon::declval<Key const&>())), "");

		Set v
		{
			Key{2},
			Key{1},
			Key{2},
			Key{4},
		};

		VERIFY(v.equal_range(Key{0}) == Result{v.begin() + 0, v.begin() + 0});
		VERIFY(v.equal_range(Key{1}) == Result{v.begin() + 0, v.begin() + 1});
		VERIFY(v.equal_range(Key{2}) == Result{v.begin() + 1, v.begin() + 2});
		VERIFY(v.equal_range(Key{3}) == Result{v.begin() + 2, v.begin() + 2});
		VERIFY(v.equal_range(Key{4}) == Result{v.begin() + 2, v.end()});
		VERIFY(v.equal_range(Key{5}) == Result{v.end(), v.end()});

		auto const& cv = v;
		VERIFY(cv.equal_range(Key{0}) == ConstResult{cv.begin() + 0, cv.begin() + 0});
		VERIFY(cv.equal_range(Key{1}) == ConstResult{cv.begin() + 0, cv.begin() + 1});
		VERIFY(cv.equal_range(Key{2}) == ConstResult{cv.begin() + 1, cv.begin() + 2});
		VERIFY(cv.equal_range(Key{3}) == ConstResult{cv.begin() + 2, cv.begin() + 2});
		VERIFY(cv.equal_range(Key{4}) == ConstResult{cv.begin() + 2, cv.end()});
		VERIFY(cv.equal_range(Key{5}) == ConstResult{cv.end(), cv.end()});
	}
	{
		using Set = hamon::flat_set<Key, hamon::greater<Key>, KeyContainer>;
		using Iterator = typename Set::iterator;
		using ConstIterator = typename Set::const_iterator;

#if defined(HAMON_USE_STD_FLAT_SET)
		using Result = std::pair<Iterator, Iterator>;
		using ConstResult = std::pair<ConstIterator, ConstIterator>;
#else
		using Result = hamon::pair<Iterator, Iterator>;
		using ConstResult = hamon::pair<ConstIterator, ConstIterator>;
#endif
		static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().equal_range(hamon::declval<Key const&>())), ConstResult>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().equal_range(hamon::declval<Key const&>())), Result>::value, "");
		static_assert(!noexcept(hamon::declval<Set const&>().equal_range(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set&>().equal_range(hamon::declval<Key const&>())), "");

		Set v
		{
			Key{2},
			Key{4},
			Key{1},
			Key{4},
			Key{1},
		};

		VERIFY(v.equal_range(Key{0}) == Result{v.end(), v.end()});
		VERIFY(v.equal_range(Key{1}) == Result{v.begin() + 2, v.end()});
		VERIFY(v.equal_range(Key{2}) == Result{v.begin() + 1, v.begin() + 2});
		VERIFY(v.equal_range(Key{3}) == Result{v.begin() + 1, v.begin() + 1});
		VERIFY(v.equal_range(Key{4}) == Result{v.begin() + 0, v.begin() + 1});
		VERIFY(v.equal_range(Key{5}) == Result{v.begin() + 0, v.begin() + 0});

		auto const& cv = v;
		VERIFY(cv.equal_range(Key{0}) == ConstResult{cv.end(), cv.end()});
		VERIFY(cv.equal_range(Key{1}) == ConstResult{cv.begin() + 2, cv.end()});
		VERIFY(cv.equal_range(Key{2}) == ConstResult{cv.begin() + 1, cv.begin() + 2});
		VERIFY(cv.equal_range(Key{3}) == ConstResult{cv.begin() + 1, cv.begin() + 1});
		VERIFY(cv.equal_range(Key{4}) == ConstResult{cv.begin() + 0, cv.begin() + 1});
		VERIFY(cv.equal_range(Key{5}) == ConstResult{cv.begin() + 0, cv.begin() + 0});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatSetTest, EqualRangeTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>>()));

	{
		hamon::flat_set<int> fs = {3, 1, 4};

		auto ret = fs.equal_range(3);

		std::stringstream ss;
		for (auto it = ret.first; it != ret.second; ++it)
		{
			ss << *it << ", ";
		}
		EXPECT_EQ("3, ", ss.str());
	}
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace equal_range_test

}	// namespace hamon_flat_set_test
