/**
 *	@file	unit_test_set_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 *
 *	template<class Key, class Compare, class Allocator, class Predicate>
 *	typename set<Key, Compare, Allocator>::size_type
 *	erase_if(set<Key, Compare, Allocator>& c, Predicate pred);
 */

#include <hamon/set/erase_if.hpp>
#include <hamon/set/set.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <string>
#include <sstream>

namespace hamon_set_test
{

namespace erase_if_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

struct IsZero
{
	template <typename T>
	constexpr bool operator()(T x) const
	{
		return x == 0;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::set<Key>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(
		hamon::erase_if(hamon::declval<Set&>(), hamon::declval<IsZero>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::erase_if(hamon::declval<Set&>(), hamon::declval<IsZero>())), "");

	{
		Set v = {3,1,4,5,2};
		auto r = hamon::erase_if(v, [](Key x) { return x % 2 == 0; });
		VERIFY(r == 2);
		const int v2[] = {1,3,5,};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	{
		Set v = {3,1,4,5,2};
		auto r = hamon::erase_if(v, IsZero{});
		VERIFY(r == 0);
		const int v2[] = {1,2,3,4,5,};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	{
		Set v = {3,1,4,5,9,2,6,};
		auto r = hamon::erase_if(v, [](Key x) { return x >= 5; });
		VERIFY(r == 3);
		const int v2[] = {1,2,3,4,};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	return true;
}

#undef VERIFY

template <typename T, typename C>
std::string ToString(const hamon::set<T, C>& set)
{
	std::stringstream out;
	auto n = set.size();
	out << "{";
	for (auto const& elm : set)
	{
		out << elm << (--n ? ", " : "");
	}
	out << "}";
	return out.str();
}

GTEST_TEST(SetTest, EraseIfTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test<short>()));

	// https://en.cppreference.com/w/cpp/container/set/erase_if
	{
		hamon::set<int> data {3, 3, 4, 5, 5, 6, 6, 7, 2, 1, 0};
		EXPECT_EQ("{0, 1, 2, 3, 4, 5, 6, 7}", ToString(data));

		auto divisible_by_3 = [](int x) { return (x % 3) == 0; };

		const auto count = hamon::erase_if(data, divisible_by_3);
		EXPECT_EQ("{1, 2, 4, 5, 7}", ToString(data));
		EXPECT_EQ(3u, count);
	}
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace erase_if_test

}	// namespace hamon_set_test
