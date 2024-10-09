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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using ForwardList = hamon::forward_list<T>;
	using Iterator = typename ForwardList::iterator;
	using ConstIterator = typename ForwardList::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<ForwardList&>().before_begin()), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ForwardList const&>().before_begin()), ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ForwardList&>().cbefore_begin()), ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ForwardList const&>().cbefore_begin()), ConstIterator>::value, "");

	static_assert(noexcept(hamon::declval<ForwardList&>().before_begin()), "");
	static_assert(noexcept(hamon::declval<ForwardList const&>().before_begin()), "");
	static_assert(noexcept(hamon::declval<ForwardList&>().cbefore_begin()), "");
	static_assert(noexcept(hamon::declval<ForwardList const&>().cbefore_begin()), "");

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
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace before_begin_test

}	// namespace hamon_forward_list_test
