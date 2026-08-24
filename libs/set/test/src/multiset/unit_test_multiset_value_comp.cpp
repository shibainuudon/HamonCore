/**
 *	@file	unit_test_multiset_value_comp.cpp
 *
 *	@brief	value_comp のテスト
 *
 *	value_compare value_comp() const;
 */

#include <hamon/set/multiset.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace value_comp_test
{

struct MyLess
{
	int id;

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

struct MyGreater
{
	int id;

	HAMON_CXX11_CONSTEXPR
	MyGreater() : id(0) {}

	HAMON_CXX11_CONSTEXPR
	MyGreater(int i) : id(i) {}

	template <typename T>
	HAMON_CXX11_CONSTEXPR
	bool operator()(T const& x, T const& y) const
	{
		return x > y;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(MyGreater const& rhs) const
	{
		return id == rhs.id;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename Compare>
HAMON_CXX20_CONSTEXPR bool test_impl(Compare const& comp)
{
	using Set = hamon::multiset<Key, Compare>;

	{
		Set v(comp);
		static_assert(hamon::is_same<decltype(v.value_comp()), Compare>::value, "");
		static_assert(!noexcept(v.value_comp()), "");
		VERIFY(v.value_comp() == comp);
	}
	{
		Set const v(comp);
		static_assert(hamon::is_same<decltype(v.value_comp()), Compare>::value, "");
		static_assert(!noexcept(v.value_comp()), "");
		VERIFY(v.value_comp() == comp);
	}

	return true;
}

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	{
		MyLess comp{13};
		VERIFY(test_impl<Key>(comp));
	}
	{
		MyGreater comp{13};
		VERIFY(test_impl<Key>(comp));
	}

	return true;
}

#undef VERIFY

// Example module 97 key compare function
struct ModCmp
{
	bool operator()(int lhs, int rhs) const
	{
		return (lhs % 97) < (rhs % 97);
	}
};

GTEST_TEST(MultisetTest, ValueCompTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/multiset/value_comp
	{
		hamon::multiset<int, ModCmp> cont{1, 2, 3, 4, 5};

		auto comp_func = cont.value_comp();

		auto it = cont.begin();
		EXPECT_TRUE (comp_func(*it, 100));
		EXPECT_FALSE(comp_func(100, *it));
		++it;
		EXPECT_TRUE (comp_func(*it, 100));
		EXPECT_FALSE(comp_func(100, *it));
		++it;
		EXPECT_FALSE(comp_func(*it, 100));
		EXPECT_FALSE(comp_func(100, *it));
		++it;
		EXPECT_FALSE(comp_func(*it, 100));
		EXPECT_TRUE (comp_func(100, *it));
		++it;
		EXPECT_FALSE(comp_func(*it, 100));
		EXPECT_TRUE (comp_func(100, *it));
		++it;
		EXPECT_TRUE(it == cont.end());
	}
}

}	// namespace value_comp_test

}	// namespace hamon_multiset_test
