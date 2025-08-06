/**
 *	@file	unit_test_hive_begin_end.cpp
 *
 *	@brief	begin, end のテスト
 *
 *	iterator                begin() noexcept;
 *	const_iterator          begin() const noexcept;
 *	iterator                end() noexcept;
 *	const_iterator          end() const noexcept;
 */

#include <hamon/hive.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace begin_end_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using iterator       = typename Hive::iterator;
	using const_iterator = typename Hive::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>().begin()), iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>().end()),   iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive const&>().begin()), const_iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive const&>().end()),   const_iterator>::value, "");

	static_assert(noexcept(hamon::declval<Hive&>().begin()), "");
	static_assert(noexcept(hamon::declval<Hive&>().end()), "");
	static_assert(noexcept(hamon::declval<Hive const&>().begin()), "");
	static_assert(noexcept(hamon::declval<Hive const&>().end()), "");

	{
		Hive v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		Hive const v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		Hive v{1,2,3};
		auto it = v.begin();
		T sum{};
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		sum += *it;
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		sum += *it;
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		sum += *it;
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(sum == T{6});
	}
	{
		Hive const v{11,12,13,14};
		auto it = v.begin();
		T sum{};
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		sum += *it;
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		sum += *it;
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		sum += *it;
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		sum += *it;
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(sum == T{50});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, BeginEndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace begin_end_test

}	// namespace hamon_hive_test
