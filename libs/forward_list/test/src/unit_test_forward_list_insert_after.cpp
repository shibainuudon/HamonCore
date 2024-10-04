/**
 *	@file	unit_test_forward_list_insert_after.cpp
 *
 *	@brief	insert_after のテスト
 *
 *	iterator insert_after(const_iterator position, const T& x);
 *	iterator insert_after(const_iterator position, T&& x);
 *	iterator insert_after(const_iterator position, size_type n, const T& x);
 *	template<class InputIterator>
 *	iterator insert_after(const_iterator position, InputIterator first, InputIterator last);
 *	iterator insert_after(const_iterator position, initializer_list<T> il);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace insert_after_test
{

struct S1
{
	int value;
};

HAMON_CXX11_CONSTEXPR bool
operator==(S1 const& lhs, S1 const& rhs)
{
	return lhs.value == rhs.value;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using ForwardList = hamon::forward_list<T>;
	using Iterator = typename ForwardList::iterator;
	using ConstIterator = typename ForwardList::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<ForwardList&>().insert_after(
			hamon::declval<ConstIterator>(),
			hamon::declval<T const&>())),
		Iterator
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<ForwardList&>().insert_after(
			hamon::declval<ConstIterator>(),
			hamon::declval<T const&>())), "");

	{
		ForwardList v;
		VERIFY(v.empty());

		{
			T x{10};
			auto ret = v.insert_after(v.before_begin(), x);
			VERIFY(ret == v.begin());
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
		{
			T x{20};
			auto ret = v.insert_after(v.before_begin(), x);
			VERIFY(ret == v.begin());
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
		{
			T x{30};
			auto ret = v.insert_after(v.begin(), x);
			VERIFY(ret == hamon::next(v.begin(), 1));
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{30});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test2()
{
	using ForwardList = hamon::forward_list<T>;
	using Iterator = typename ForwardList::iterator;
	using ConstIterator = typename ForwardList::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<ForwardList&>().insert_after(
			hamon::declval<ConstIterator>(),
			hamon::declval<T&&>())),
		Iterator
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<ForwardList&>().insert_after(
			hamon::declval<ConstIterator>(),
			hamon::declval<T&&>())), "");

	{
		ForwardList v;
		VERIFY(v.empty());

		{
			auto ret = v.insert_after(v.before_begin(), T{10});
			VERIFY(ret == v.begin());
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
		{
			auto ret = v.insert_after(v.begin(), T{20});
			VERIFY(ret == hamon::next(v.begin(), 1));
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(it == v.end());
		}
		{
			auto ret = v.insert_after(v.begin(), T{30});
			VERIFY(ret == hamon::next(v.begin(), 1));
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{30});
			VERIFY(*it++ == T{20});
			VERIFY(it == v.end());
		}
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test3()
{
	using ForwardList = hamon::forward_list<T>;
	using Iterator = typename ForwardList::iterator;
	using ConstIterator = typename ForwardList::const_iterator;
	using SizeType = typename ForwardList::size_type;

	static_assert(hamon::is_same<
		decltype(hamon::declval<ForwardList&>().insert_after(
			hamon::declval<ConstIterator>(),
			hamon::declval<SizeType>(),
			hamon::declval<T const&>())),
		Iterator
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<ForwardList&>().insert_after(
			hamon::declval<ConstIterator>(),
			hamon::declval<SizeType>(),
			hamon::declval<T const&>())), "");

	{
		ForwardList v;
		VERIFY(v.empty());

		{
			T x{10};
			auto ret = v.insert_after(v.before_begin(), 2, x);
			VERIFY(ret == hamon::next(v.begin(), 1));
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
		{
			T x{20};
			auto ret = v.insert_after(v.begin(), 3, x);
			VERIFY(ret == hamon::next(v.begin(), 3));
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test4()
{
	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test5()
{
	using ForwardList = hamon::forward_list<T>;
	using Iterator = typename ForwardList::iterator;
	using ConstIterator = typename ForwardList::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<ForwardList&>().insert_after(
			hamon::declval<ConstIterator>(),
			hamon::declval<std::initializer_list<T>>())),
		Iterator
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<ForwardList&>().insert_after(
			hamon::declval<ConstIterator>(),
			hamon::declval<std::initializer_list<T>>())), "");

	{
		ForwardList v;
		VERIFY(v.empty());

		{
			auto ret = v.insert_after(v.before_begin(), {T{1},T{2},T{3}});
			VERIFY(ret == hamon::next(v.begin(), 2));
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(it == v.end());
		}
		{
			auto ret = v.insert_after(v.begin(), {T{4},T{5}});
			VERIFY(ret == hamon::next(v.begin(), 2));
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(it == v.end());
		}
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	VERIFY(test1<T>());
	VERIFY(test2<T>());
	VERIFY(test3<T>());
	VERIFY(test4<T>());
	VERIFY(test5<T>());
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, InsertAfterTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
}

}	// namespace insert_after_test

}	// namespace hamon_forward_list_test
