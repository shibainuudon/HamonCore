/**
 *	@file	unit_test_hive_erase_position.cpp
 *
 *	@brief	erase のテスト
 *
 *	iterator erase(const_iterator position);
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace erase_position_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using iterator       = typename Hive::iterator;
	using const_iterator = typename Hive::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().erase(hamon::declval<const_iterator>())), iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().erase(hamon::declval<const_iterator>())), "");

	Hive v;
	auto it0 = v.emplace(T{1});
	auto it1 = v.emplace(T{2});
	auto it2 = v.emplace(T{3});
	auto it3 = v.emplace(T{4});
	auto it4 = v.emplace(T{5});
	VERIFY(v.size() == 5u);
	VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{15});

	{
		auto expected = hamon::next(it1);
		auto ret = v.erase(it1);
		VERIFY(ret == expected);
		VERIFY(v.size() == 4u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{13});
	}
	{
		auto expected = hamon::next(it3);
		auto ret = v.erase(it3);
		VERIFY(ret == expected);
		VERIFY(v.size() == 3u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{9});
	}

	v.emplace(T{6});
	VERIFY(v.size() == 4u);
	VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{15});

	v.erase(it2);
	VERIFY(v.size() == 3u);
	VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{12});

	v.erase(it4);
	VERIFY(v.size() == 2u);
	VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{7});

	v.erase(it0);
	VERIFY(v.size() == 1u);
	VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{6});

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, ErasePositionTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace erase_position_test

}	// namespace hamon_hive_test
