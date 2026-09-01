/**
 *	@file	unit_test_set_begin_end.cpp
 *
 *	@brief	begin, end のテスト
 *
 *	iterator               begin() noexcept;
 *	const_iterator         begin() const noexcept;
 *	iterator               end() noexcept;
 *	const_iterator         end() const noexcept;
 *	const_iterator         cbegin() const noexcept;
 *	const_iterator         cend() const noexcept;
 */

#include <hamon/set/set.hpp>
#include <hamon/algorithm.hpp>
#include <hamon/sstream/stringstream.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace begin_end_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::set<Key>;
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	{
		Set v;
		Set const cv;
		static_assert(hamon::is_same<decltype(v.begin()),   Iterator>::value, "");
		static_assert(hamon::is_same<decltype(v.end()),     Iterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.begin()),  ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.end()),    ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(v.cbegin()),  ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(v.cend()),    ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.cbegin()), ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.cend()),   ConstIterator>::value, "");

		static_assert(noexcept(v.begin()), "");
		static_assert(noexcept(v.end()), "");
		static_assert(noexcept(cv.begin()), "");
		static_assert(noexcept(cv.end()), "");
		static_assert(noexcept(v.cbegin()), "");
		static_assert(noexcept(v.cend()), "");
		static_assert(noexcept(cv.cbegin()), "");
		static_assert(noexcept(cv.cend()), "");
	}
	{
		Set v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		Set const v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		Set v;
		auto it = v.cbegin();
		VERIFY(it == v.cbegin());
		VERIFY(it == v.cend());
	}
	{
		Set v
		{
			Key{1},
			Key{4},
			Key{1},
			Key{4},
			Key{2},
			Key{1},
		};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == Key{1});
		VERIFY(*(++it) == Key{2});
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*(it++) == Key{2});
		VERIFY(*it == Key{4});
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
		VERIFY(*(--it) == Key{4});
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*(it--) == Key{4});
		VERIFY(*it == Key{2});
	}
	{
		Set const v
		{
			Key{1},
			Key{4},
			Key{1},
			Key{4},
			Key{2},
			Key{1},
		};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == Key{1});
		VERIFY(*(++it) == Key{2});
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*(it++) == Key{2});
		VERIFY(*it == Key{4});
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
		VERIFY(*(--it) == Key{4});
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*(it--) == Key{4});
		VERIFY(*it == Key{2});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, BeginEndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/set/begin
	{
		hamon::set<int> set {3, 1, 4, 1, 5, 9, 2, 6, 5};
		hamon::stringstream out;
		hamon::for_each(set.cbegin(), set.cend(), [&](int x)
		{
			out << x << ' ';
		});
		EXPECT_EQ("1 2 3 4 5 6 9 ", out.str());
	}
}

}	// namespace begin_end_test

}	// namespace hamon_set_test
