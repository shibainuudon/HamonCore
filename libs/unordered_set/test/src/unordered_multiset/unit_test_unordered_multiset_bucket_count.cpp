/**
 *	@file	unit_test_unordered_multiset_bucket_count.cpp
 *
 *	@brief	bucket_count のテスト
 *
 *	constexpr size_type bucket_count() const noexcept;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace bucket_count_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().bucket_count()), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().bucket_count()), SizeType>::value, "");
	static_assert(noexcept(hamon::declval<Set&>().bucket_count()), "");
	static_assert(noexcept(hamon::declval<Set const&>().bucket_count()), "");

	Set const v{Key{3}, Key{1}, Key{4}, Key{1}, Key{5}};
	VERIFY(v.bucket_count() > 0);

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, BucketCountTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace bucket_count_test

}	// namespace hamon_unordered_multiset_test
