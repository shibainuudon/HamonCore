/**
 *	@file	unit_test_hive_rbegin_rend.cpp
 *
 *	@brief	rbegin, rend のテスト
 *
 *	reverse_iterator        rbegin() noexcept;
 *	const_reverse_iterator  rbegin() const noexcept;
 *	reverse_iterator        rend() noexcept;
 *	const_reverse_iterator  rend() const noexcept;
 */

#include <hamon/hive.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace rbegin_rend_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using reverse_iterator       = typename Hive::reverse_iterator;
	using const_reverse_iterator = typename Hive::const_reverse_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>().rbegin()), reverse_iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>().rend()),   reverse_iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive const&>().rbegin()), const_reverse_iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive const&>().rend()),   const_reverse_iterator>::value, "");

	static_assert(noexcept(hamon::declval<Hive&>().rbegin()), "");
	static_assert(noexcept(hamon::declval<Hive&>().rend()), "");
	static_assert(noexcept(hamon::declval<Hive const&>().rbegin()), "");
	static_assert(noexcept(hamon::declval<Hive const&>().rend()), "");

	{
		Hive v;
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it == v.rend());
	}
	{
		Hive const v;
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it == v.rend());
	}
	{
		Hive v{1,2,3};
		auto it = v.rbegin();
		T sum{};
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		sum += *it;
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		sum += *it;
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		sum += *it;
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
		VERIFY(sum == T{6});
	}
	{
		Hive const v{11,12,13,14};
		auto it = v.rbegin();
		T sum{};
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		sum += *it;
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		sum += *it;
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		sum += *it;
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		sum += *it;
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
		VERIFY(sum == T{50});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, RBeginREndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace rbegin_rend_test

}	// namespace hamon_hive_test
