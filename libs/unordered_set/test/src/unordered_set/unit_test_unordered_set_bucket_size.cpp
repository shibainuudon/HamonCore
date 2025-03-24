/**
 *	@file	unit_test_unordered_set_bucket_size.cpp
 *
 *	@brief	bucket_size のテスト
 *
 *	constexpr size_type bucket_size(size_type n) const;
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace bucket_size_test
{

#if !defined(HAMON_USE_STD_UNORDERED_SET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::unordered_set<Key>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().bucket_size(hamon::declval<SizeType>())), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().bucket_size(hamon::declval<SizeType>())), SizeType>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_SET)
	static_assert( noexcept(hamon::declval<Set&>().bucket_size(hamon::declval<SizeType>())), "");
	static_assert( noexcept(hamon::declval<Set const&>().bucket_size(hamon::declval<SizeType>())), "");
#endif

	Set const v{Key{3}, Key{1}, Key{4}, Key{1}, Key{5}};
	VERIFY(v.bucket_size(v.bucket(Key{0})) >= 0);
	VERIFY(v.bucket_size(v.bucket(Key{1})) >= 1);
	VERIFY(v.bucket_size(v.bucket(Key{2})) >= 0);
	VERIFY(v.bucket_size(v.bucket(Key{3})) >= 1);
	VERIFY(v.bucket_size(v.bucket(Key{4})) >= 1);
	VERIFY(v.bucket_size(v.bucket(Key{5})) >= 1);

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, BucketSizeTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace bucket_size_test

}	// namespace hamon_unordered_set_test
