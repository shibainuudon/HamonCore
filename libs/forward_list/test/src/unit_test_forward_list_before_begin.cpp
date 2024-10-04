/**
 *	@file	unit_test_forward_list_before_begin.cpp
 *
 *	@brief	before_begin のテスト
 *
 *	iterator before_begin() noexcept;
 *	const_iterator before_begin() const noexcept;
 *
 *	const_iterator cbefore_begin() const noexcept;
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace before_begin_test
{

#if !defined(HAMON_USE_STD_FORWARD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// MSVCでconstexprにすると内部コンパイラエラーになってしまう TODO
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test()
{
	using ForwardList = hamon::forward_list<T>;
	using Iterator = typename ForwardList::iterator;
	using ConstIterator = typename ForwardList::const_iterator;

	{
		ForwardList v;
		ForwardList const cv;
		static_assert(hamon::is_same<decltype(v.before_begin()), Iterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.before_begin()), ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(v.cbefore_begin()), ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.cbefore_begin()), ConstIterator>::value, "");

		static_assert(noexcept(v.before_begin()), "");
		static_assert(noexcept(cv.before_begin()), "");
		static_assert(noexcept(v.cbefore_begin()), "");
		static_assert(noexcept(cv.cbefore_begin()), "");
	}
	{
		ForwardList v;
		auto it = v.before_begin();
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		++it;
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		ForwardList const v;
		auto it = v.before_begin();
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		++it;
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		ForwardList v;
		auto it = v.cbefore_begin();
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		++it;
		VERIFY(it == v.cbegin());
		VERIFY(it == v.cend());
	}
	{
		ForwardList v{1,2,3};
		auto it = v.before_begin();
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		++it;
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
	}
	{
		ForwardList const v{1,2,3};
		auto it = v.before_begin();
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		++it;
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
	}
	{
		ForwardList v{1,2,3};
		auto it = v.cbefore_begin();
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		++it;
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, BeforeBeginTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace before_begin_test

}	// namespace hamon_forward_list_test
