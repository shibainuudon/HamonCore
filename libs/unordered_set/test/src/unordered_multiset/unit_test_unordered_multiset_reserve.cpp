/**
 *	@file	unit_test_unordered_multiset_reserve.cpp
 *
 *	@brief	reserve のテスト
 *
 *	constexpr void reserve(size_type n);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace reserve_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().reserve(hamon::declval<SizeType>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().reserve(hamon::declval<SizeType>())), "");

	Set v;

	v.max_load_factor(2.0f);
	v.reserve(22);

	VERIFY(static_cast<float>(v.bucket_count()) >= 22.0f / v.max_load_factor());

	for (int i = 0; i < 22; ++i)
	{
		v.emplace(static_cast<Key>(i));
	}

	v.reserve(99);

	VERIFY(static_cast<float>(v.bucket_count()) >= 99.0f / v.max_load_factor());

	for (int i = 0; i < 77; ++i)
	{
		v.emplace(static_cast<Key>(i+22));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, ReserveTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace reserve_test

}	// namespace hamon_unordered_multiset_test
