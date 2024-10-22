/**
 *	@file	unit_test_list_splice.cpp
 *
 *	@brief	splice のテスト
 *
 *	void splice(const_iterator position, list& x);
 *	void splice(const_iterator position, list&& x);
 *	void splice(const_iterator position, list& x, const_iterator i);
 *	void splice(const_iterator position, list&& x, const_iterator i);
 *	void splice(const_iterator position, list& x, const_iterator first, const_iterator last);
 *	void splice(const_iterator position, list&& x, const_iterator first, const_iterator last);
 */

#include <hamon/list/list.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace splice_test
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
LIST_TEST_CONSTEXPR bool test1()
{
	using List = hamon::list<T>;
	using ConstIterator = typename List::const_iterator;

	{
		List v;
		ConstIterator pos;
		List x;
		static_assert(hamon::is_same<decltype(v.splice(pos, x)), void>::value, "");
#if !defined(HAMON_USE_STD_LIST)
		static_assert( noexcept(v.splice(pos, x)), "");
#endif
	}
	{
		List v1;
		List v2;
		v2.splice(v2.begin(), v1);
		VERIFY(v1.empty());
		VERIFY(v2.empty());
		VERIFY(v1.size() == 0);
		VERIFY(v2.size() == 0);
		VERIFY(v1.begin() == v1.end());
		VERIFY(v1.rbegin() == v1.rend());
		VERIFY(v2.begin() == v2.end());
		VERIFY(v2.rbegin() == v2.rend());
	}
	{
		List v1{1,2,3,4,5};
		List v2{10,11,12};
		v2.splice(v2.begin(), v1);
		VERIFY(v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 0);
		VERIFY(v2.size() == 8);
		VERIFY(v1.begin() == v1.end());
		VERIFY(v1.rbegin() == v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
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
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v2.rend());
		}
	}
	{
		List v1;
		List v2{10,11,12};
		v2.splice(v2.begin(), v1);
		VERIFY(v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 0);
		VERIFY(v2.size() == 3);
		VERIFY(v1.begin() == v1.end());
		VERIFY(v1.rbegin() == v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{10});
			VERIFY(it == v2.rend());
		}
	}
	{
		List v1{1,2,3,4,5};
		List v2;
		v2.splice(v2.begin(), v1);
		VERIFY(v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 0);
		VERIFY(v2.size() == 5);
		VERIFY(v1.begin() == v1.end());
		VERIFY(v1.rbegin() == v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v2.end());
		}
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v2.rend());
		}
	}

	return true;
}

template <typename T>
LIST_TEST_CONSTEXPR bool test2()
{
	using List = hamon::list<T>;
	using ConstIterator = typename List::const_iterator;

	{
		List v;
		ConstIterator pos;
		List x;
		static_assert(hamon::is_same<decltype(v.splice(pos, hamon::move(x))), void>::value, "");
#if !defined(HAMON_USE_STD_LIST)
		static_assert( noexcept(v.splice(pos, hamon::move(x))), "");
#endif
	}
	{
		List v1{1,2,3,4,5};
		List v2{10,11,12};
		v2.splice(hamon::next(v2.cbegin(), 1), hamon::move(v1));
		VERIFY(v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 0);
		VERIFY(v2.size() == 8);
		VERIFY(v1.begin() == v1.end());
		VERIFY(v1.rbegin() == v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
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
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{10});
			VERIFY(it == v2.rend());
		}
	}
	{
		List v1;
		List v2{10,11,12};
		v2.splice(v2.begin(), hamon::move(v1));
		VERIFY(v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 0);
		VERIFY(v2.size() == 3);
		VERIFY(v1.begin() == v1.end());
		VERIFY(v1.rbegin() == v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{10});
			VERIFY(it == v2.rend());
		}
	}
	{
		List v1{1,2,3,4,5};
		List v2;
		v2.splice(v2.end(), hamon::move(v1));
		VERIFY(v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 0);
		VERIFY(v2.size() == 5);
		VERIFY(v1.begin() == v1.end());
		VERIFY(v1.rbegin() == v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v2.end());
		}
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v2.rend());
		}
	}

	return true;
}

