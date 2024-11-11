/**
 *	@file	unit_test_multiset_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 *
 *	template<class Key, class Compare, class Allocator, class Predicate>
 *	typename multiset<Key, Compare, Allocator>::size_type
 *	erase_if(multiset<Key, Compare, Allocator>& c, Predicate pred);
 */

#include <hamon/set/erase_if.hpp>
#include <hamon/set/multiset.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <string>
#include <sstream>

namespace hamon_multiset_test
{

namespace erase_if_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
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
MULTISET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::multiset<Key>;
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
		Set v = {3,1,4,1,5,9,2,6,5,3,5,};
		auto r = hamon::erase_if(v, [](Key x) { return x >= 5; });
		VERIFY(r == 5);
		const int v2[] = {1,1,2,3,3,4,};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	return true;
}

#undef VERIFY

template <typename T, typename C>
std::string ToString(const hamon::multiset<T, C>& set)
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

GTEST_TEST(MultisetTest, EraseIfTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<short>()));

	// https://en.cppreference.com/w/cpp/container/multiset/erase_if
	{
		hamon::multiset<int> data {3, 3, 4, 5, 5, 6, 6, 7, 2, 1, 0};
		EXPECT_EQ("{0, 1, 2, 3, 3, 4, 5, 5, 6, 6, 7}", ToString(data));

		auto divisible_by_3 = [](int x) { return (x % 3) == 0; };

		const auto count = hamon::erase_if(data, divisible_by_3);
		EXPECT_EQ("{1, 2, 4, 5, 5, 7}", ToString(data));
		EXPECT_EQ(5u, count);
	}
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace erase_if_test

}	// namespace hamon_multiset_test
