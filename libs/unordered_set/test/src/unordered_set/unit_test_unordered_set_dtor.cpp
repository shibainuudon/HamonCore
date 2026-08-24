/**
 *	@file	unit_test_unordered_set_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	constexpr ~unordered_set();
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_destructible.hpp>
#include <hamon/type_traits/is_nothrow_destructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace dtor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_set<Key>;

	static_assert( hamon::is_destructible<Set>::value, "");
	static_assert( hamon::is_nothrow_destructible<Set>::value, "");
	static_assert(!hamon::is_trivially_destructible<Set>::value, "");

	// TODO

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, DtorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace dtor_test

}	// namespace hamon_unordered_set_test
