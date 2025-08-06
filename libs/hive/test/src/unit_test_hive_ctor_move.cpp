/**
 *	@file	unit_test_hive_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	hive(hive&&) noexcept;
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_implicitly_move_constructible.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace ctor_move_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Hive = hamon::hive<T>;

	static_assert( hamon::is_move_constructible<Hive>::value, "");
	static_assert( hamon::is_nothrow_move_constructible<Hive>::value, "");
	static_assert( hamon::is_implicitly_move_constructible<Hive>::value, "");
	static_assert(!hamon::is_trivially_move_constructible<Hive>::value, "");

	{
		Hive v1 = {T{1}, T{2}, T{3}};
		Hive v2 = {hamon::move(v1)};
		VERIFY(v2.size() == 3u);
		VERIFY(hamon::accumulate(v2.begin(), v2.end(), T{}, hamon::plus<T>{}) == T{6});
	}

	return true;
}

// コピーもムーブもできない型
struct NonMovable
{
	int value;

	HAMON_CXX14_CONSTEXPR NonMovable(int v) : value(v) {}

	NonMovable(NonMovable const&)            = delete;
	NonMovable(NonMovable &&)                = delete;
	NonMovable& operator=(NonMovable const&) = delete;
	NonMovable& operator=(NonMovable &&)     = delete;
};

HAMON_CXX20_CONSTEXPR bool test2()
{
	hamon::hive<NonMovable> v1;
	v1.emplace(1);
	v1.emplace(2);
	v1.emplace(3);
	v1.emplace(4);

	hamon::hive<NonMovable> v2(hamon::move(v1));
	VERIFY(v2.size() == 4u);
	VERIFY(hamon::accumulate(v2.begin(), v2.end(), 0,
		[](int lhs, NonMovable const& rhs) { return lhs + rhs.value; }) == 10);

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, CtorMoveTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<float>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());
}

}	// namespace ctor_move_test

}	// namespace hamon_hive_test