template <typename T>
LIST_TEST_CONSTEXPR bool test3()
{
	using List = hamon::list<T>;
	using ConstIterator = typename List::const_iterator;

	{
		List v;
		ConstIterator pos;
		List x;
		ConstIterator i;
		static_assert(hamon::is_same<decltype(v.splice(pos, x, i)), void>::value, "");
#if !defined(HAMON_USE_STD_LIST)
		static_assert( noexcept(v.splice(pos, x, i)), "");
#endif
	}
	{
		List v1{1,2,3,4,5};
		List v2{10,11,12};
		v2.splice(v2.begin(), v1, v1.begin());
		VERIFY(!v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 4);
		VERIFY(v2.size() == 4);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
		{
			auto it = v1.begin();
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v1.end());
		}
		{
			auto it = v1.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(it == v1.rend());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{1});
			VERIFY(it == v2.rend());
		}
	}
	{
		List v1{1,2,3,4,5};
		List v2;
		v2.splice(v2.end(), v1, hamon::next(v1.begin(), 1));
		VERIFY(!v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 4);
		VERIFY(v2.size() == 1);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v1.end());
		}
		{
			auto it = v1.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.rend());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{2});
			VERIFY(it == v2.end());
		}
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{2});
			VERIFY(it == v2.rend());
		}
	}
	{
		List v{1,2,3,4,5};
		v.splice(v.begin(), v, v.begin());
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.rend());
		}
	}
	{
		List v{1,2,3,4,5};
		v.splice(hamon::next(v.begin(), 1), v, v.begin());
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v.end());
		}
	}
	{
		List v{1,2,3,4,5};
		v.splice(v.begin(), v, hamon::next(v.begin(), 1));
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(it == v.rend());
		}
	}
	{
		List v{1,2,3,4,5};
		v.splice(hamon::next(v.begin(), 3), v, hamon::next(v.begin(), 1));
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.rend());
		}
	}
	{
		List v{1,2,3,4,5};
		v.splice(v.end(), v, v.begin());
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(it == v.rend());
		}
	}

	return true;
}

template <typename T>
LIST_TEST_CONSTEXPR bool test4()
{
	using List = hamon::list<T>;
	using ConstIterator = typename List::const_iterator;

	{
		List v;
		ConstIterator pos;
		List x;
		ConstIterator i;
		static_assert(hamon::is_same<decltype(v.splice(pos, hamon::move(x), i)), void>::value, "");
#if !defined(HAMON_USE_STD_LIST)
		static_assert( noexcept(v.splice(pos, hamon::move(x), i)), "");
#endif
	}
	{
		List v1{1,2,3,4,5};
		List v2{10,11,12};
		v2.splice(v2.cend(), hamon::move(v1), v1.cbegin());
		VERIFY(!v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 4);
		VERIFY(v2.size() == 4);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
		{
			auto it = v1.begin();
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v1.end());
		}
		{
			auto it = v1.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(it == v1.rend());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{1});
			VERIFY(it == v2.end());
		}
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{10});
			VERIFY(it == v2.rend());
		}
	}
	{
		List v1{1,2,3,4,5};
		List v2;
		v2.splice(v2.begin(), hamon::move(v1), hamon::next(v1.begin(), 2));
		VERIFY(!v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 4);
		VERIFY(v2.size() == 1);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v1.end());
		}
		{
			auto it = v1.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.rend());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{3});
			VERIFY(it == v2.end());
		}
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{3});
			VERIFY(it == v2.rend());
		}
	}

	return true;
}

