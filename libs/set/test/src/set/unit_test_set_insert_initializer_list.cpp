﻿/**
 *	@file	unit_test_set_insert_initializer_list.cpp
 *
 *	@brief	insert のテスト
 *
 *	void insert(initializer_list<value_type>);
 */

#include <hamon/set/set.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace insert_initializer_list_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

#if !defined(HAMON_NO_EXCEPTIONS)
struct MayThrow
{
	struct Exception{};

	int value;

	MayThrow(int v) : value(v)
	{}

	MayThrow(MayThrow const& x)
		: value(x.value)
	{
		if (x.value < 0)
		{
			throw Exception{};
		}
	}

	MayThrow(MayThrow&&)                 = default;
	MayThrow& operator=(MayThrow&&)      = delete;
	MayThrow& operator=(MayThrow const&) = delete;

	friend constexpr bool operator<(MayThrow const& lhs, MayThrow const& rhs)
	{
		return lhs.value < rhs.value;
	}
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::set<Key>;
	using ValueType = typename Set::value_type;

	Set v;

	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<std::initializer_list<ValueType>>())), void>::value, "");
	static_assert(!noexcept(v.insert(hamon::declval<std::initializer_list<ValueType>>())), "");

	{
		v.insert({ Key{3}, Key{2}, Key{3}, Key{1}, Key{2}, Key{3} });
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		{
			auto it = v.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{2});
			VERIFY(*it++ == Key{3});
			VERIFY(it == v.end());
		}
	}
	{
		v.insert({ Key{2}, Key{4}, Key{0}, Key{1} });
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		{
			auto it = v.begin();
			VERIFY(*it++ == Key{0});
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{2});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{4});
			VERIFY(it == v.end());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, InsertInitializerListTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using Set = hamon::set<MayThrow>;

		Set v;
		EXPECT_EQ(0u, v.size());

		EXPECT_THROW(v.insert({ MayThrow{40}, MayThrow{10}, MayThrow{-30}, MayThrow{20} }), MayThrow::Exception);
		EXPECT_EQ(2u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(10, (it++)->value);
			EXPECT_EQ(40, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		v.emplace(-20);
		EXPECT_EQ(3u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(-20, (it++)->value);
			EXPECT_EQ( 10, (it++)->value);
			EXPECT_EQ( 40, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_NO_THROW(v.insert({ MayThrow{ 20}, MayThrow{-20}, MayThrow{30} }));
		EXPECT_EQ(5u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(-20, (it++)->value);
			EXPECT_EQ( 10, (it++)->value);
			EXPECT_EQ( 20, (it++)->value);
			EXPECT_EQ( 30, (it++)->value);
			EXPECT_EQ( 40, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
#endif
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace insert_initializer_list_test

}	// namespace hamon_set_test
