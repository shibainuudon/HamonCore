/**
 *	@file	unit_test_hive_crbegin_crend.cpp
 *
 *	@brief	crbegin, crend のテスト
 *
 *	const_reverse_iterator  crbegin() const noexcept;
 *	const_reverse_iterator  crend() const noexcept;
 */

#include <hamon/hive.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace crbegin_crend_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using const_reverse_iterator = typename Hive::const_reverse_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>().crbegin()), const_reverse_iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>().crend()),   const_reverse_iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive const&>().crbegin()), const_reverse_iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive const&>().crend()),   const_reverse_iterator>::value, "");

	static_assert(noexcept(hamon::declval<Hive&>().crbegin()), "");
	static_assert(noexcept(hamon::declval<Hive&>().crend()), "");
	static_assert(noexcept(hamon::declval<Hive const&>().crbegin()), "");
	static_assert(noexcept(hamon::declval<Hive const&>().crend()), "");

	{
		Hive v;
		auto it = v.crbegin();
		VERIFY(it == v.crbegin());
		VERIFY(it == v.crend());
	}
	{
		Hive const v;
		auto it = v.crbegin();
		VERIFY(it == v.crbegin());
		VERIFY(it == v.crend());
	}
	{
		Hive v{1,2,3};
		auto it = v.crbegin();
		T sum{};
		VERIFY(it == v.crbegin());
		VERIFY(it != v.crend());
		sum += *it;
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		sum += *it;
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		sum += *it;
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it == v.crend());
		VERIFY(sum == T{6});
	}
	{
		Hive const v{11,12,13,14};
		auto it = v.crbegin();
		T sum{};
		VERIFY(it == v.crbegin());
		VERIFY(it != v.crend());
		sum += *it;
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		sum += *it;
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		sum += *it;
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		sum += *it;
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it == v.crend());
		VERIFY(sum == T{50});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, CRBeginCREndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace crbegin_crend_test

}	// namespace hamon_hive_test
