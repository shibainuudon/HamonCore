/**
 *	@file	unit_test_list_begin_end.cpp
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

#include <hamon/list/list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace begin_end_test
{

#if !defined(HAMON_USE_STD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
LIST_TEST_CONSTEXPR bool test()
{
	using List = hamon::list<T>;
	using Iterator = typename List::iterator;
	using ConstIterator = typename List::const_iterator;

	{
		List v;
		List const cv;
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
		List v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		List const v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		List v;
		auto it = v.cbegin();
		VERIFY(it == v.cbegin());
		VERIFY(it == v.cend());
	}
	{
		List v{1,2,3};
		{
			auto it = v.begin();
			VERIFY(it == v.begin());
			VERIFY(it != v.end());
			VERIFY(*it == 1);
			++it;
			VERIFY(it != v.begin());
			VERIFY(it != v.end());
			VERIFY(*it == 2);
			*it = 10;
			++it;
			VERIFY(it != v.begin());
			VERIFY(it != v.end());
			VERIFY(*it == 3);
			--it;
			VERIFY(it != v.begin());
			VERIFY(it != v.end());
			VERIFY(*it == 10);
			++it;
			VERIFY(it != v.begin());
			VERIFY(it != v.end());
			VERIFY(*it == 3);
			++it;
			VERIFY(it != v.begin());
			VERIFY(it == v.end());
		}
		{
			auto it = v.begin();
			VERIFY(*it++ == 1);
			VERIFY(*it++ == 10);
			VERIFY(*it-- == 3);
			VERIFY(*it-- == 10);
			VERIFY(*it   == 1);
			VERIFY(it == v.begin());
		}
		{
			auto it = v.begin();
			VERIFY(*(++it) == 10);
			VERIFY(*(++it) == 3);
			VERIFY(*(--it) == 10);
			VERIFY(*(--it) == 1);
			VERIFY(*(++it) == 10);
			VERIFY(*(++it) == 3);
			VERIFY(++it == v.end());
		}
	}
	{
		List const v{11,12,13,14};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 11);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 12);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 13);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 14);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
	}
	{
		List v{1,2,3};
		auto it = v.cbegin();
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, BeginEndTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace begin_end_test

}	// namespace hamon_list_test
