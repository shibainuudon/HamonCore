/**
 *	@file	unit_test_hive_cbegin_cend.cpp
 *
 *	@brief	cbegin, cend のテスト
 *
 *	const_iterator          cbegin() const noexcept;
 *	const_iterator          cend() const noexcept;
 */

#include <hamon/hive.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace cbegin_cend_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using const_iterator = typename Hive::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>().cbegin()), const_iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>().cend()),   const_iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive const&>().cbegin()), const_iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive const&>().cend()),   const_iterator>::value, "");

	static_assert(noexcept(hamon::declval<Hive&>().cbegin()), "");
	static_assert(noexcept(hamon::declval<Hive&>().cend()), "");
	static_assert(noexcept(hamon::declval<Hive const&>().cbegin()), "");
	static_assert(noexcept(hamon::declval<Hive const&>().cend()), "");

	{
		Hive v;
		auto it = v.cbegin();
		VERIFY(it == v.cbegin());
		VERIFY(it == v.cend());
	}
	{
		Hive const v;
		auto it = v.cbegin();
		VERIFY(it == v.cbegin());
		VERIFY(it == v.cend());
	}
	{
		Hive v{1,2,3};
		auto it = v.cbegin();
		T sum{};
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		sum += *it;
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		sum += *it;
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		sum += *it;
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
		VERIFY(sum == T{6});
	}
	{
		Hive const v{11,12,13,14};
		auto it = v.cbegin();
		T sum{};
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		sum += *it;
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		sum += *it;
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		sum += *it;
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		sum += *it;
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
		VERIFY(sum == T{50});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, CBeginCEndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace cbegin_cend_test

}	// namespace hamon_hive_test
