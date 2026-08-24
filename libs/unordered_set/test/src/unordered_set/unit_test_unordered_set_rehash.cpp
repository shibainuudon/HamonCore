/**
 *	@file	unit_test_unordered_set_rehash.cpp
 *
 *	@brief	rehash のテスト
 *
 *	constexpr void rehash(size_type n);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace rehash_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_set<Key>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().rehash(hamon::declval<SizeType>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().rehash(hamon::declval<SizeType>())), "");

	Set v;

	v.rehash(10);
	VERIFY(static_cast<float>(v.bucket_count()) >= static_cast<float>(v.size()) / v.max_load_factor());
	VERIFY(v.bucket_count() >= 10);

	for (int i = 0; i < 100; ++i)
	{
		v.emplace(static_cast<Key>(i));
	}

	v.rehash(1000);
	VERIFY(static_cast<float>(v.bucket_count()) >= static_cast<float>(v.size()) / v.max_load_factor());
	VERIFY(v.bucket_count() >= 1000);

	v.clear();
	v.rehash(1);
	VERIFY(static_cast<float>(v.bucket_count()) >= static_cast<float>(v.size()) / v.max_load_factor());
	VERIFY(v.bucket_count() >= 1);

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, RehashTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace rehash_test

}	// namespace hamon_unordered_set_test
