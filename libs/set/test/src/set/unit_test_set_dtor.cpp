/**
 *	@file	unit_test_set_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	~set();
 */

#include <hamon/set/set.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace dtor_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

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
SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::set<Key>;

	static_assert( hamon::is_destructible<Set>::value, "");
	static_assert( hamon::is_nothrow_destructible<Set>::value, "");
	static_assert(!hamon::is_trivially_destructible<Set>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, DtorTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));

	S::s_dtor_count = 0;
	{
		hamon::set<S> v;
	}
	EXPECT_EQ(0, S::s_dtor_count);

	S::s_dtor_count = 0;
	{
		hamon::set<S> v;

		v.emplace(10);
		EXPECT_EQ(0, S::s_dtor_count);
	}
	EXPECT_EQ(1, S::s_dtor_count);

	S::s_dtor_count = 0;
	{
		hamon::set<S> v;
		v.emplace(10);
		v.emplace(15);
		v.emplace(20);
		EXPECT_EQ(0, S::s_dtor_count);
	}
	EXPECT_EQ(3, S::s_dtor_count);
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace dtor_test

}	// namespace hamon_set_test