template <typename T>
LIST_TEST_CONSTEXPR bool test5()
{
	using List = hamon::list<T>;
	using ConstIterator = typename List::const_iterator;

	{
		List v;
		ConstIterator pos;
		List x;
		ConstIterator first;
		ConstIterator last;
		static_assert(hamon::is_same<decltype(v.splice(pos, x, first, last)), void>::value, "");
#if !defined(HAMON_USE_STD_LIST)
		static_assert( noexcept(v.splice(pos, x, first, last)), "");
#endif
	}
	{
		List v1{1,2,3,4,5};
		List v2{10,11,12};
		v2.splice(v2.begin(), v1, v1.begin(), v1.cend());
		VERIFY(v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 0);
		VERIFY(v2.size() == 8);
		VERIFY(v1.begin() == v1.end());
		VERIFY(v1.rbegin() == v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
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
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v2.rend());
		}
	}
	{
		List v1{1,2,3,4,5};
		List v2{10,11,12};
		v2.splice(v2.end(), v1, hamon::next(v1.begin(), 1), v1.end());
		VERIFY(!v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 1);
		VERIFY(v2.size() == 7);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.end());
		}
		{
			auto it = v1.rbegin();
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.rend());
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
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{10});
			VERIFY(it == v2.rend());
		}
	}
	{
		List v1{1,2,3,4,5};
		List v2{10,11,12};
		v2.splice(hamon::next(v2.begin(), 1), v1, hamon::next(v1.begin(), 1), hamon::next(v1.begin(), 4));
		VERIFY(!v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 2);
		VERIFY(v2.size() == 6);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{5});
			VERIFY(it == v1.end());
		}
		{
			auto it = v1.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.rend());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{10});
			VERIFY(it == v2.rend());
		}
	}
	{
		List v1{1,2,3,4,5};
		List v2{10,11,12};
		v2.splice(v2.begin(), v1, v1.begin(), v1.begin());
		VERIFY(!v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 5);
		VERIFY(v2.size() == 3);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
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
			auto it = v1.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.rend());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{10});
			VERIFY(it == v2.rend());
		}
	}
	{
		List v{1,2,3,4,5};
		v.splice(v.end(), v, v.begin(), v.end());
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.rend());
		}
	}
	{
		List v{1,2,3,4,5};
		v.splice(v.begin(), v, hamon::next(v.begin(), 1), v.end());
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(it == v.rend());
		}
	}
	{
		List v{1,2,3,4,5};
		v.splice(v.begin(), v, hamon::next(v.begin(), 1), hamon::next(v.begin(), 4));
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{5});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(it == v.rend());
		}
	}
	{
		List v{1,2,3,4,5};
		v.splice(v.end(), v, hamon::next(v.begin(), 1), hamon::next(v.begin(), 4));
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.rend());
		}
	}

	return true;
}

template <typename T>
LIST_TEST_CONSTEXPR bool test6()
{
	using List = hamon::list<T>;
	using ConstIterator = typename List::const_iterator;

	{
		List v;
		ConstIterator pos;
		List x;
		ConstIterator first;
		ConstIterator last;
		static_assert(hamon::is_same<decltype(v.splice(pos, hamon::move(x), first, last)), void>::value, "");
#if !defined(HAMON_USE_STD_LIST)
		static_assert( noexcept(v.splice(pos, hamon::move(x), first, last)), "");
#endif
	}
	{
		List v1{1,2,3,4,5};
		List v2{10,11,12};
		v2.splice(v2.begin(), hamon::move(v1), hamon::next(v1.begin(), 1), v1.end());
		VERIFY(!v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 1);
		VERIFY(v2.size() == 7);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.end());
		}
		{
			auto it = v1.rbegin();
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.rend());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(it == v2.rend());
		}
	}
	{
		List v1{1,2,3,4,5};
		List v2{10,11,12};
		v2.splice(hamon::next(v2.begin(), 2), hamon::move(v1), hamon::next(v1.begin(), 1), v1.end());
		VERIFY(!v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 1);
		VERIFY(v2.size() == 7);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.end());
		}
		{
			auto it = v1.rbegin();
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.rend());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{10});
			VERIFY(it == v2.rend());
		}
	}
	{
		List v1{1,2,3,4,5};
		List v2{10,11,12};
		v2.splice(hamon::next(v2.begin(), 1), hamon::move(v1), v1.begin(), hamon::next(v1.begin(), 1));
		VERIFY(!v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 4);
		VERIFY(v2.size() == 4);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
		{
			auto it = v1.begin();
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v1.end());
		}
		{
			auto it = v1.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(it == v1.rend());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(it == v2.end());
		}
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{10});
			VERIFY(it == v2.rend());
		}
	}
	{
		List v1{1,2,3,4,5};
		List v2{10,11,12};
		v2.splice(v2.end(), hamon::move(v1), hamon::next(v1.begin(), 1), hamon::next(v1.begin(), 3));
		VERIFY(!v1.empty());
		VERIFY(!v2.empty());
		VERIFY(v1.size() == 3);
		VERIFY(v2.size() == 5);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v1.end());
		}
		{
			auto it = v1.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.rend());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(it == v2.end());
		}
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{10});
			VERIFY(it == v2.rend());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, SpliceTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<float>());

	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test3<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test3<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test3<float>());

	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test4<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test4<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test4<float>());

	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test5<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test5<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test5<float>());

	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test6<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test6<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test6<float>());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace splice_test

}	// namespace hamon_list_test
