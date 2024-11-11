/**
 *	@file	unit_test_set_key_comp.cpp
 *
 *	@brief	key_comp のテスト
 *
 *	key_compare key_comp() const;
 */

#include <hamon/set/set.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace key_comp_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

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
SET_TEST_CONSTEXPR bool test_impl(Compare const& comp)
{
	using Set = hamon::set<Key, Compare>;

	{
		Set v(comp);
		static_assert(hamon::is_same<decltype(v.key_comp()), Compare>::value, "");
		static_assert(!noexcept(v.key_comp()), "");
		VERIFY(v.key_comp() == comp);
	}
	{
		Set const v(comp);
		static_assert(hamon::is_same<decltype(v.key_comp()), Compare>::value, "");
		static_assert(!noexcept(v.key_comp()), "");
		VERIFY(v.key_comp() == comp);
	}

	return true;
}

template <typename Key>
SET_TEST_CONSTEXPR bool test()
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

GTEST_TEST(SetTest, KeyCompTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/set/key_comp
	{
		hamon::set<int, ModCmp> cont{1, 2, 3, 4, 5};

		auto comp_func = cont.key_comp();

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

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace key_comp_test

}	// namespace hamon_set_test
