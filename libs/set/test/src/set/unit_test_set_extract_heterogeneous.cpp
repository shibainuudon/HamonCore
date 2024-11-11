﻿/**
 *	@file	unit_test_set_extract_heterogeneous.cpp
 *
 *	@brief	extract のテスト
 *
 *	template<class K> node_type extract(K&& x);
 */

#include <hamon/set/set.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_SET) || \
	(defined(__cpp_lib_associative_heterogeneous_erasure) && (__cpp_lib_associative_heterogeneous_erasure >= 202110L))

namespace hamon_set_test
{

namespace extract_heterogeneous_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::set<Key, hamon::less<>>;
	using NodeType = typename Set::node_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().extract(hamon::declval<int>())), NodeType>::value, "");
#if !defined(HAMON_USE_STD_SET)
	static_assert(!noexcept(hamon::declval<Set&>().extract(hamon::declval<int>())), "");
#endif

	Set v{Key{3}, Key{1}, Key{4}, Key{1}, Key{5} };
	VERIFY(v.size() == 4);

	{
		auto r = v.extract(3);
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.value() == Key{3});
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(it == v.end());
	}
	{
		auto r = v.extract(2);
		VERIFY(bool(r) == false);
		VERIFY(r.empty() == true);
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(it == v.end());
	}
	{
		auto r = v.extract(5);
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.value() == Key{5});
		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 4);
		VERIFY(it == v.end());
	}
	{
		auto r = v.extract(3);
		VERIFY(bool(r) == false);
		VERIFY(r.empty() == true);
		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 4);
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

struct S
{
	static int s_ctor_count;
	static int s_dtor_count;

	int value;

	S(int v) : value(v)
	{
		++s_ctor_count;
	}

	~S()
	{
		++s_dtor_count;
	}

	S(S&&)                 = delete;
	S(S const&)            = delete;
	S& operator=(S&&)      = delete;
	S& operator=(S const&) = delete;

	friend bool operator<(S const& lhs, S const& rhs)
	{
		return lhs.value < rhs.value;
	}

	friend bool operator<(S const& lhs, int rhs)
	{
		return lhs.value < rhs;
	}

	friend bool operator<(int lhs, S const& rhs)
	{
		return lhs < rhs.value;
	}
};

int S::s_ctor_count = 0;
int S::s_dtor_count = 0;

GTEST_TEST(SetTest, ExtractHeterogeneousTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));

	S::s_ctor_count = 0;
	S::s_dtor_count = 0;
	{
		hamon::set<S, hamon::less<>> v;
		v.emplace(1);
		v.emplace(2);
		v.emplace(3);
		v.emplace(4);
		EXPECT_EQ(4, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		v.extract(2);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(4, S::s_ctor_count);
		EXPECT_EQ(1, S::s_dtor_count);

		v.extract(3);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(4, S::s_ctor_count);
		EXPECT_EQ(2, S::s_dtor_count);

		v.extract(2);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(4, S::s_ctor_count);
		EXPECT_EQ(2, S::s_dtor_count);

		v.extract(5);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(4, S::s_ctor_count);
		EXPECT_EQ(2, S::s_dtor_count);
	}
	EXPECT_EQ(4, S::s_ctor_count);
	EXPECT_EQ(4, S::s_dtor_count);
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace extract_heterogeneous_test

}	// namespace hamon_set_test

#endif
