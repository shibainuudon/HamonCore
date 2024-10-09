/**
 *	@file	unit_test_forward_list_begin_end.cpp
 *
 *	@brief	begin_end のテスト
 *
 *	iterator begin() noexcept;
 *	const_iterator begin() const noexcept;
 *	iterator end() noexcept;
 *	const_iterator end() const noexcept;
 *
 *	const_iterator cbegin() const noexcept;
 *	const_iterator cend() const noexcept;
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace begin_end_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using ForwardList = hamon::forward_list<T>;
	using Iterator = typename ForwardList::iterator;
	using ConstIterator = typename ForwardList::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<ForwardList&>().begin()), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ForwardList&>().end()),   Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ForwardList const&>().begin()), ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ForwardList const&>().end()),   ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ForwardList&>().cbegin()), ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ForwardList&>().cend()),   ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ForwardList const&>().cbegin()), ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ForwardList const&>().cend()),   ConstIterator>::value, "");

	static_assert(noexcept(hamon::declval<ForwardList&>().begin()), "");
	static_assert(noexcept(hamon::declval<ForwardList&>().end()), "");
	static_assert(noexcept(hamon::declval<ForwardList const&>().begin()), "");
	static_assert(noexcept(hamon::declval<ForwardList const&>().end()), "");
	static_assert(noexcept(hamon::declval<ForwardList&>().cbegin()), "");
	static_assert(noexcept(hamon::declval<ForwardList&>().cend()), "");
	static_assert(noexcept(hamon::declval<ForwardList const&>().cbegin()), "");
	static_assert(noexcept(hamon::declval<ForwardList const&>().cend()), "");

	{
		ForwardList v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		ForwardList const v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		ForwardList v;
		auto it = v.cbegin();
		VERIFY(it == v.cbegin());
		VERIFY(it == v.cend());
	}
	{
		ForwardList v{1,2,3};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
	}
	{
		ForwardList const v{11,12,13,14};
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
		ForwardList v{1,2,3};
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

GTEST_TEST(ForwardListTest, BeginEndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace begin_end_test

}	// namespace hamon_forward_list_test
