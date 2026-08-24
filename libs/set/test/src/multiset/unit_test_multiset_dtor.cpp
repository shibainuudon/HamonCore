/**
 *	@file	unit_test_multiset_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	~multiset();
 */

#include <hamon/set/multiset.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace dtor_test
{

struct S
{
	static int s_dtor_count;

	int value;

	S(int v) : value(v)
	{
	}

	~S()
	{
		++s_dtor_count;
	}

	friend bool operator<(S const& lhs, S const& rhs)
	{
		return lhs.value < rhs.value;
	}
};

int S::s_dtor_count = 0;

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::multiset<Key>;

	static_assert( hamon::is_destructible<Set>::value, "");
	static_assert( hamon::is_nothrow_destructible<Set>::value, "");
	static_assert(!hamon::is_trivially_destructible<Set>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, DtorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));

	S::s_dtor_count = 0;
	{
		hamon::multiset<S> v;
	}
	EXPECT_EQ(0, S::s_dtor_count);

	S::s_dtor_count = 0;
	{
		hamon::multiset<S> v;

		v.emplace(10);
		EXPECT_EQ(0, S::s_dtor_count);
	}
	EXPECT_EQ(1, S::s_dtor_count);

	S::s_dtor_count = 0;
	{
		hamon::multiset<S> v;
		v.emplace(10);
		v.emplace(15);
		v.emplace(20);
		v.emplace(10);
		EXPECT_EQ(0, S::s_dtor_count);
	}
	EXPECT_EQ(4, S::s_dtor_count);
}

}	// namespace dtor_test

}	// namespace hamon_multiset_test
