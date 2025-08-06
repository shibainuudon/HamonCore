/**
 *	@file	unit_test_hive_get_iterator.cpp
 *
 *	@brief	get_iterator のテスト
 *
 *	iterator get_iterator(const_pointer p) noexcept;
 *	const_iterator get_iterator(const_pointer p) const noexcept;
 */

#include <hamon/hive.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace get_iterator_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using const_pointer  = typename Hive::const_pointer;
	using iterator       = typename Hive::iterator;
	using const_iterator = typename Hive::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive      &>().get_iterator(hamon::declval<const_pointer>())), iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive const&>().get_iterator(hamon::declval<const_pointer>())), const_iterator>::value, "");
	static_assert(noexcept(hamon::declval<Hive      &>().get_iterator(hamon::declval<const_pointer>())), "");
	static_assert(noexcept(hamon::declval<Hive const&>().get_iterator(hamon::declval<const_pointer>())), "");

	{
		Hive v;
		auto p1 = &(*v.emplace(T{1}));
		auto p2 = &(*v.emplace(T{2}));
		auto p3 = &(*v.emplace(T{3}));
		auto p4 = &(*v.emplace(T{4}));
		VERIFY(*v.get_iterator(p1) == T{1});
		VERIFY(*v.get_iterator(p2) == T{2});
		VERIFY(*v.get_iterator(p3) == T{3});
		VERIFY(*v.get_iterator(p4) == T{4});
	}
	{
		Hive const v{3,1,4,1,5,9,2,6,5,3,5};
		for (auto it = v.begin(); it != v.end(); ++it)
		{
			auto p = &(*it);
			auto it2 = v.get_iterator(p);
			VERIFY(it == it2);
			VERIFY(*p == *it2);
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, GetIteratorTest)
{
#if (defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 120000))
	// gcc11 のときはconstexprにできない
	EXPECT_TRUE(test<int>());
	EXPECT_TRUE(test<char>());
	EXPECT_TRUE(test<float>());
#else
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
#endif
}

}	// namespace get_iterator_test

}	// namespace hamon_hive_test
