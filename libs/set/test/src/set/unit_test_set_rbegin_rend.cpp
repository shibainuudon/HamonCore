/**
 *	@file	unit_test_set_rbegin_rend.cpp
 *
 *	@brief	rbegin, rend のテスト
 *
 *	reverse_iterator       rbegin() noexcept;
 *	const_reverse_iterator rbegin() const noexcept;
 *	reverse_iterator       rend() noexcept;
 *	const_reverse_iterator rend() const noexcept;
 *	const_reverse_iterator crbegin() const noexcept;
 *	const_reverse_iterator crend() const noexcept;
 */

#include <hamon/set/set.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <sstream>

namespace hamon_set_test
{

namespace rbegin_rend_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::set<Key>;
	using ReverseIterator = typename Set::reverse_iterator;
	using ConstReverseIterator = typename Set::const_reverse_iterator;

	{
		Set v;
		Set const cv;
		static_assert(hamon::is_same<decltype(v.rbegin()),   ReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(v.rend()),     ReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.rbegin()),  ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.rend()),    ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(v.crbegin()),  ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(v.crend()),    ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.crbegin()), ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.crend()),   ConstReverseIterator>::value, "");

		static_assert(noexcept(v.rbegin()), "");
		static_assert(noexcept(v.rend()), "");
		static_assert(noexcept(cv.rbegin()), "");
		static_assert(noexcept(cv.rend()), "");
		static_assert(noexcept(v.crbegin()), "");
		static_assert(noexcept(v.crend()), "");
		static_assert(noexcept(cv.crbegin()), "");
		static_assert(noexcept(cv.crend()), "");
	}
	{
		Set v;
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it == v.rend());
	}
	{
		Set const v;
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it == v.rend());
	}
	{
		Set v;
		auto it = v.crbegin();
		VERIFY(it == v.crbegin());
		VERIFY(it == v.crend());
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
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it == v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == Key{4});
		VERIFY(*(++it) == Key{2});
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*(it++) == Key{2});
		VERIFY(*it == Key{1});
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it == v.crend());
		VERIFY(*(--it) == Key{1});
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*(it--) == Key{1});
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
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it == v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == Key{4});
		VERIFY(*(++it) == Key{2});
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*(it++) == Key{2});
		VERIFY(*it == Key{1});
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it == v.crend());
		VERIFY(*(--it) == Key{1});
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*(it--) == Key{1});
		VERIFY(*it == Key{2});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, RBeginREndTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/set/rbegin
	{
		hamon::set<unsigned> rep {1, 2, 3, 4, 1, 2, 3, 4};
		std::stringstream out;
		for (auto it = rep.crbegin(); it != rep.crend(); ++it)
		{
			out << *it << ' ';
		};
		EXPECT_EQ("4 3 2 1 ", out.str());
	}
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace rbegin_rend_test

}	// namespace hamon_set_test
