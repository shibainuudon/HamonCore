/**
 *	@file	unit_test_forward_list_splice_after.cpp
 *
 *	@brief	splice_after のテスト
 *
 *	void splice_after(const_iterator position, forward_list& x);
 *	void splice_after(const_iterator position, forward_list&& x);
 *	void splice_after(const_iterator position, forward_list& x, const_iterator i);
 *	void splice_after(const_iterator position, forward_list&& x, const_iterator i);
 *	void splice_after(const_iterator position, forward_list& x, const_iterator first, const_iterator last);
 *	void splice_after(const_iterator position, forward_list&& x, const_iterator first, const_iterator last);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace splice_after_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using ForwardList = hamon::forward_list<T>;
	using ConstIterator = typename ForwardList::const_iterator;

	{
		ForwardList v;
		ConstIterator pos;
		ForwardList x;
		static_assert(hamon::is_same<decltype(v.splice_after(pos, x)), void>::value, "");
		static_assert( noexcept(v.splice_after(pos, x)), "");
	}
	{
		ForwardList v1{1,2,3,4,5};
		ForwardList v2{10,11,12};
		v2.splice_after(v2.cbefore_begin(), v1);

		VERIFY(v1.empty());
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
	}
	{
		ForwardList v1;
		ForwardList v2{10,11,12};
		v2.splice_after(v2.cbefore_begin(), v1);

		VERIFY(v1.empty());
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
	}
	{
		ForwardList v1{1,2,3,4,5};
		ForwardList v2;
		v2.splice_after(v2.cbefore_begin(), v1);

		VERIFY(v1.empty());
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v2.end());
		}
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test2()
{
	using ForwardList = hamon::forward_list<T>;
	using ConstIterator = typename ForwardList::const_iterator;

	{
		ForwardList v;
		ConstIterator pos;
		ForwardList x;
		static_assert(hamon::is_same<decltype(v.splice_after(pos, hamon::move(x))), void>::value, "");
		static_assert( noexcept(v.splice_after(pos, hamon::move(x))), "");
	}
	{
		ForwardList v1{1,2,3,4,5};
		ForwardList v2{10,11,12};
		v2.splice_after(v2.cbegin(), hamon::move(v1));

		VERIFY(v1.empty());
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
	}
	{
		ForwardList v1;
		ForwardList v2{10,11,12};
		v2.splice_after(v2.cbefore_begin(), hamon::move(v1));

		VERIFY(v1.empty());
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
	}
	{
		ForwardList v1{1,2,3,4,5};
		ForwardList v2;
		v2.splice_after(v2.cbefore_begin(), hamon::move(v1));

		VERIFY(v1.empty());
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v2.end());
		}
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test3()
{
	using ForwardList = hamon::forward_list<T>;
	using ConstIterator = typename ForwardList::const_iterator;

	{
		ForwardList v;
		ConstIterator pos;
		ForwardList x;
		ConstIterator i;
		static_assert(hamon::is_same<decltype(v.splice_after(pos, x, i)), void>::value, "");
		static_assert( noexcept(v.splice_after(pos, x, i)), "");
	}
	{
		ForwardList v1{1,2,3,4,5};
		ForwardList v2{10,11,12};
		v2.splice_after(v2.cbefore_begin(), v1, v1.begin());

		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test4()
{
	using ForwardList = hamon::forward_list<T>;
	using ConstIterator = typename ForwardList::const_iterator;

	{
		ForwardList v;
		ConstIterator pos;
		ForwardList x;
		ConstIterator i;
		static_assert(hamon::is_same<decltype(v.splice_after(pos, hamon::move(x), i)), void>::value, "");
		static_assert( noexcept(v.splice_after(pos, hamon::move(x), i)), "");
	}
	{
		ForwardList v1{1,2,3,4,5};
		ForwardList v2{10,11,12};
		v2.splice_after(v2.cbegin(), hamon::move(v1), v1.cbegin());

		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test5()
{
	using ForwardList = hamon::forward_list<T>;
	using ConstIterator = typename ForwardList::const_iterator;

	{
		ForwardList v;
		ConstIterator pos;
		ForwardList x;
		ConstIterator first;
		ConstIterator last;
		static_assert(hamon::is_same<decltype(v.splice_after(pos, x, first, last)), void>::value, "");
		static_assert( noexcept(v.splice_after(pos, x, first, last)), "");
	}
	{
		ForwardList v1{1,2,3,4,5};
		ForwardList v2{10,11,12};
		v2.splice_after(v2.cbefore_begin(), v1, v1.cbefore_begin(), v1.cend());

		VERIFY(v1.empty());

		{
			auto it = v2.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
	}
	{
		ForwardList v1{1,2,3,4,5};
		ForwardList v2{10,11,12};
		v2.splice_after(v2.begin(), v1, v1.begin(), v1.end());

		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
	}
	{
		ForwardList v1{1,2,3,4,5};
		ForwardList v2{10,11,12};
		v2.splice_after(hamon::next(v2.begin(), 1), v1, hamon::next(v1.begin(), 1), hamon::next(v1.begin(), 4));

		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{5});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
	}
	{
		ForwardList v1{1,2,3,4,5};
		ForwardList v2{10,11,12};
		v2.splice_after(v2.before_begin(), v1, v1.before_begin(), v1.begin());

		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test6()
{
	using ForwardList = hamon::forward_list<T>;
	using ConstIterator = typename ForwardList::const_iterator;

	{
		ForwardList v;
		ConstIterator pos;
		ForwardList x;
		ConstIterator first;
		ConstIterator last;
		static_assert(hamon::is_same<decltype(v.splice_after(pos, hamon::move(x), first, last)), void>::value, "");
		static_assert( noexcept(v.splice_after(pos, hamon::move(x), first, last)), "");
	}
	{
		ForwardList v1{1,2,3,4,5};
		ForwardList v2{10,11,12};
		v2.splice_after(v2.begin(), hamon::move(v1), hamon::next(v1.begin(), 1), v1.end());

		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
	}
	{
		ForwardList v1{1,2,3,4,5};
		ForwardList v2{10,11,12};
		v2.splice_after(hamon::next(v2.begin(), 2), hamon::move(v1), v1.begin(), v1.end());

		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v2.end());
		}
	}
	{
		ForwardList v1{1,2,3,4,5};
		ForwardList v2{10,11,12};
		v2.splice_after(hamon::next(v2.begin(), 2), hamon::move(v1), v1.begin(), hamon::next(v1.begin(), 1));

		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
	}
	{
		ForwardList v1{1,2,3,4,5};
		ForwardList v2{10,11,12};
		v2.splice_after(hamon::next(v2.begin(), 1), hamon::move(v1), hamon::next(v1.begin(), 1), hamon::next(v1.begin(), 3));

		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, SpliceAfterTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<float>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2<float>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3<float>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4<float>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test5<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test5<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test5<float>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test6<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test6<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test6<float>());
}

}	// namespace splice_after_test

}	// namespace hamon_forward_list_test
