/**
 *	@file	unit_test_flat_set_begin_end.cpp
 *
 *	@brief	begin, end のテスト
 *
 *	constexpr iterator               begin() noexcept;
 *	constexpr const_iterator         begin() const noexcept;
 *	constexpr iterator               end() noexcept;
 *	constexpr const_iterator         end() const noexcept;
 *	constexpr const_iterator         cbegin() const noexcept;
 *	constexpr const_iterator         cend() const noexcept;
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace begin_end_test
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
	using Set = hamon::flat_set<Key, hamon::less<Key>, KeyContainer>;

	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().begin()),   Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().end()),     Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().cbegin()),  ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().cend()),    ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().begin()),  ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().end()),    ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().cbegin()), ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().cend()),   ConstIterator>::value, "");

	static_assert(noexcept(hamon::declval<Set&>().begin()), "");
	static_assert(noexcept(hamon::declval<Set&>().end()), "");
	static_assert(noexcept(hamon::declval<Set&>().cbegin()), "");
	static_assert(noexcept(hamon::declval<Set&>().cend()), "");
	static_assert(noexcept(hamon::declval<Set const&>().begin()), "");
	static_assert(noexcept(hamon::declval<Set const&>().end()), "");
	static_assert(noexcept(hamon::declval<Set const&>().cbegin()), "");
	static_assert(noexcept(hamon::declval<Set const&>().cend()), "");

	{
		Set v;
		{
			auto it = v.begin();
			VERIFY(it == v.begin());
			VERIFY(it == v.end());
		}
		{
			auto it = v.cbegin();
			VERIFY(it == v.cbegin());
			VERIFY(it == v.cend());
		}
		Set const cv;
		{
			auto it = cv.begin();
			VERIFY(it == cv.begin());
			VERIFY(it == cv.end());
		}
		{
			auto it = cv.cbegin();
			VERIFY(it == cv.cbegin());
			VERIFY(it == cv.cend());
		}
	}
	{
		Set v
		{
			Key{2},
			Key{3},
			Key{1},
		};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == Key{1});
		{
			auto t = ++it;
			VERIFY(*t == Key{2});
		}
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == Key{2});
		{
			auto t = it++;
			VERIFY(*t == Key{2});
		}
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == Key{3});
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
	}
	{
		Set const v
		{
			Key{4},
			Key{2},
			Key{3},
			Key{1},
		};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == Key{1});
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == Key{2});
		it++;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == Key{3});
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == Key{4});
		it++;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatSetTest, BeginEndTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>>()));

	{
		hamon::flat_set<int> fs = {3, 1, 4};

		std::stringstream ss;
		for (auto i = fs.begin(); i != fs.end(); ++i)
		{
			ss << *i << ", ";
		}
		EXPECT_EQ("1, 3, 4, ", ss.str());
	}
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace begin_end_test

}	// namespace hamon_flat_set_test
