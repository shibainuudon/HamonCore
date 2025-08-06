/**
 *	@file	unit_test_hive_emplace_hint.cpp
 *
 *	@brief	emplace_hint のテスト
 *
 *	template<class... Args> iterator emplace_hint(const_iterator hint, Args&&... args);
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace emplace_hint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using iterator = typename Hive::iterator;
	using const_iterator = typename Hive::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().emplace_hint(hamon::declval<const_iterator>())), iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().emplace_hint(hamon::declval<const_iterator>(), hamon::declval<T>())), iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().emplace_hint(hamon::declval<const_iterator>())), "");
	static_assert(!noexcept(hamon::declval<Hive>().emplace_hint(hamon::declval<const_iterator>(), hamon::declval<T>())), "");

	Hive v;
	VERIFY(v.empty());
	VERIFY(v.size() == 0u);
	{
		auto ret = v.emplace_hint(v.cbegin(), T{10});
		VERIFY(ret == v.begin());
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{10});
	}
	VERIFY(v.size() == 1u);
	{
		auto ret = v.emplace_hint(v.cend(), T{20});
		VERIFY(*ret == T{20});
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{30});
	}
	VERIFY(v.size() == 2u);

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, EmplaceHintTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace emplace_hint_test

}	// namespace hamon_hive_test
