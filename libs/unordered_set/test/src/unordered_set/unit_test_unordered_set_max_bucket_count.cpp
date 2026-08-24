/**
 *	@file	unit_test_unordered_set_max_bucket_count.cpp
 *
 *	@brief	max_bucket_count のテスト
 *
 *	constexpr size_type max_bucket_count() const noexcept;
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace max_bucket_count_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_set<Key>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().max_bucket_count()), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().max_bucket_count()), SizeType>::value, "");
	static_assert(noexcept(hamon::declval<Set&>().max_bucket_count()), "");
	static_assert(noexcept(hamon::declval<Set const&>().max_bucket_count()), "");

	Set const v;
	VERIFY(v.max_bucket_count() > 0);

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, MaxBucketCountTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace max_bucket_count_test

}	// namespace hamon_unordered_set_test
