/**
 *	@file	unit_test_hive_ctor_initializer_list.cpp
 *
 *	@brief	initializer_list を引数に取るコンストラクタのテスト
 *
 *	hive(initializer_list<T> il, const Allocator& = Allocator());
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace ctor_initializer_list_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using Allocator = typename Hive::allocator_type;

	static_assert( hamon::is_constructible           <Hive, std::initializer_list<T>>::value, "");
	static_assert(!hamon::is_nothrow_constructible   <Hive, std::initializer_list<T>>::value, "");
	static_assert( hamon::is_implicitly_constructible<Hive, std::initializer_list<T>>::value, "");
	static_assert(!hamon::is_trivially_constructible <Hive, std::initializer_list<T>>::value, "");

	static_assert( hamon::is_constructible           <Hive, std::initializer_list<T>, const Allocator&>::value, "");
	static_assert(!hamon::is_nothrow_constructible   <Hive, std::initializer_list<T>, const Allocator&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Hive, std::initializer_list<T>, const Allocator&>::value, "");
	static_assert(!hamon::is_trivially_constructible <Hive, std::initializer_list<T>, const Allocator&>::value, "");

	Allocator alloc;

	{
		Hive v = {T{1}, T{2}, T{3}};
		VERIFY(v.size() == 3u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{6});
	}
	{
		Hive v({T{3}, T{1}, T{4}, T{1}, T{5}}, alloc);
		VERIFY(v.size() == 5u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{14});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, CtorInitializerListTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<double>());
}

}	// namespace ctor_initializer_list_test

}	// namespace hamon_hive_test
