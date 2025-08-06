/**
 *	@file	unit_test_hive_splice.cpp
 *
 *	@brief	splice のテスト
 *
 *	void splice(hive& x);
 *	void splice(hive&& x);
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/stdexcept/length_error.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace splice_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().splice(hamon::declval<Hive&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().splice(hamon::declval<Hive&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().splice(hamon::declval<Hive&>())), "");
	static_assert(!noexcept(hamon::declval<Hive>().splice(hamon::declval<Hive&&>())), "");

	{
		Hive v1{1,2,3,4,5};
		Hive v2{6,7,8,9};

		auto it1 = v2.begin();
		auto it2 = hamon::next(it1);
		auto it3 = hamon::next(it2);
		auto it4 = hamon::next(it3);

		v1.splice(v1);

		VERIFY(v1.size() == 5u);
		VERIFY(v2.size() == 4u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{15});
		VERIFY(hamon::accumulate(v2.begin(), v2.end(), T{}, hamon::plus<T>{}) == T{30});

		v1.splice(v2);

		VERIFY(v1.size() == 9u);
		VERIFY(v2.size() == 0u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{45});
		VERIFY((*it1 + *it2 + *it3 + *it4) == T{30});
	}
	{
		Hive v1{1,2,3};
		Hive v2{4,5,6,7,8,9,10,11,12,13};

		hamon::vector<T*> vp;
		for (auto it = v2.begin(); it != v2.end(); ++it)
		{
			vp.push_back(&(*it));
		}

		v1.splice(hamon::move(v2));

		VERIFY(v1.size() == 13u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{91});

		T sum{};
		for (auto it = vp.begin(); it != vp.end(); ++it)
		{
			sum += *(*it);
		}
		VERIFY(sum == T{85});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, SpliceTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::hive<int> v1{100, 13, hamon::hive_limits{8, 16}};
		hamon::hive<int> v2{200, 42, hamon::hive_limits{8, 64}};
		EXPECT_THROW(v1.splice(v2), hamon::length_error);
		EXPECT_EQ(100u, v1.size());
		EXPECT_EQ(200u, v2.size());
		v2.splice(v1);
		EXPECT_EQ(  0u, v1.size());
		EXPECT_EQ(300u, v2.size());
	}
	{
		hamon::hive<int> v1{100, 13, hamon::hive_limits{8, 16}};
		hamon::hive<int> v2{200, 42, hamon::hive_limits{1, 16}};
		EXPECT_THROW(v1.splice(v2), hamon::length_error);
		EXPECT_EQ(100u, v1.size());
		EXPECT_EQ(200u, v2.size());
		v2.splice(v1);
		EXPECT_EQ(  0u, v1.size());
		EXPECT_EQ(300u, v2.size());
	}
#endif
}

}	// namespace splice_test

}	// namespace hamon_hive_test
