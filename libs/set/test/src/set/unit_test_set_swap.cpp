﻿/**
 *	@file	unit_test_set_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	void swap(set&)
 *		noexcept(allocator_traits<Allocator>::is_always_equal::value &&
 *			is_nothrow_swappable_v<Compare>);
 *
 *	template<class Key, class Compare, class Allocator>
 *	void swap(set<Key, Compare, Allocator>& x, set<Key, Compare, Allocator>& y)
 *		noexcept(noexcept(x.swap(y)));
 */

#include <hamon/set/set.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace swap_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

template <typename T>
struct MyAllocator
{
	using value_type = T;
#if !defined(HAMON_USE_STD_SET)
	using is_always_equal = hamon::false_type;
	using propagate_on_container_swap = hamon::true_type;
#else
	using is_always_equal = std::false_type;
	using propagate_on_container_swap = std::true_type;
#endif

	int id;

	HAMON_CXX11_CONSTEXPR
	MyAllocator() : id(0) {}

	HAMON_CXX11_CONSTEXPR
	MyAllocator(int i) : id(i) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	MyAllocator(MyAllocator<U> const& a) : id(a.id) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		// [allocator.members]/11
		::operator delete(p);
		(void)n;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(MyAllocator const& rhs) const
	{
		return id == rhs.id;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(MyAllocator const& rhs) const
	{
		return id != rhs.id;
	}
};

struct MyLess
{
	int id;

	HAMON_CXX11_CONSTEXPR
	MyLess() : id(0) {}

	HAMON_CXX11_CONSTEXPR
	MyLess(int i) : id(i) {}

	template <typename T>
	HAMON_CXX11_CONSTEXPR
	bool operator()(T const& x, T const& y) const
	{
		return x < y;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(MyLess const& rhs) const
	{
		return id == rhs.id;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
SET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::set<Key>;

	{
		Set v;
		static_assert(hamon::is_same<decltype(v.swap(v)), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(v, v)), void>::value, "");
		static_assert(noexcept(v.swap(v)), "");
		static_assert(noexcept(swap(v, v)), "");
	}
	{
		Set v1 { Key{3}, Key{1}, Key{4}, Key{1}, Key{5} };
		Set v2 { Key{1}, Key{7}, Key{3} };

		v1.swap(v2);
		VERIFY(v1.size() == 3);
		VERIFY(v2.size() == 4);
		{
			auto it = v1.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{7});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{5});
			VERIFY(it == v2.end());
		}

		swap(v1, v2);
		VERIFY(v1.size() == 4);
		VERIFY(v2.size() == 3);
		{
			auto it = v1.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{5});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{7});
			VERIFY(it == v2.end());
		}
	}
	{
		Set v1;
		Set v2 { Key{10} };

		v1.swap(v2);
		VERIFY(v1.size() == 1);
		VERIFY(v2.size() == 0);
		{
			auto it = v1.begin();
			VERIFY(*it++ == Key{10});
			VERIFY(it == v1.end());
		}

		swap(v1, v2);
		VERIFY(v1.size() == 0);
		VERIFY(v2.size() == 1);
		{
			auto it = v2.begin();
			VERIFY(*it++ == Key{10});
			VERIFY(it == v2.end());
		}
	}

	return true;
}

template <typename Key>
SET_TEST_CONSTEXPR bool test2()
{
	using Compare = MyLess;
	using Allocator = MyAllocator<Key>;
	using Set = hamon::set<Key, Compare, Allocator>;

	{
		Set v;
		static_assert(hamon::is_same<decltype(v.swap(v)), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(v, v)), void>::value, "");
#if !defined(HAMON_USE_STD_SET)
		static_assert(!noexcept(v.swap(v)), "");
		static_assert(!noexcept(swap(v, v)), "");
#endif
	}
	{
		Compare c1{10};
		Compare c2{20};
		Allocator a1{30};
		Allocator a2{40};
		Set v1 {{ Key{3}, Key{1}, Key{4}, Key{1}, Key{5} }, c1, a1};
		Set v2 {{ Key{1}, Key{7}, Key{3} }, c2, a2};

		v1.swap(v2);
		VERIFY(v1.size() == 3);
		VERIFY(v2.size() == 4);
		VERIFY(v1.key_comp() == c2);
		VERIFY(v2.key_comp() == c1);
		VERIFY(v1.get_allocator() == a2);
		VERIFY(v2.get_allocator() == a1);
		{
			auto it = v1.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{7});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{5});
			VERIFY(it == v2.end());
		}

		swap(v1, v2);
		VERIFY(v1.size() == 4);
		VERIFY(v2.size() == 3);
		VERIFY(v1.key_comp() == c1);
		VERIFY(v2.key_comp() == c2);
		VERIFY(v1.get_allocator() == a1);
		VERIFY(v2.get_allocator() == a2);
		{
			auto it = v1.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{5});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{7});
			VERIFY(it == v2.end());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, SwapTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace swap_test

}	// namespace hamon_set_test